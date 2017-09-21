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
#include "utils/logging.h"
#include "methods.h"
#include "route_properties.h"

namespace wpp {

    using namespace utils;

    const int TREAT_FOLDER_ALSO_AS_RESOURCE = 1;



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

                // for each token
                for (const auto &t : tok) {
                    // try to find it on simple children
                    auto child_it = nodes_[current_idx].children.find(t);

                    // if we could find a child
                    if (child_it != nodes_[current_idx].children.end()) {
                        current_idx = child_it->second;
                    } else {
                        // for each regex child
                        bool found = false;
                        for (auto &&param_child : nodes_[current_idx].param_children) {
                            // try to match all its regexes
                            found = true;
                            if (!std::regex_match(t, param_child.formula)){
                                found = false;
                            }
                            if (found){
                                match_params.parameter_name.push_back(param_child.name);
                                match_params.parameter_trait.push_back(param_child.type);
                                match_params.parameter_value.push_back(t);
                                current_idx = param_child.idx;
                                break;
                            }
                        }
                        if (!found){
                            // we try optional regexes
                            // for each optional regex child
                            for (auto &&optional_param_child : nodes_[current_idx].optional_param_children) {
                                // try to match all its regexes
                                bool found = true;
                                if (!std::regex_match(t, optional_param_child.formula)){
                                    found = false;
                                }
                                if (found){
                                    match_params.parameter_name.push_back(optional_param_child.name);
                                    match_params.parameter_trait.push_back(optional_param_child.type);
                                    match_params.parameter_value.push_back(t);
                                    current_idx = optional_param_child.idx;
                                }
                            }
                            // if none of the optional children match but there are optional
                            if (!found && !nodes_[current_idx].optional_param_children.empty()){
                                // we try going through an optional anyway
                                auto& optional_param_child = nodes_[current_idx].optional_param_children[0];
                                match_params.parameter_name.push_back(optional_param_child.name);
                                match_params.parameter_trait.push_back(optional_param_child.type);
                                match_params.parameter_value.push_back(t);
                                current_idx = optional_param_child.idx;
                                found = true;
                            }
                        }

                    }
                }

                // when we run out of tokens
                if (nodes_[current_idx].rule_index[(int)l] != nullptr ) {
                     return {true,*nodes_[current_idx].rule_index[(int)l],match_params};
                } else {
                     return {false,0,match_params};
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
                            log::critical << "Could not find the parameter " << route._uri_members[i] << std::endl;
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
                    log::debug << std::string(level, ' ') << "/" << child.first << std::endl;
                    debug_node_print(&nodes_[child.second], level + child.first.length() + 1);
                }
                for (auto &&child : n->param_children) {
                    std::string typestr = paramtype_to_string(child.type);
                    log::debug << std::string(level, ' ') << "/" << "{" << typestr << ": " << child.name << "}" << std::endl;
                    debug_node_print(&nodes_[child.idx], child.name.length() + typestr.length() + level + 5);
                }
                for (auto &&child : n->optional_param_children) {
                    std::string typestr = "Optional " + paramtype_to_string(child.type);
                    log::debug << std::string(level, ' ') << "/" << "{" << typestr << ": " << child.name << "}" << std::endl;
                    debug_node_print(&nodes_[child.idx], child.name.length() + typestr.length() + level + 5);
                }
            }

        public:
            // print the whole tree
            void debug_print() {
                for (int i = 0; i < number_of_methods(); ++i) {
                    if (head()->rule_index[i] != nullptr){
                        log::debug << "/" << std::endl;
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
