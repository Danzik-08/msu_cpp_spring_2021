#pragma once

#include<mutex>

#include<fstream>

#include<string>

#include<vector>

const size_t LEN = (1020 * 1020) / 2; //кажется, что если брать (1024 * 1024) . 2, вылетаем по памяти...

void my_merge(const std::string & part_1,
    const std::string & part_2,
        const std::string & result, uint64_t * cur_mem_1, uint64_t * cur_mem_2);
void my_wait(size_t threads_all);

struct my_data {
    uint64_t * mem_1;
    size_t & len_1;
    uint64_t * mem_2;
    size_t & len_2;
    std::mutex & mutex_;
    size_t & last_in_queu;
    size_t & last_readed_in_queu;
    size_t cur_cnt;
    std::ifstream & main_file;
};

void main_func(my_data cur_data);
