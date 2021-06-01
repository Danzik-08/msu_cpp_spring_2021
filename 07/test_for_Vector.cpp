#include "Vector.hpp"

int main(){
    //test1
    Vector<char> x(10);
    if ((x.size() == 10) && (x.capacity() == 10))
        std::cout<<"OK 1"<<std::endl;
    else
        std::cout<<"Wrong 1"<<std::endl;
    //test2
    x[0] = 'a'; x[8] = 'b'; x[8] = 'c';
    if ((x[0] == 'a') && (x[8] == 'c'))
        std::cout<<"OK 2"<<std::endl;
    else
        std::cout<<"Wrong 2"<<std::endl;
    //test3
    x.push_back('d');
    if ((x[10] == 'd') && (x.size() == 11) && (x.capacity() == 22))
        std::cout<<"OK 3"<<std::endl;
    else
        std::cout<<"Wrong 3"<<std::endl;
    //test4
    x.pop_back();
    if ((x.size() == 10) && (x.capacity() == 22))
        std::cout<<"OK 4"<<std::endl;
    else
        std::cout<<"Wrong 4"<<std::endl;
    //test5
    x.emplace_back('e');
    if ((x[10] == 'e') && (x.size() == 11) && (x.capacity() == 22))
        std::cout<<"OK 5"<<std::endl;
    else
        std::cout<<"Wrong 5"<<std::endl;
    //test6
    x.clear();
    if (x.empty())
        std::cout<<"OK 6"<<std::endl;
    else
        std::cout<<"Wrong 6"<<std::endl;
    //test7
    x.resize(21);
    x.push_back('0');
    if ((x.size() == 22) && (x.capacity() == 42))
        std::cout<<"OK 7"<<std::endl;
    else
        std::cout<<"Wrong 7"<<std::endl;
    //test8
    x.reserve(x.size());
    if (x.size() == x.capacity())
        std::cout<<"OK 8"<<std::endl;
    else
        std::cout<<"Wrong 8"<<std::endl;
    //test9
    x.resize(4);
    x[0] = 'x'; x[1] = 'y'; x[2] = 'z'; x[3] = 'w';
    std::string ans = "";
    for (auto it = x.begin(); it != x.end(); ++it)
        ans += *it;
    if (ans == "xyzw")
        std::cout<<"OK 9"<<std::endl;
    else
        std::cout<<"Wrong 9"<<std::endl;
    //test10
    ans = "";
    for (auto it = x.rbegin(); it != x.rend(); ++it)
        ans += *it;
    if (ans == "wzyx")
        std::cout<<"OK 10"<<std::endl;
    else
        std::cout<<"Wrong 10"<<std::endl;
    //test11
    x.clear();
    char h = 'h';
    x.push_back(std::move(h));
    if (x[0] == 'h')
        std::cout<<"OK 11"<<std::endl;
    else
        std::cout<<"Wrong 11"<<std::endl;
    return 0;
}
