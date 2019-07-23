#include <benchmark/benchmark.h>

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <stdio.h>
#include <wpp.h>

using namespace std;

#include <chrono>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <crow/ci_map.h>

void insert_int_container(benchmark::State& state){
    int container = state.range(0);
    int n = state.range(1);
    bool measure_insert_or_search = state.range(2);

    const string alphanum = "0123456789!@#$%^&*ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    while (state.KeepRunning()){
        state.PauseTiming();
        vector<pair<std::string, std::string>> m1;
        vector<pair<std::string, std::string>> m2;
        multimap<std::string, std::string> m3;
        unordered_multimap<std::string, std::string> m4;
        crow::ci_map m5;

        vector<string> keys;
        vector<string> values;
        vector<string> search_str;

        for (int i = 0; i < n; ++i) {
            string rnd_string_key(10,' ');
            for(unsigned int k = 0; k < 10; ++k)
            {
                rnd_string_key[k] = alphanum[rand() % alphanum.size()];
            }
            string rnd_string_value(10,' ');
            for(unsigned int k = 0; k < 10; ++k)
            {
                rnd_string_value[k] = alphanum[rand() % alphanum.size()];
            }
            string rnd_string_search(10,' ');
            for(unsigned int k = 0; k < 10; ++k)
            {
                rnd_string_search[k] = alphanum[rand() % alphanum.size()];
            }
            keys.push_back(rnd_string_key);
            values.push_back(rnd_string_value);
            search_str.push_back(rnd_string_search);
        }

        if (measure_insert_or_search) {
            state.ResumeTiming();
        }
        if (container == 0) {
            for (int i = 0; i < keys.size(); ++i) {
                (m1.push_back(make_pair(keys[i], values[i])));
            }
        } else if (container == 1) {
            for (int i = 0; i < keys.size(); ++i) {
                (m1.push_back(make_pair(keys[i], values[i])));
                (std::sort(m2.begin(),m2.end()));
            }
        } else if (container == 2) {
            for (int i = 0; i < keys.size(); ++i) {
                (m3.insert(make_pair(keys[i],values[i])));
            }
        } else if (container == 3) {
            for (int i = 0; i < keys.size(); ++i) {
                (m4.insert(make_pair(keys[i],values[i])));
            }
        } else if (container == 4) {
            for (int i = 0; i < keys.size(); ++i) {
                (m5.insert(make_pair(keys[i],values[i])));
            }
        }
        if (measure_insert_or_search) {
            state.PauseTiming();
        } else {
            state.ResumeTiming();
        }
        if (container == 0) {
            for (int i = 0; i < keys.size(); ++i) {
                benchmark::DoNotOptimize(std::find_if(m1.begin(),m1.end(),[&search_str,&i](pair<std::string, std::string> elem){return std::strcmp(search_str[i].c_str(), elem.first.c_str())==0;}));
            }
        } else if (container == 1) {
            for (int i = 0; i < keys.size(); ++i) {
                benchmark::DoNotOptimize(std::lower_bound(m2.begin(),m2.end(),search_str[i],[](pair<std::string, std::string> elem, std::string value){return std::strcmp(elem.first.c_str(), value.c_str())<0;}));
            }
        } else if (container == 2) {
            for (int i = 0; i < keys.size(); ++i) {
                auto it3 = m3.find(search_str[i]);
                if (it3!=m3.end()){
                    benchmark::DoNotOptimize(it3->first);
                }
            }
        } else if (container == 3) {
            for (int i = 0; i < keys.size(); ++i) {
                auto it4 = m4.find(search_str[i]);
                if (it4!=m4.end()){
                    benchmark::DoNotOptimize(it4->first);
                }
            }
        } else if (container == 4) {
            for (int i = 0; i < keys.size(); ++i) {
                auto it5 = m5.find(search_str[i]);
                if (it5!=m5.end()){
                    benchmark::DoNotOptimize(it5->first);
                }
            }
        }
        if (!measure_insert_or_search) {
            state.PauseTiming();
        }
        m1.clear();
        m2.clear();
        m3.clear();
        m4.clear();
        m5.clear();
        state.ResumeTiming();
    }
}

//BENCHMARK(http_parsing_test);

static void CustomArguments_insert_int_container(benchmark::internal::Benchmark* b) {
    for (int i = 0; i <= 5; ++i)
        for (int j = 8; j <= 8*8*8*8; j *= 2)
            for (int k = 0; k <= 1; k ++)
                b->Args({i, j, k});
}
//BENCHMARK(insert_int_container)->Ranges({{0, 5}, {8, 8<<10}, {0,1}});
BENCHMARK(insert_int_container)->Apply(CustomArguments_insert_int_container)->Iterations(10);

BENCHMARK_MAIN();