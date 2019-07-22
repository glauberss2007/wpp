//
// Created by Alan de Freitas on 10/02/17.
//

#ifndef WPP_REGISTER_VIEW_LAMBDA_H_H
#define WPP_REGISTER_VIEW_LAMBDA_H_H

#include <string>
#include <utility>
#include <functional>
#include <tuple>

#include <boost/algorithm/string.hpp>

#include "response.h"
#include <w++>

using string_type = std::string;
using lambda_type = std::function<string_type(const string_type &)>;
using namespace std;
using namespace wpp;

wpp::json get_parameters(const string& s);
std::string csrf_token(application &app);

void register_view_lambdas(application &app) {

    ////////////////////////////////////////////////////////////////
    //                         Lambdas                            //
    ////////////////////////////////////////////////////////////////

    // return url to route
    app.lambda("route",[&app](const std::string & s) {
        return app.url_for(s);
    });

    // return url to asset
    app.lambda("asset",[&app](const std::string & s) {
        return app.asset(s);
    });

    // form field to define method
    app.lambda("method_field",[&app](const std::string & s) {
        return string("<input type=\"hidden\" name=\"_method\" value=\"") + boost::algorithm::to_upper_copy(s) + "\">";
    });

    // return link component
    app.lambda("link",[&app](const std::string & s) {
        wpp::json parameters = get_parameters(s);
        if (parameters.size() < 2) {
            return "<a href=\"" + s + "\">" + s + "</a>";
        } else {
            return "<a href=\"" + parameters[1].get<string>() + "\">" + parameters[0].get<string>() + "</a>";
        }
    });

    // return nothing
    app.lambda("comment",[&app](const std::string & s) {
        return string();
    });

    ////////////////////////////////////////////////////////////////
    //                  Lambdas with renderer                     //
    ////////////////////////////////////////////////////////////////

    // return non rendered text
    app.lambda("verbatim",[&app](const std::string & s, renderer&) {
        return s;
    });

    ////////////////////////////////////////////////////////////////
    //            Lambdas with renderer + context data            //
    ////////////////////////////////////////////////////////////////

    // return number of elements
    app.lambda("count",[](const std::string & s, renderer& r) {
        renderer_internal& ri = static_cast<renderer_internal&>(r);
        auto element = ri.ctx->ctx.get(s);
        if (element != nullptr){
            return std::to_string(element->size());
        } else {
            return string();
        }
    });

    // return csrf token field
    app.lambda("csrf_field",[&app](const std::string & s, renderer& r) {
        renderer_internal& ri = static_cast<renderer_internal&>(r);
        auto element = ri.ctx->ctx.get("_csrfmiddlewaretoken");
        if (element == nullptr){
            string csrf_token_string = csrf_token(app);
            mustache_data csrf_token_data{mustache_data::type::object};
            csrf_token_data.set("_csrfmiddlewaretoken",csrf_token_string);
            ri.ctx->ctx.push_copy(&csrf_token_data);
            return string("<input type=\"hidden\" name=\"_csrfmiddlewaretoken\" value=\"")+csrf_token_string+"\" />";
        } else {
            return string("<input type=\"hidden\" name=\"_csrfmiddlewaretoken\" value=\"")+element->string_value()+"\" />";
        }
    });

    // return csrf token field
    app.lambda("csrf_token",[&app](const std::string & s, renderer& r) {
        renderer_internal& ri = static_cast<renderer_internal&>(r);
        auto element = ri.ctx->ctx.get("_csrfmiddlewaretoken");
        if (element == nullptr){
            string csrf_token_string = csrf_token(app);
            mustache_data csrf_token_data{mustache_data::type::object};
            csrf_token_data.set("_csrfmiddlewaretoken",csrf_token_string);
            ri.ctx->ctx.push_copy(&csrf_token_data);
            return csrf_token_string;
        } else {
            return element->string_value();
        }
    });

    // print each element of a list or object
    app.lambda("foreach",[](const std::string & s, renderer& r) {
        // get parameters
        wpp::json parameters = get_parameters(s);
        // get context
        renderer_internal &ri = static_cast<renderer_internal &>(r);
        if (parameters.size() == 2 && parameters[0].is_string() && parameters[1].is_string()) {
            // if there is only text string + one string parameter, try to loop the variable
            const mustache_data *var = ri.ctx->ctx.get(parameters[1].get<string>());
            if (var && var->is_non_empty_list()) {
                string result;
                for (int i = 0; i < var->list_value().size(); ++i) {
                    const mustache_data& item = (var->list_value())[i];
                    mustache_data loopdata{mustache_data::type::object};
                    loopdata.set("is_first",(i==0 ? true : false));
                    loopdata.set("is_last",(i==var->list_value().size()-1 ? true : false));
                    loopdata.set("loop_index",to_string(i));
                    loopdata.set("loop_iteration",to_string(i+1));
                    loopdata.set("loop_remaining",to_string(var->list_value().size()-i-1));
                    loopdata.set("loop_count",to_string(var->list_value().size()));
                    ri.ctx->ctx.push(&loopdata);
                    ri.ctx->ctx.push(&item);
                    result += r(parameters[0].get<string>());
                    ri.ctx->ctx.pop();
                    ri.ctx->ctx.pop();
                }
                return result;
            }
        } else if (parameters.size() == 3  && parameters[0].is_string() && parameters[1].is_string() && parameters[2].is_number_integer()) {
            // if there is text + string parameter + int parameter, loop in chunks
            const mustache_data *var = ri.ctx->ctx.get(parameters[1].get<string>());
            if (var && var->is_non_empty_list()) {
                int chunk_size = parameters[2].get<int>();
                int n_of_chunks = var->size()/chunk_size;
                int rest_of_chunks = var->size()%chunk_size;
                string result;
                for (int i = 0; i < n_of_chunks; ++i) {
                    mustache_data chunk_list{mustache_data::type::list};
                    for (int j = 0; j < chunk_size; ++j) {
                        chunk_list.push_back(var->list_value()[i * chunk_size + j]);
                    }
                    mustache_data chunk{mustache_data::type::object};
                    chunk.set("chunk",chunk_list);
                    if (i == 0){
                        chunk.set("is_first",true);
                    } else {
                        chunk.set("is_first",false);
                    }
                    if (i == n_of_chunks+(rest_of_chunks != 0?1:0)-1){
                        chunk.set("is_last",true);
                    } else {
                        chunk.set("is_last",false);
                    }
                    chunk.set("loop_index",to_string(i));
                    chunk.set("loop_iteration",to_string(i+1));
                    chunk.set("loop_remaining",to_string(n_of_chunks+(rest_of_chunks != 0?1:0)-i-1));
                    chunk.set("loop_count",to_string(n_of_chunks+(rest_of_chunks != 0?1:0)));
                    ri.ctx->ctx.push(&chunk);
                    result += r(parameters[0].get<string>());
                    ri.ctx->ctx.pop();
                }
                if (rest_of_chunks != 0) {
                    mustache_data chunk_list{mustache_data::type::list};
                    for (int j = 0; j < rest_of_chunks; ++j) {
                        chunk_list.push_back(var->list_value()[var->size() - rest_of_chunks + j]);
                    }
                    mustache_data chunk{mustache_data::type::object};
                    chunk.set("chunk",chunk_list);
                    if (n_of_chunks == 0){
                        chunk.set("is_first",true);
                        chunk.set("is_last",true);
                    } else {
                        chunk.set("is_first",false);
                        chunk.set("is_last",true);
                    }
                    chunk.set("loop_index",to_string(n_of_chunks+1));
                    chunk.set("loop_iteration",to_string(n_of_chunks+2));
                    chunk.set("loop_remaining",to_string((int)0));
                    chunk.set("loop_count",to_string(n_of_chunks+1));
                    ri.ctx->ctx.push(&chunk);
                    result += r(parameters[0].get<string>());
                    ri.ctx->ctx.pop();
                }
                return result;
            }
        }
        // if there are no parameters or more than 3 parameters, or another error
        // return nothing
        return string();
    });


    app.lambda("if",[&app](const std::string & s, renderer& r) {
        renderer_internal& ri = static_cast<renderer_internal&>(r);
        wpp::json parameters = get_parameters(s);
        if (parameters.size() < 2) {
            return string();
        } else if (parameters.size() == 2) {
            if (parameters[0].is_string() && parameters[1].is_string()){
                const json varname = parameters[1];
                const string varnamestring = varname.get<string>();
                const auto elem = ri.ctx->ctx.get(varnamestring);
                if (elem != nullptr){
                    json text = parameters[0];
                    return r(text.get<std::string>());
                } else {
                    return string();
                }
            }
        } else if (parameters.size() == 3) {
            if (parameters[0].is_string() && parameters[1].is_string() && parameters[2].is_string()){
                const json varname1 = parameters[1];
                const json varname2 = parameters[2];
                const string varnamestring1 = varname1.get<string>();
                const string varnamestring2 = varname2.get<string>();
                const string s1 = r(string("{{") + varnamestring1 + "}}");
                const string s2 = r(string("{{") + varnamestring2 + "}}");
                if (!s1.empty() && s1 == s2){
                    json text = parameters[0];
                    return r(text.get<std::string>());
                }
            }

        }
        return string();
    });

    //app.lambda("push",[&app](const std::string & s, renderer& r) {
    //    renderer_internal& ri = static_cast<renderer_internal&>(r);
    //    vector<string> parameters;
    //    if (get_parameters(s,parameters)) {
    //        if (parameters.size() >= 2) {
    //            auto stack_iter = ri.ctx->stacks.find(parameters[0]);
    //            if (stack_iter != ri.ctx->stacks.end()){
    //                stack_iter->second += parameters[1];
    //            } else {
    //                ri.ctx->stacks[parameters[0]] = parameters[1];
    //            }
    //        }
    //    }
    //    return string();
    //});

    //app.lambda("push_once",[&app](const std::string & s, renderer& r) {
    //    renderer_internal& ri = static_cast<renderer_internal&>(r);
    //    vector<string> parameters;
    //    if (get_parameters(s,parameters)) {
    //        if (parameters.size() >= 2) {
    //            auto stack_iter = ri.ctx->stacks.find(parameters[0]);
    //            if (stack_iter != ri.ctx->stacks.end()){
    //                if (stack_iter->second.find(parameters[1]) == std::string::npos ){
    //                    stack_iter->second += parameters[1];
    //                }
    //            } else {
    //                ri.ctx->stacks[parameters[0]] = parameters[1];
    //            }
    //        }
    //    }
    //    return string();
    //});

    app.lambda("stack",[&app](const std::string & s, renderer& r) {
        renderer_internal& ri = static_cast<renderer_internal&>(r);
        auto stack_iter = ri.ctx->stacks.find(s);
        if (stack_iter != ri.ctx->stacks.end()){
            return stack_iter->second;
        } else {
            return string();
        }

    });

} // end (void register_view_lambdas(application &app))

std::string csrf_token(application &app){
    std::string unix_timestamp = to_string(std::time(nullptr));
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand0 generator(seed);
    string random_number = to_string(generator());
    std::random_device rd;
    string total;
    if (rd.entropy() > 0){
        string real_random_number = to_string(rd());
        total = unix_timestamp + random_number + real_random_number;
    } else {
        total = unix_timestamp + random_number;
    }
    // digest the id
    return app.digest(total);
}

wpp::json get_parameters(const string& s){
    const std::size_t start = 0;
    bool the_text_started_with_an_opening = s.substr(start,1) == "(";
    if (!the_text_started_with_an_opening){
        return wpp::json();
    } else {
        std::size_t opening_parameter = start;
        std::size_t closing_parameter = s.find(")",opening_parameter+1);
        std::size_t intermediate_opening = s.find("(",opening_parameter+1);
        // find brackets
        bool we_closed_an_internal = intermediate_opening < closing_parameter;
        while (we_closed_an_internal) {
            closing_parameter = s.find(")",closing_parameter+1);
            intermediate_opening = s.find("(",intermediate_opening+1);
            we_closed_an_internal = intermediate_opening < closing_parameter;
        }
        // look for json inside brackets
        const std::string paramstr = string("[") + s.substr(opening_parameter+1,closing_parameter-opening_parameter-1) + string("]");
        wpp::json param = wpp::json::parse(paramstr);
        param.insert(param.begin(),s.substr(closing_parameter+1));
        return param;
    }
}

#endif //WPP_REGISTER_VIEW_LAMBDA_H_H
