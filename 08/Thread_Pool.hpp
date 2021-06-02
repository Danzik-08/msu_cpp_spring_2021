#pragma once
#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <chrono>
#include <queue>
#include <string>
#include <ctime>


class ThreadPool{

    std::queue <void*> Queue;
    std::condition_variable next;
    bool work = true;
    std::mutex m; //mutex for queue
    size_t Size = 0; //number of unsolved tasks
    size_t poolSize;
    std::mutex cv; //mutex for condition
    void process(size_t i);
    std::vector <std::thread> threads;

public:

    ThreadPool(size_t poolSize = std::thread::hardware_concurrency()){
        this->poolSize = poolSize;
        for (size_t i(0); i < poolSize; i++)
            this->threads.push_back(std::thread (&ThreadPool::process, this, i));
    }

    ~ThreadPool(){
        //try to end all threads before ~ThreadPool() finished
        this->m.lock();
        this->work = false;
        this->m.unlock();
        this->next.notify_all();
        for (size_t i(0); i < (this->poolSize); i++)
            if (this->threads[i].joinable())
        	this->threads[i].join();
    }

    //it is some incorrect for ThreadPool to use copy/move constructor or operator=
    ThreadPool(const ThreadPool& other){
        for (size_t i(0); i < poolSize; i++)
            this->threads.push_back(std::thread (&ThreadPool::process, this, i));
    };
    ThreadPool(ThreadPool&& other) noexcept{
        for (size_t i(0); i < poolSize; i++)
            this->threads.push_back(std::thread (&ThreadPool::process, this, i));
    };
    ThreadPool& operator=(const ThreadPool& other){
        for (size_t i(0); i < poolSize; i++)
            this->threads.push_back(std::thread (&ThreadPool::process, this, i));
        return (*this);
    };
    ThreadPool& operator=(ThreadPool&& other) noexcept{
        for (size_t i(0); i < poolSize; i++)
            this->threads.push_back(std::thread (&ThreadPool::process, this, i));
        return (*this);
    };

    template <class Func, class... Args>
    auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>;
};

#include "Thread_Pool.tpp"
