#include<cassert>

#include<stdio.h>

#include<iostream>

#include<fstream>

#include<thread>

#include<pthread.h>

#include<string>

#include<functional>

#include"SortBinFile.h"

#include"HelpFunctions.h"


void DefaultTest(void) {
    std::mutex mutex_;
    std::ifstream file;
    uint64_t * mem_1 = new uint64_t[LEN];
    uint64_t * mem_2 = new uint64_t[LEN];
    size_t len_1 = 0, len_2 = 0, last_in_queu = 0, last_readed_in_queu = 0;
    std::string data_ = "data_file.txt";
    create_file_for_test(data_);
    std::cout << "Created!" << std::endl;
    file.open(data_, std::ios::binary);
    std::thread thr_1(std::bind(main_func, my_data {
        mem_1,
        len_1,
        mem_2,
        len_2,
        mutex_,
        last_in_queu,
        last_readed_in_queu,
        0,
        file
    }));
    std::thread thr_2(std::bind(main_func, my_data {
        mem_1,
        len_1,
        mem_2,
        len_2,
        mutex_,
        last_in_queu,
        last_readed_in_queu,
        1,
        file
    }));
    thr_1.join();
    thr_2.join();
    file.close();
    delete[] mem_1;
    delete[] mem_2;
    assert(compare_files(data_, "result.txt") == true);
    return;
}

int main() {
    DefaultTest();
    std::cout << "Success!\n";
    return 0;
}
