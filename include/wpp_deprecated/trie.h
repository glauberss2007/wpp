//
// Created by Alan de Freitas on 24/06/17.
//

#ifndef WPP_TRIE_H
#define WPP_TRIE_H

#include <cstdint>
#include <utility>
#include <tuple>
#include <unordered_map>
#include <memory>
#include <boost/lexical_cast.hpp>
#include <vector>

#include "common.h"
#include "http_response.h"
#include "http_request.h"
#include "utility.h"
#include "logging.h"
#include "websocket.h"
#include "rule.h"
#include "settings.h"


namespace wpp {

    const int RULE_SPECIAL_REDIRECT_SLASH = 1;

    // TODO: add rule : and add possibility of parameter names

    // trie data structure
    class Trie
    {
    public:
        // trie nodes
        struct Node
        {
            // each rule has an index
            unsigned rule_index{};
            // an array of indexes of children according to parameter type -> (int)ParamType::MAX parameters (number of each parameter)
            // these are only regex children
            std::array<unsigned, (int)ParamType::MAX> param_children{};
            // and an unordered map of children (that can be found by their name) that are not parameters
            std::unordered_map<std::string, unsigned> children;

            // a simple node is one with rule index 0 and no param children
            bool IsSimpleNode() const
            {
                return
                        !rule_index &&
                        std::all_of(
                                std::begin(param_children),
                                std::end(param_children),
                                [](unsigned x){ return !x; });
            }
        };

        // trie has only a vector of nodes
        Trie() : nodes_(1)
        {
        }

    private:
        // make the trie more efficient
        void optimizeNode(Node* node)
        {
            // for each parameter child possible
            for(auto x : node->param_children)
            {
                // skip if there is no child with the parameter type
                if (!x)
                    continue;
                // else, we optimize the child first
                Node* child = &nodes_[x];
                optimizeNode(child);
            }
            // if it has no children, there is nothing to optimize
            if (node->children.empty())
                return;
            // try to merge with the children
            bool mergeWithChild = true;
            // for each string child (kv.first = child's string, fv.second = child's index)
            for(auto& kv : node->children)
            {
                // if the string child has param children, we don't merge (it's a bifurcation)
                Node* child = &nodes_[kv.second];
                if (!child->IsSimpleNode())
                {
                    mergeWithChild = false;
                    break;
                }
            }
            // if we can merge (basically put the child letters together into words)
            if (mergeWithChild)
            {
                // unordered map<string,int> with indexes of nodes to be merged under each string
                decltype(node->children) merged;
                // for each child
                for(auto& kv : node->children)
                {
                    Node* child = &nodes_[kv.second];
                    // for each of the child's child
                    for(auto& child_kv : child->children)
                    {
                        // we put the strings together and keep the child index to delete later
                        merged[kv.first + child_kv.first] = child_kv.second;
                    }
                }
                // the merged children go to the node we're optimizing so they all on the same level
                node->children = std::move(merged);
                // optimize the node again (until there is nothing to optimize)
                optimizeNode(node);
            }
            else
            {
                // if we're not going to merge
                // we go through each child optimizing them
                for(auto& kv : node->children)
                {
                    Node* child = &nodes_[kv.second];
                    optimizeNode(child);
                }
            }
        }

        // make the whole trie more efficient (recursively optimize all nodes)
        void optimize()
        {
            optimizeNode(head());
        }

    public:
        // check if root node has no param children and then optimize
        void validate()
        {
            if (!head()->IsSimpleNode())
                throw std::runtime_error("Internal error: Trie header should be simple!");
            optimize();
        }

        // find a node according to that request url
        std::pair<unsigned, routing_params> find(const std::string& req_url, const Node* node = nullptr, unsigned pos = 0, routing_params* params = nullptr) const
        {
            // routing parameters from the request
            routing_params empty;
            if (params == nullptr)
                params = &empty;

            unsigned found{};
            routing_params match_params;

            // start looking from the root node
            if (node == nullptr)
                node = head();

            // if url.size() is 0, return the current node
            if (pos == req_url.size())
                return {node->rule_index, *params};

            // function to update the elem we found (update only if it has an index and it's smaller than the current)
            auto update_found = [&found, &match_params](std::pair<unsigned, routing_params>& ret)
            {
                if (ret.first && (!found || found > ret.first))
                {
                    found = ret.first;
                    match_params = std::move(ret.second);
                }
            };

            // if the node has an int parameter we try to match it
            if (node->param_children[(int)ParamType::INT])
            {
                char c = req_url[pos];
                if ((c >= '0' && c <= '9') || c == '+' || c == '-')
                {
                    char* eptr;
                    errno = 0;
                    long long int value = strtoll(req_url.data()+pos, &eptr, 10);
                    if (errno != ERANGE && eptr != req_url.data()+pos)
                    {
                        params->int_params.push_back(value);
                        auto ret = find(req_url, &nodes_[node->param_children[(int)ParamType::INT]], eptr - req_url.data(), params);
                        update_found(ret);
                        params->int_params.pop_back();
                    }
                }
            }

            // if the node has an uint parameter...
            if (node->param_children[(int)ParamType::UINT])
            {
                char c = req_url[pos];
                if ((c >= '0' && c <= '9') || c == '+')
                {
                    char* eptr;
                    errno = 0;
                    unsigned long long int value = strtoull(req_url.data()+pos, &eptr, 10);
                    if (errno != ERANGE && eptr != req_url.data()+pos)
                    {
                        params->uint_params.push_back(value);
                        auto ret = find(req_url, &nodes_[node->param_children[(int)ParamType::UINT]], eptr - req_url.data(), params);
                        update_found(ret);
                        params->uint_params.pop_back();
                    }
                }
            }

            // if the node has a double parameter...
            if (node->param_children[(int)ParamType::DOUBLE])
            {
                char c = req_url[pos];
                if ((c >= '0' && c <= '9') || c == '+' || c == '-' || c == '.')
                {
                    char* eptr;
                    errno = 0;
                    double value = strtod(req_url.data()+pos, &eptr);
                    if (errno != ERANGE && eptr != req_url.data()+pos)
                    {
                        params->double_params.push_back(value);
                        auto ret = find(req_url, &nodes_[node->param_children[(int)ParamType::DOUBLE]], eptr - req_url.data(), params);
                        update_found(ret);
                        params->double_params.pop_back();
                    }
                }
            }

            // if the node has a string parameter...
            if (node->param_children[(int)ParamType::STRING])
            {
                size_t epos = pos;
                for(; epos < req_url.size(); epos ++)
                {
                    if (req_url[epos] == '/')
                        break;
                }

                if (epos != pos)
                {
                    params->string_params.push_back(req_url.substr(pos, epos-pos));
                    auto ret = find(req_url, &nodes_[node->param_children[(int)ParamType::STRING]], epos, params);
                    update_found(ret);
                    params->string_params.pop_back();
                }
            }

            // if the node has a path parameter...
            if (node->param_children[(int)ParamType::PATH])
            {
                size_t epos = req_url.size();

                if (epos != pos)
                {
                    params->string_params.push_back(req_url.substr(pos, epos-pos));
                    auto ret = find(req_url, &nodes_[node->param_children[(int)ParamType::PATH]], epos, params);
                    update_found(ret);
                    params->string_params.pop_back();
                }
            }

            // for each string child
            for(auto& kv : node->children)
            {
                // we try to match it
                const std::string& fragment = kv.first;
                const Node* child = &nodes_[kv.second];

                if (req_url.compare(pos, fragment.size(), fragment) == 0)
                {
                    auto ret = find(req_url, child, pos + fragment.size(), params);
                    update_found(ret);
                }
            }

            // return what we matched
            return {found, match_params};
        }

        // add a rule's index to the rule trie
        void add(const std::string& url, unsigned rule_index)
        {
            // initial rule index is 0
            unsigned idx{0};

            const char opening_tag = wpp_settings::opening_tag;
            const char closing_tag = wpp_settings::closing_tag;

            // check through the url to get parameters
            for(unsigned i = 0; i < url.size(); i ++)
            {
                // get first char
                char c = url[i];
                // check if it's opening a parameter
                if (c == opening_tag)
                {
                    struct ParamTraits
                    {
                        ParamType type;
                        std::string name;
                    };
                    ParamTraits paramTraits[] =
                            {
                                    { ParamType::INT, {opening_tag,'i','n','t',closing_tag} },
                                    { ParamType::UINT, {opening_tag,'u','i','n','t',closing_tag} },
                                    { ParamType::DOUBLE, {opening_tag,'f','l','o','a','t',closing_tag} },
                                    { ParamType::DOUBLE, {opening_tag,'d','o','u','b','l','e',closing_tag} },
                                    { ParamType::STRING, {opening_tag,'s','t','r',closing_tag} },
                                    { ParamType::STRING, {opening_tag,'s','t','r','i','n','g',closing_tag} },
                                    { ParamType::PATH, {opening_tag,'p','a','t','h',closing_tag} },
                            };

                    // for each parameter possible
                    for(auto& x:paramTraits)
                    {
                        // if url from position i to i+parametername.size is equal to the parameter name (including closing tag)
                        if (url.compare(i, x.name.size(), x.name) == 0)
                        {
                            // if the current node of index 0 has no children of the x_type
                            if (!nodes_[idx].param_children[(int)x.type])
                            {
                                // we create a new node for this route
                                auto new_node_idx = new_node();
                                // push a new children node, get it's id (which is nodes.size()-1) and link it on the parent node's children
                                nodes_[idx].param_children[(int)x.type] = new_node_idx;
                            }
                            // the current node id is the id of the children we just added or the old children of same parameter type
                            idx = nodes_[idx].param_children[(int)x.type];
                            // advance the counter
                            i += x.name.size();
                            // stop testing parameter types
                            break;
                        }
                    }
                    // return -1 on counter to compensate for loop's i++
                    i --;
                }
                else
                {
                    // if it's not a specific parameter we create a string for it
                    // the parameter is the string's first letter
                    std::string piece(&c, 1);
                    // if the current node doesn't have a child with this name (the first letter)
                    if (!nodes_[idx].children.count(piece))
                    {
                        // we create a node for it
                        auto new_node_idx = new_node();
                        // we emplace
                        nodes_[idx].children.emplace(piece, new_node_idx);
                    }
                    // the current node is now the child (new or old)
                    idx = nodes_[idx].children[piece];
                }
            }
            // if at the end the current node already has a rule_index, it already exists (we tried to add two equal routes)
            if (nodes_[idx].rule_index)
                throw std::runtime_error("handler already exists for " + url);
            nodes_[idx].rule_index = rule_index;
        }
    private:
        void debug_node_print(Node* n, int level)
        {
            const char opening_tag = wpp_settings::opening_tag;
            const char closing_tag = wpp_settings::closing_tag;

            // for each param child
            for(int i = 0; i < (int)ParamType::MAX; i ++)
            {
                // if there is one
                if (n->param_children[i])
                {
                    // we print it
                    log_debug << std::string(2*level, ' ') /*<< "("<<n->param_children[i]<<") "*/ << std::endl;
                    switch((ParamType)i)
                    {
                        case ParamType::INT:
                            log_debug << opening_tag << "int" << closing_tag << std::endl;
                            break;
                        case ParamType::UINT:
                            log_debug << opening_tag << "uint" << closing_tag << std::endl;
                            break;
                        case ParamType::DOUBLE:
                            log_debug << opening_tag << "float" << closing_tag << std::endl;
                            break;
                        case ParamType::STRING:
                            log_debug << opening_tag << "str" << closing_tag << std::endl;
                            break;
                        case ParamType::PATH:
                            log_debug << opening_tag << "path" << closing_tag << std::endl;
                            break;
                        default:
                            log_debug << opening_tag << "ERROR" << closing_tag << std::endl;
                            break;
                    }
                    // print the child's child with more indentation
                    debug_node_print(&nodes_[n->param_children[i]], level+1);
                }
            }
            // for each string children
            for(auto& kv : n->children)
            {
                // print the letter or word
                log_debug << std::string(2*level, ' ') /*<< "(" << kv.second << ") "*/ << kv.first << std::endl;
                // print this child's child with more indentation
                debug_node_print(&nodes_[kv.second], level+1);
            }
        }

    public:
        // print the whole tree
        void debug_print()
        {
            debug_node_print(head(), 0);
        }

    private:
        // root node
        const Node* head() const
        {
            return &nodes_.front();
        }

        // root node
        Node* head()
        {
            return &nodes_.front();
        }

        // create node and return it's id
        unsigned new_node()
        {
            nodes_.resize(nodes_.size()+1);
            return nodes_.size() - 1;
        }

        // list of all nodes
        std::vector<Node> nodes_;
    };


}

#endif //WPP_TRIE_H
