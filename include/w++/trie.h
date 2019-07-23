//
// Created by Alan de Freitas on 24/06/17.
//

#ifndef WPP_TRIE_H
#define WPP_TRIE_H

#include <cstdint>
#include <utility>
#include <tuple>
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <vector>
#include <string>
#include <regex>
#include <array>

#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
// #include "utils/logging.h"
#include "methods.h"
#include "route_properties.h"

namespace wpp {

    using namespace utils;

    const int TREAT_FOLDER_ALSO_AS_RESOURCE = 1;

    using boost::optional;

    // trie data structure
    class Trie {
        public:


            // trie nodes
            struct Node {
                // each rule has an index
                // bool represents a route for these methods
                std::array<unsigned*,number_of_methods()> rule_index;

                // an array of indexes of children according to parameter type -> number_of_ParamType parameters (number of each parameter)
                // these are only regex children
                struct child_properties {
                    std::regex formula;
                    ParamType type;
                    unsigned idx;
                    std::string name;
                };

                // regex children
                std::vector<child_properties> param_children{};
                // optional regex children
                std::vector<child_properties> optional_param_children{};
                // and an unordered map of children (that can be found by their name) that are not parameters
                std::unordered_map<std::string, unsigned> children;

            };

            // trie has only a vector of nodes
            Trie() : nodes_(1) {}

        public:
            // find a node according to that request url
            std::tuple<bool, unsigned, routing_params> find(const std::string &req_url, method l = method::get) const {

                // what we will return
                unsigned current_idx{0};
                routing_params match_params;

                typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
                boost::char_separator<char> sep{"/"};
                tokenizer tok{req_url, sep};
                bool fail_to_find_any_node = false;
                vector<string> tokens(tok.begin(),tok.end());

                // for each token
                for (vector<string>::iterator tokenIterator = tokens.begin(); tokenIterator != tokens.end() && !fail_to_find_any_node; ++tokenIterator) {
                    const auto &t = *tokenIterator;
                    bool a_node_was_found_in_this_iteration = false;
                    bool this_is_the_last_token = tokenIterator == tokens.end()-1;

                    // try to find token it on simple string children
                    auto child_it = nodes_[current_idx].children.find(t);
                    // if we could find a simple child
                    auto we_could_find_a_simple_child = child_it != nodes_[current_idx].children.end();
                    if (we_could_find_a_simple_child) {
                        // we change the current node
                        current_idx = child_it->second;
                        // if this is the last token and the child has a route on the method requested
                        if (this_is_the_last_token && nodes_[current_idx].rule_index[(int)l] != nullptr){
                            // we return a struct with this node
                            return {true, *nodes_[current_idx].rule_index[(int) l], match_params};
                        }
                        a_node_was_found_in_this_iteration = true;
                    }

                    if (!a_node_was_found_in_this_iteration) {
                        auto& regex_children = nodes_[current_idx].param_children;
                        for (auto &&param_child : regex_children) {
                            a_node_was_found_in_this_iteration = true;
                            if (!std::regex_match(t, param_child.formula)) {
                                a_node_was_found_in_this_iteration = false;
                            }
                            if (a_node_was_found_in_this_iteration) {
                                match_params.parameter_name.push_back(param_child.name);
                                match_params.parameter_trait.push_back(param_child.type);
                                match_params.parameter_value.push_back(t);
                                current_idx = param_child.idx;
                                auto child_has_a_route = nodes_[current_idx].rule_index[(int) l] != nullptr;
                                if (this_is_the_last_token &&
                                        child_has_a_route) {
                                    return {true, *nodes_[current_idx].rule_index[(int) l], match_params};
                                } else {
                                    break;
                                }
                            }
                        }
                    }

                    if (!a_node_was_found_in_this_iteration) {
                        auto& optional_regex_children = nodes_[current_idx].optional_param_children;
                        for (auto &&optional_param_child : optional_regex_children) {
                            // assume we will find the node here
                            a_node_was_found_in_this_iteration = true;
                            // try to match all its regexes
                            if (!std::regex_match(t, optional_param_child.formula)) {
                                a_node_was_found_in_this_iteration = false;
                            }
                            if (a_node_was_found_in_this_iteration) {
                                // push parameters
                                match_params.parameter_name.push_back(optional_param_child.name);
                                match_params.parameter_trait.push_back(optional_param_child.type);
                                match_params.parameter_value.push_back(t);
                                current_idx = optional_param_child.idx;
                                // if this is the last token and the child has a route on the method requested
                                if (this_is_the_last_token &&
                                    nodes_[current_idx].rule_index[(int) l] != nullptr) {
                                    // we return a struct with this node
                                    return {true, *nodes_[current_idx].rule_index[(int) l], match_params};
                                } else {
                                    break;
                                }
                            }
                        }
                    }

                    // while none of the optional children match but there is still at least one optional
                    auto current_node_has_optional_children = !nodes_[current_idx].optional_param_children.empty();
                    auto optional_child_is_only_hope = this_is_the_last_token && current_node_has_optional_children;
                    if (!a_node_was_found_in_this_iteration && optional_child_is_only_hope){
                        auto empty = optional<string>{};
                        auto& optional_param_child = nodes_[current_idx].optional_param_children[0];
                        match_params.parameter_name.push_back(optional_param_child.name);
                        match_params.parameter_trait.push_back(optional_param_child.type);
                        match_params.parameter_value.push_back(empty);
                        current_idx = optional_param_child.idx;
                        auto current_node_has_a_route = nodes_[current_idx].rule_index[(int) l] != nullptr;
                        if (!this_is_the_last_token && current_node_has_a_route) {
                            a_node_was_found_in_this_iteration = true;
                        } else {
                            if (current_node_has_a_route) {
                                return {true, *nodes_[current_idx].rule_index[(int) l], match_params};
                            } else {
                                a_node_was_found_in_this_iteration = false;
                                fail_to_find_any_node = true;
                                break;
                            }
                        }
                    }

                    if (!a_node_was_found_in_this_iteration) {
                        fail_to_find_any_node = true;
                        return {false,0,match_params};
                    }
                }

                // when we run out of tokens
                // if we failed to find a node or the node to which we are pointing is not valid
                if (fail_to_find_any_node || nodes_[current_idx].rule_index[(int) l] == nullptr){
                    return {false,0,match_params};
                } else {
                    return {true, *nodes_[current_idx].rule_index[(int) l], match_params};
                }

            }

            // add a rule's index to the rule trie
            void add(const route_properties route, unsigned rule_index) {
                // initial rule index is 0
                unsigned current_idx{0};

                for (int i = 0; i < route._uri_members.size(); ++i) {
                    if (route._uri_member_regex_type[i] == uri_member_type::simple_string){
                        auto it = nodes_[current_idx].children.find(route._uri_members[i]);
                        if (it != nodes_[current_idx].children.end()){
                            current_idx = it->second;
                        } else {
                            auto new_node_idx = new_node();
                            nodes_[current_idx].children[route._uri_members[i]] = new_node_idx;
                            current_idx = new_node_idx;
                        }
                    } else {
                        auto new_node_idx = new_node();
                        auto it = std::find(route._uri_parameter_names.begin(),route._uri_parameter_names.end(),route._uri_members[i]);
                        if (it != route._uri_parameter_names.end()){
                            auto pos = it - route._uri_parameter_names.begin();
                            std::string formula_string;
                            for (int j = 0; j < route._uri_member_regexes[pos].size(); ++j) {
                                if (j != route._uri_member_regexes[pos].size() - 1){
                                    formula_string += std::string("(?=") + route._uri_member_regexes[pos][j] + std::string(")");
                                } else {
                                    formula_string += std::string("(") + route._uri_member_regexes[pos][j] + std::string(")");
                                }
                            }
                            Node::child_properties c = Node::child_properties({std::regex(formula_string), route._uri_member_data_type[pos], new_node_idx, route._uri_parameter_names[pos]});
                            if (route._uri_member_regex_type[i] == uri_member_type::regex){
                                nodes_[current_idx].param_children.push_back(c);
                                current_idx = nodes_[current_idx].param_children.back().idx;
                            } else {
                                nodes_[current_idx].optional_param_children.push_back(c);
                                current_idx = nodes_[current_idx].optional_param_children.back().idx;
                            }
                        } else {
                            std::cerr << "Could not find the parameter " << route._uri_members[i] << std::endl;
                            return;
                        }
                    }
                }

                for (auto &&method : route._methods) {
                    nodes_[current_idx].rule_index[((int)method)] = new unsigned (rule_index);
                }

            }

        private:
            void debug_node_print(Node *n, int level) {
                for (auto &&child : n->children) {
                    std::cout << std::string(level, ' ') << "/" << child.first << std::endl;
                    debug_node_print(&nodes_[child.second], level + child.first.length() + 1);
                }
                for (auto &&child : n->param_children) {
                    std::string typestr = paramtype_to_string(child.type);
                    std::cout << std::string(level, ' ') << "/" << "{" << typestr << ": " << child.name << "}" << std::endl;
                    debug_node_print(&nodes_[child.idx], child.name.length() + typestr.length() + level + 5);
                }
                for (auto &&child : n->optional_param_children) {
                    std::string typestr = "Optional " + paramtype_to_string(child.type);
                    std::cout << std::string(level, ' ') << "/" << "{" << typestr << ": " << child.name << "}" << std::endl;
                    debug_node_print(&nodes_[child.idx], child.name.length() + typestr.length() + level + 5);
                }
            }

        public:
            // print the whole tree
            void debug_print() {
                for (int i = 0; i < number_of_methods(); ++i) {
                    if (head()->rule_index[i] != nullptr){
                        std::cout << "/" << std::endl;
                        break;
                    }
                }
                debug_node_print(head(), 1);
            }

        private:
            // root node
            const Node *head() const {
                return &nodes_.front();
            }

            // root node
            Node *head() {
                return &nodes_.front();
            }

            // create node and return it's id
            unsigned new_node() {
                nodes_.resize(nodes_.size() + 1);
                return nodes_.size() - 1;
            }

            // list of all nodes
            std::vector<Node> nodes_;
    };


}

#endif //WPP_TRIE_H
