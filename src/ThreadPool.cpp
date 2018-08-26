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
            pool.tasks.pop_front();
        }

        task();
    }
}

ThreadPool::ThreadPool(size_t numThreads)
        : stop(false),
          numThreads(numThreads) {
    for(size_t i(0); i < numThreads; ++i) {
        workers.push_back(std::thread(Worker(*this)));
    }
}

ThreadPool::~ThreadPool() {
    stop = true;
    condition.notify_all();

    for (size_t i = 0; i < workers.size(); ++i) {
        if (workers[i].joinable()) {
            workers[i].join();
        }
    }
}

void ThreadPool::join() {
    stop = true;
    condition.notify_all();

    for(size_t i = 0;i<workers.size();++i) {
        if (workers[i].joinable()) {
            workers[i].join();
        }
    }

    workers.clear();
    stop = false;
    for(size_t i(0); i < numThreads; ++i) {
        workers.push_back(std::thread(Worker(*this)));
    }
}

void ThreadPool::post(std::function<void()> f) {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        tasks.push_back(std::function<void()>(f));
    }
    condition.notify_one();
}