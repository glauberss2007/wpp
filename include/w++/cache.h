//
// Created by Alan de Freitas on 25/09/17.
//

#ifndef WPP_CACHE_H
#define WPP_CACHE_H

#include "lru/lru.hpp"
#include "json.hpp"
#include <chrono>
#include <string>


namespace wpp {
    using namespace std::chrono_literals;
    using json = nlohmann::json;
    using clock = std::chrono::steady_clock;
    using time_point = clock::time_point;
    using duration = std::chrono::duration<double, std::milli>;
    class cache
    {
    public:
        struct cache_data {
            time_point _insertion_time;
            duration _time_to_live;
            json _value;

            bool operator!=(const cache_data &rhs) const{
                return ((_insertion_time != rhs._insertion_time) && (_value != rhs._value));
            }
            bool operator==(const cache_data &rhs) const{
                return ((_insertion_time == rhs._insertion_time) && (_value == rhs._value));
            }
            bool operator>(const cache_data &rhs) const{
                return ((_insertion_time > rhs._insertion_time) && (_value > rhs._value));
            }
            bool operator<(const cache_data &rhs) const{
                return ((_insertion_time < rhs._insertion_time) && (_value < rhs._value));
            }
        };

        explicit cache(const duration& time_to_live,
                            size_t capacity = 100000)
                : _base_cache(time_to_live, capacity), _default_expiration_time(time_to_live) {
        }

        bool has(string key){
            if (_base_cache.contains(key)){
                cache_data& data = _base_cache[key];
                auto elapsed = (clock::now() - data._insertion_time);
                if (std::chrono::duration_cast<duration>(elapsed) > data._time_to_live){
                    _base_cache.erase(key);
                    return false;
                } else {
                    return true;
                }

            }
            return false;
        }

        wpp::json get(string key, json default_ = ""){
            if (this->has(key)){
                return _base_cache[key]._value;
            } else {
                return default_;
            }
        }

        cache& put(string key, json value){
            _base_cache.emplace(key,cache_data{clock::now(),_default_expiration_time,value});
            return *this;
        }

        cache& put(string key, json value, duration expiration_time){
            _base_cache.emplace(key,cache_data{clock::now(),expiration_time,value});
            return *this;
        }

        cache& put(initializer_list<pair<string,json>> l){
            for (auto &&item  : l) {
                _base_cache.emplace(item.first,cache_data{clock::now(),_default_expiration_time,item.second});
            }
            return *this;
        }

        cache& put(initializer_list<pair<string,json>> l, duration expiration_time){
            for (auto &&item  : l) {
                _base_cache.emplace(item.first,cache_data{clock::now(),expiration_time,item.second});
            }
            return *this;
        }

        cache& add(string key, json value){
            if (!this->has(key)) {
                this->put(key,value);
            }
            return *this;
        }

        cache& add(string key, json value, duration expiration_time){
            if (!this->has(key)) {
                this->put(key,value,expiration_time);
            }
            return *this;
        }

        cache& increment(string key, int amount = 1){
            if (this->has(key)){
                cache_data& data = _base_cache[key];
                if (data._value.is_number()){
                    data._value = data._value.get<int>() + amount;
                }
            }
            return *this;
        }
        cache& decrement(string key, int amount = 1){
            if (this->has(key)){
                cache_data& data = _base_cache[key];
                if (data._value.is_number()){
                    data._value = data._value.get<int>() - amount;
                }
            }
            return *this;
        }
        template <typename FUNC>
        json remember(string key, FUNC func){
            if (!this->has(key)){
                this->put(key,func());
            }
            return _base_cache[key]._value;
        }

        json pull(string key){
            if (this->has(key)){
                auto temp = _base_cache[key]._value;
                this->forget(key);
                return temp;
            } else {
                return json();
            }
        }

        bool forget(string key){
            if (this->has(key)){
                _base_cache.erase(key);
                return true;
            } else {
                return false;
            }
        }

        bool erase(string key){
            if (this->has(key)){
                _base_cache.erase(key);
                return true;
            } else {
                return false;
            }
        }

        cache& flush(){
            _base_cache.clear();
            return *this;
        }

        cache& resize(size_t new_capacity){
            _base_cache.capacity(new_capacity);
            return *this;
        }

        size_t size(){
            return _base_cache.capacity();
        }

        bool empty(){
            return _base_cache.is_empty();
        }

        private:
            duration _default_expiration_time;
            LRU::TimedCache<std::string, cache_data, duration, std::hash<std::string>> _base_cache{24h,10000};
    };

}

#endif //WPP_CACHE_H
