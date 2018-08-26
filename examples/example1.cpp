#include "ThreadPool.h"
#include <iostream>
#include <list>
#include <random>

int main() {

    ThreadPool threadPool(5);
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, 2000);
    std::list<int> list;
    for (int i(2); i <= 11; ++i) {
        list.push_back(i);
    }

    std::mutex outputMutex;
    std::cout << "List: ";
    for (const auto& el : list) {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    while (list.size() > 0) {
        std::list<int> newList;
        for (auto& el : list) {
            threadPool.post([&el, &newList, &distribution, &generator, &outputMutex]() {
                int timeout(distribution(generator));
                std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
                if (el * el < 100) {
                    newList.push_back(el * el);
                } else {
                    std::lock_guard<std::mutex> lock(outputMutex);
                    std::cout << "Result: " << el * el << std::endl;
                }
            });
        }
        threadPool.join();
        std::swap(list, newList);
        std::cout << "List: ";
        for (const auto& el : list) {
            std::cout << el << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}