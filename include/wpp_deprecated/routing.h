#pragma once

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
#include "const_str.h"
#include "logging.h"
#include "websocket.h"
#include "rule.h"
#include "trie.h"

namespace wpp
{

    // the router keeps all the rules and a pre-processed trie to find rules efficiently
    class Router
    {
    public:
        // rules is vector of pointers to rules of any kind
        Router() : rules_(2) 
        {
        }

        // new dynamic rule
        DynamicRule& new_rule_dynamic(const std::string& rule)
        {
            // create the rule object
            auto ruleObject = new DynamicRule(rule);
            // add to the rules vector and trie
            internal_add_rule_object(rule, ruleObject);
            // return it
            return *ruleObject;
        }

        // tagged rules are based on templates
        template <uint64_t N>
        typename const_str::arguments<N>::type::template rebind<TaggedRule>& new_rule_tagged(const std::string& rule)
        {
            using RuleT = typename const_str::arguments<N>::type::template rebind<TaggedRule>;
            auto ruleObject = new RuleT(rule);

            internal_add_rule_object(rule, ruleObject);

            return *ruleObject;
        }

        // the internal process of adding rules
        void internal_add_rule_object(const std::string& rule, BaseRule* ruleObject)
        {
            // add to the rule list and trie
            rules_.emplace_back(ruleObject);
            trie_.add(rule, rules_.size() - 1);

            // add a version with/without final slashes to the trie too
            // directory case: 
            //   request to `/about' url matches `/about/' rule 
            if (rule.size() > 1 && rule.back() == '/')
            {
                std::string rule_without_trailing_slash = rule;
                rule_without_trailing_slash.pop_back();
                trie_.add(rule_without_trailing_slash, RULE_SPECIAL_REDIRECT_SLASH);
            } else if (rule.size() > 1 && rule.back() != '/') {
                std::string rule_with_trailing_slash = rule;
                rule_with_trailing_slash.push_back('/');
                trie_.add(rule_with_trailing_slash, RULE_SPECIAL_REDIRECT_SLASH);
            }
        }

        // validate and optimize trie
        void validate()
        {
            // validade trie
            trie_.validate();
            // check if all rules have a handler function
            for(auto& rule:rules_)
            {
                if (rule)
				{
					auto upgraded = rule->upgrade();
					if (upgraded)
						rule = std::move(upgraded);
                    rule->validate();
				}
            }
        }

        // run the upgrade handle for a certain request
		template <typename Adaptor> 
		void handle_upgrade(const request& req, response& res, Adaptor&& adaptor)
		{
            // look for the route requested
            auto found = trie_.find(req.url);
            unsigned rule_index = found.first;

            // check if we found a valid rule
            if (!rule_index)
            {
                log_debug << "Cannot match rules " << req.url << std::endl;
                res = response(404);
                res.end();
                return;
            }

            if (rule_index >= rules_.size())
                throw std::runtime_error("Trie internal structure corrupted!");

            if (rule_index == RULE_SPECIAL_REDIRECT_SLASH)
            {
                log_info << "Redirecting to a url with trailing slash: " << req.url << std::endl;
                res = response(301);

                // TODO absolute url building
                if (req.get_header_value("Host").empty())
                {
                    res.add_header("Location", req.url + "/");
                }
                else
                {
                    res.add_header("Location", "http://" + req.get_header_value("Host") + req.url + "/");
                }
                res.end();
                return;
            }

            // if the rule we found doesn't match the method
            if ((rules_[rule_index]->get_methods() & (1<<(uint32_t)req.method)) == 0)
            {
                log_debug << "Rule found but method mismatch: " << req.url << " with " << method_name(req.method) << "(" << (uint32_t)req.method << ") / " << rules_[rule_index]->get_methods() << std::endl;
                res = response(404);
                res.end();
                return;
            }

            // matched message
            log_debug << "Matched rule (upgrade) '" << rules_[rule_index]->rule_ << "' " << (uint32_t)req.method << " / " << rules_[rule_index]->get_methods() << std::endl;

            // handle it
            // any uncaught exceptions become 500s
            try
            {
                rules_[rule_index]->handle_upgrade(req, res, std::move(adaptor));
            }
            catch(std::exception& e)
            {
                log_error << "An uncaught exception occurred: " << e.what() << std::endl;
                res = response(500);
                res.end();
                return;   
            }
            catch(...)
            {
                log_error << "An uncaught exception occurred. The type was unknown so no information was available." << std::endl;
                res = response(500);
                res.end();
                return;   
            }
		}

        void handle(const request& req, response& res)
        {
            // same as other rule (different method)
            auto found = trie_.find(req.url);

            unsigned rule_index = found.first;

            if (!rule_index)
            {
                log_debug << "Cannot match rules " << req.url << std::endl;
                res = response(404);
                res.end();
                return;
            }

            if (rule_index >= rules_.size())
                throw std::runtime_error("Trie internal structure corrupted!");

            if (rule_index == RULE_SPECIAL_REDIRECT_SLASH)
            {
                log_info << "Redirecting to a url with trailing slash: " << req.url << std::endl;
                res = response(301);

                // TODO absolute url building
                if (req.get_header_value("Host").empty())
                {
                    res.add_header("Location", req.url + "/");
                }
                else
                {
                    res.add_header("Location", "http://" + req.get_header_value("Host") + req.url + "/");
                }
                res.end();
                return;
            }

            if ((rules_[rule_index]->get_methods() & (1<<(uint32_t)req.method)) == 0)
            {
                log_debug << "Rule found but method mismatch: " << req.url << " with " << method_name(req.method) << "(" << (uint32_t)req.method << ") / " << rules_[rule_index]->get_methods() << std::endl;
                res = response(404);
                res.end();
                return;
            }

            log_debug << "Matched rule '" << rules_[rule_index]->rule_ << "' " << (uint32_t)req.method << " / " << rules_[rule_index]->get_methods() << std::endl;

            // any uncaught exceptions become 500s
            try
            {
                rules_[rule_index]->handle(req, res, found.second);
            }
            catch(std::exception& e)
            {
                log_error << "An uncaught exception occurred: " << e.what() << std::endl;
                res = response(500);
                res.end();
                return;   
            }
            catch(...)
            {
                log_error << "An uncaught exception occurred. The type was unknown so no information was available." << std::endl;
                res = response(500);
                res.end();
                return;   
            }
        }

        void debug_print()
        {
            trie_.debug_print();
        }

    private:
        std::vector<std::unique_ptr<BaseRule>> rules_;
        Trie trie_;
    };
}
