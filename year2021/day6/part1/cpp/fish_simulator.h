//
// Created by hawk on 18.06.22.
//

#ifndef ADVENT_OF_CODE_FISH_SIMULATOR_H
#define ADVENT_OF_CODE_FISH_SIMULATOR_H

#include <vector>
#include <iostream>
#include <array>
#include <thread>
#include <future>

const unsigned int daysBeforeFirstBirth = 8;
const unsigned int daysBeforeNextBirth = 6;

class fish {

public:
    static std::size_t count_fishes(unsigned int days_before_first_birth, unsigned int days_to_live) {
        std::size_t result = 0;
        result = (days_to_live >= (days_before_first_birth + 1)) ? 1 : 0;
        if (result == 0) {
            return result;
        }
        auto remaining_days = days_to_live - (days_before_first_birth + 1);

        auto div = remaining_days / (daysBeforeNextBirth + 1);
        if (div < 1) {
            return result;
        }
        result += div;

        result += fish::count_fishes(daysBeforeFirstBirth, remaining_days);    // children of the first child

        for (auto birth = 0; birth < div; birth++) {
            result += fish::count_fishes(daysBeforeFirstBirth,
                                         remaining_days - (daysBeforeNextBirth + 1) * (birth + 1));
        }
        return result;
    }

    static void thread_count_fishes(unsigned int days_before_first_birth, unsigned int days_to_live,
                                    std::promise<std::size_t> &&result_count_fishes) {

        result_count_fishes.set_value(count_fishes(days_before_first_birth, days_to_live));
    }
};

struct thread_pool_item{
    std::future<std::size_t> count_new_born_fishes;
    std::thread worker_thread;
    unsigned long count_start_fishes;
};

class fish_simulator {
    std::vector<unsigned int> _fishes;
public:
    explicit fish_simulator(const std::vector<unsigned int> &init_data) {
        _fishes = init_data;
    }

    std::size_t simulate(unsigned int days_to_live) {
        std::size_t result = 0;
        std::vector<thread_pool_item> thread_pool;

        for (unsigned int start_day = 1; start_day < daysBeforeNextBirth; start_day++) {
            unsigned int count = std::count(_fishes.begin(), _fishes.end(), start_day);

            if (count > 0) {
                std::promise<std::size_t> prms;
                thread_pool.emplace_back( thread_pool_item {
                        prms.get_future(),
                        std::thread(fish::thread_count_fishes, start_day, days_to_live, std::move(prms)),
                        count
                } );


                //auto created = fish::count_fishes(start_day, rounds) * count + count;
                //result += created;
            }
        }

        for(auto& item : thread_pool ) {
            item.worker_thread.join();
        }

        for(auto& item : thread_pool ) {
            result += item.count_new_born_fishes.get() * item.count_start_fishes + item.count_start_fishes;
        }

        return result;

    }
};


#endif //ADVENT_OF_CODE_FISH_SIMULATOR_H
