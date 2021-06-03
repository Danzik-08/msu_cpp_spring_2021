#pragma once

#include<iostream>

#include<vector>

#include<string>

#include<cstdint>

#include<fstream>

#include<cstdlib>

#include<ctime>

const size_t SIZE = 100000000; //data size

void create_file_for_test(const std::string & file_name);

bool compare_files(const std::string & file_name_1,
    const std::string & file_name_2);

bool read_from_file(const std::string & file_name, std::vector < uint64_t > & cur_vec_val);
