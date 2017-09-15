#include "thread_pool.h"
#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/range/irange.hpp>

#include <vector>
#include <chrono>
#include <thread>
#include <random>

#include <iostream>
#include "termcolor/termcolor.hpp"

int main() {
    std::cout << termcolor::on_yellow << termcolor::bold << "Thread Pool"
              << termcolor::reset << std::endl;

    std::cout << termcolor::bold << termcolor::underline << "Slepping Threads" << termcolor::reset << std::endl;
    {
        ThreadPool pool(std::thread::hardware_concurrency());
        std::vector<std::future<int> > results;

        const int number_of_jobs = 2;

        for (int i = 0; i < number_of_jobs; ++i) {
            results.emplace_back(
                    pool.enqueue([i] {
                        std::cout << "hello " << i << std::endl;
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        std::cout << "world " << i << std::endl;
                        return i * i;
                    })
            );
        }

        for (auto &&result: results) {
            std::cout << result.get() << ' ';
        }
        std::cout << std::endl;
    }

    std::cout << termcolor::on_yellow << termcolor::bold << "Interleaved Evolutionary Algorithm"
              << termcolor::reset << std::endl;


    std::cout << termcolor::bold << termcolor::underline << "Evaluation Functions" << termcolor::reset << std::endl;
    {
        ThreadPool pool(std::thread::hardware_concurrency());

        auto print_container = [](auto &container) {
            for (auto &&item : container) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        };

        auto evaluation_function = [](double &x) {
            return x * x;
        };

        const int population_size = 100;
        using individual = double;

        // Initial population
        std::vector<individual> population(population_size);
        std::default_random_engine generator((int) std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<double> distribution(0.0, 10.0);
        boost::generate(population,
                        [&generator, &distribution]() { return distribution(generator); });

        // Generation 0
        // Population
        std::cout << termcolor::underline << "Current population" <<  termcolor::reset << std::endl;
        print_container(population);

        // Tournament candidates (not in parallel)
        const int parents_per_child = 2;
        const int candidates_per_tournament = 2;
        std::vector<size_t> tournament_candidates(population_size * parents_per_child * candidates_per_tournament);
        std::uniform_int_distribution<size_t> tournament_distribution(0, population_size - 1);
        boost::generate(tournament_candidates, [&generator, &tournament_distribution]() { return tournament_distribution(generator); });
        std::cout << termcolor::underline << "Parent candidates" << termcolor::reset << std::endl;
        print_container(tournament_candidates);

        for (int i = 0; i < population_size; ++i) {
            if (boost::find(tournament_candidates,i) == tournament_candidates.end()){
                std::cout << "Parent " << i << " is not even a candidate" << std::endl;
            }
        }

        // Push evaluation to thread pool / (In practice we will be also getting child evaluation from the last iteration)
        std::vector<std::future<double>> results(population_size);
        for (auto &&parent : tournament_candidates) {
            if (!results[parent].valid()){
                results[parent] = pool.enqueue([&evaluation_function, &population, &parent] {
                    return evaluation_function(population[parent]);
                });
            }
        }

        // Push tournaments to thread pool / Get evaluation results from the pool
        // Each tournament round waits for the evaluation of 2 parents
        std::vector<double> population_fitness(population_size,0.0);
        std::vector<std::future<size_t>> tournament_results(population_size*parents_per_child);

        for (int i = 0; i < population_size * parents_per_child; i++) {
            tournament_results[i] = pool.enqueue([&population_fitness,i,&tournament_candidates,&results] {
                int first_candidate = i * parents_per_child;
                const std::vector<size_t> candidate_positions(tournament_candidates.begin()+first_candidate,tournament_candidates.begin()+first_candidate+candidates_per_tournament);
                std::vector<size_t> candidate_fitness(parents_per_child);
                for (int j = 0; j < candidate_positions.size(); ++j) {
                    if (results[candidate_positions[j]].valid()){
                        population_fitness[candidate_positions[j]] = results[candidate_positions[j]].get();
                    }
                    candidate_fitness[j] = population_fitness[candidate_positions[j]];
                }
                return candidate_positions[boost::max_element(candidate_fitness) - candidate_fitness.begin()];
            });
        }

        std::cout << termcolor::underline << "Current population fitness" << termcolor::reset << std::endl;
        {
            double sum = 0;
            int valid_f = 0;
            for (int i = 0; i < population_size; ++i) {
                auto &&item = population_fitness[i];
                std::cout << i << ":" << population[i] << ":fx(" << item << ") ";
                sum += item;
                valid_f += item != 0;
            }
            std::cout << std::endl;
            std::cout << "Average fitness: " << termcolor::on_green << sum/valid_f << termcolor::reset << std::endl;
        }

        // In practice we would inserting here the survival selection in the process as well
        // We would only generate the children that are candidates to survival selection (saving time once more)

        // Push child generation to thread pool / get tournament results from the pool
        // Each child generation waits for two tournament results between two parents
        std::vector<std::future<individual>> children_generation_results(population_size);
        std::vector<size_t> parent_indexes(population_size*parents_per_child);

        for (int i = 0; i < population_size; ++i) {
            children_generation_results[i] = pool.enqueue([&tournament_results,i,&population,&parent_indexes] {
                for (int j = 0; j < parents_per_child; ++j) {
                    parent_indexes[i*candidates_per_tournament+j] = tournament_results[i*candidates_per_tournament+j].get();
                }
                return (population[parent_indexes[i*parents_per_child]] + population[parent_indexes[i*parents_per_child+1]])/2;
            });
        }

        std::cout << termcolor::underline << "Parent indexes" << termcolor::reset << std::endl;
        print_container(parent_indexes);

        // Push child evaluation to thread pool / get children generation from the pool
        std::vector<individual> children(population_size);
        std::vector<std::future<double>> children_evaluation_results(population_size);

        for (int i = 0; i < population_size; ++i) {
            children_evaluation_results[i] = pool.enqueue([i, &evaluation_function, &children, &children_generation_results] {
                children[i] = children_generation_results[i].get();
                return evaluation_function(children[i]);
            });
        }

        std::cout << termcolor::underline << "Children" <<  termcolor::reset << std::endl;
        print_container(children);

        // Get children fitness
        // (in practice we would be pushing the next tournament or selection procedure)
        std::vector<double> children_fitness(population_size);
        for (int i = 0; i < population_size; ++i) {
            children_fitness[i] = children_evaluation_results[i].get();
        }

        std::cout << termcolor::underline << "Children fitness" << termcolor::reset << std::endl;
        {
            double sum = 0;
            int valid_f = 0;
            for (int i = 0; i < population_size; ++i) {
                auto &&item = children_fitness[i];
                std::cout << i << ":" << population[i] << ":fx(" << item << ") ";
                sum += item;
                valid_f += item != 0;
            }
            std::cout << std::endl;
            std::cout << "Average fitness: " << termcolor::on_green << sum/valid_f << termcolor::reset << std::endl;
        }

    }


    return 0;
}
