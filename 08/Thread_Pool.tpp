#include "Thread_Pool.hpp"


void ThreadPool::process(size_t i){
    while (this->work){
        {
            std::unique_lock<std::mutex> lk(this->cv);
            while ((this->Size == 0) && (this->work))
                this->next.wait(lk);
        }

        this->m.lock();
        if (this->Size == 0){
            this->m.unlock();
            continue;
        }
        this->Size -= 1;
        auto task = ((std::future<void>*)this->Queue.front());
        (this->Queue).pop();
        this->m.unlock();

        if ((*task).valid()) //may be task was done from main before from that thread
            (*task).wait();
    }
}

template <class Func, class... Args>
auto ThreadPool::exec(Func func, Args... args) -> std::future<decltype(func(args...))>{
    auto f = std::async(std::launch::deferred, func, args...);
    this->m.lock();
    this->Queue.push(&f);
    this->Size += 1;
    this->next.notify_one();
    this->m.unlock();
    return f;
}
