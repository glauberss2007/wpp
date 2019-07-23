//
// Created by Alan de Freitas on 15/11/2017.
//

#ifndef WPP_GUARD_H
#define WPP_GUARD_H

#include "request.h"

namespace wpp {

    class guard {
        protected:
            // The currently authenticated user.
            json _user{nullptr};
            // The user provider implementation.
            // user_provider provider;
            // The guard callback that generates a user in json format
            std::function<wpp::json(wpp::request&)> _callback;
            // The request instance.
            wpp::request& _request;

        public:
            using self_t = guard;

            guard(std::function<wpp::json(wpp::request&)> callback, wpp::request& request_) : _callback(callback), _request(request_){
                _request.auth = this;
                this->_user = _callback(_request);
            };

            // Determine if the current user is authenticated.
            json authenticate()
            {
                if (!this->_user.is_null()){
                    return this->_user;
                } else {
                    return json(nullptr);
                }
            }

            // Determine if the current user is authenticated.
            bool check()
            {
                return !this->_user.is_null();
            }

            // Determine if the current user is a guest.
            bool guest()
            {
                return !this->check();
            }

            // Get the ID for the currently authenticated user.
            json id()
            {
                if (this->check()) {
                    return this->_user["id"];
                }
                return json{nullptr};
            }

            // Set the current user
            self_t& set_user(json __user)
            {
                this->_user = __user;
                return *this;
            }

            // Get the currently authenticated user.
            json user(){
                if (!this->_user.is_null()) {
                    return this->_user;
                }
                this->_user = this->_callback(_request);
                return this->_user;
            }

            // Validate a user's credentials.
            //bool validate(json __user){
            //    user s = this->_callback(credentials);
            //    return !user.is_null();
            //}

            // Set the current request instance.
            self_t& set_request(wpp::request __request)
            {
                this->_request = __request;
                return *this;
            }

            bool has_role(string name){
                return has_role({name});
            }

            bool has_role(vector<string> names){
                if (this->check()) {
                    if (this->_user.count("role")){
                        for (string& name: names){
                            boost::algorithm::trim(name);
                            if (this->_user["role"].is_string()){
                                if (this->_user["role"].get<string>() == name){
                                    return true;
                                }
                            } else if (this->_user["role"].is_array()){
                                for (json& r: this->_user["role"]){
                                    if (r.is_string()){
                                        if (r.get<string>() == name){
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                return false;
            }

            bool has_permission(string name){
                return has_permission({name});
            }

            bool has_permission(vector<string> names){
                if (this->check()) {
                    if (this->_user.count("permission")){
                        for (string& name: names) {
                            boost::algorithm::trim(name);
                            if (this->_user["permission"].is_string()) {
                                if (this->_user["permission"].get<string>() == name) {
                                    return true;
                                }
                            } else if (this->_user["permission"].is_array()) {
                                for (json &perm: this->_user["permission"]) {
                                    if (perm.is_string()) {
                                        if (perm.get<string>() == name) {
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                return false;
            }

    };
}


#endif //WPP_GUARD_H
