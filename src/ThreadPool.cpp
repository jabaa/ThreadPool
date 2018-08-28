#include "ThreadPool.h"

void Worker::operator()() {
    std::function<void()> task;
    while (true)
    {
        {
            std::unique_lock<std::mutex> lock(pool.queueMutex);

            while (!pool.stop && pool.tasks.empty()) {
                pool.condition.wait(lock);
            }

            if (pool.stop && pool.tasks.empty()) {
                return;
            }

            task = pool.tasks.front();
            pool.tasks.pop();
        }

        task();
    }
}

ThreadPool::ThreadPool(size_t numThreads)
        : stop(false),
          numThreads(numThreads) {
    for (size_t i(0); i < numThreads; ++i) {
        threads.emplace_back(Worker(*this));
    }
}

ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all();

    for (size_t i = 0; i < threads.size(); ++i) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }
}

void ThreadPool::join() {
    stop = true;
    condition.notify_all();

    for (size_t i = 0; i < threads.size();++i) {
        if (threads[i].joinable()) {
            threads[i].join();
        }
    }

    threads.clear();
    stop = false;
    for (size_t i(0); i < numThreads; ++i) {
        threads.emplace_back(Worker(*this));
    }
}

void ThreadPool::post(std::function<void()> f) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.emplace(f);
    }
    condition.notify_one();
}
