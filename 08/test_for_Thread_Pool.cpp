#include "Thread_Pool.hpp"


void foo1(){
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

std::string foo2(size_t k){
    return ("number of task is " + std::to_string(k));
}

struct A {};

void foo(const A&) {};

int main() {
    ThreadPool p(8);
    //test1
    try{
        auto task1 = p.exec(foo, A());
        task1.get();
        auto task2 = p.exec([]() {return 1;});
        task2.get();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    catch(std::future_error&){
        std::cout<<"Wrong 1"<<std::endl;
        return 0;
    }
    std::cout<<"OK 1"<<std::endl;
    //test2
    unsigned int start_time =  clock();
    auto t1 = p.exec(foo1);
    auto t2 = p.exec(foo1);
    auto t3 = p.exec(foo1);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    t1.get();
    t2.get();
    t3.get();
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    if (search_time > 3*CLOCKS_PER_SEC ) //summary time without threads = 6 seconds
        std::cout<<"Wrong 2"<<std::endl;
    else
        std::cout<<"OK 2"<<std::endl;
    //test3
    ThreadPool p2(2);
    auto ans1 = p2.exec(foo2, 1);
    auto ans2 = p2.exec(foo2, 2);
    auto ans3 = p2.exec(foo2, 3); //when all threads are busy then tasks will wait in queue
    auto ans4 = p2.exec(foo2, 4);
    if ((ans1.get() == "number of task is 1") && (ans2.get() == "number of task is 2")
        && (ans3.get() == "number of task is 3") && (ans4.get() == "number of task is 4"))
        std::cout<<"OK 3";
    else
        std::cout<<"Wrong 3";

    return 0;
}
