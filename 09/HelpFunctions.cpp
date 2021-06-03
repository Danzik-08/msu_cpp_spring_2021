#include<iostream>

#include<algorithm>

#include "HelpFunctions.h"

void create_file_for_test(const std::string & file_name) {
    std::srand(std::time(nullptr));
    std::ofstream file_for_write;
    file_for_write.open(file_name, std::ios::binary);
    if (!file_for_write.is_open()) {
        std::cout << "Failed to open files" << std::endl;
        exit(1);
    }
    uint64_t cur_elem;
    for (size_t i = 0; i < SIZE; i++) {
        cur_elem = rand() % 100000;
        file_for_write.write(reinterpret_cast < char * > ( & cur_elem), sizeof(cur_elem));
    }
    file_for_write.close();
    return;
}

bool read_from_file(const std::string & file_name, std::vector < uint64_t > & cur_vec_val) {
    std::ifstream file_for_read;
    file_for_read.open(file_name, std::ios::binary);
    if (!file_for_read.is_open()) {
        return false;
    }
    uint64_t cur_elem;
    for (size_t i = 0; i < SIZE; i++) {
        file_for_read.read(reinterpret_cast < char * > ( & cur_elem), sizeof(cur_elem));
        if (file_for_read.eof())
            break;
        cur_vec_val.push_back(cur_elem);
    }
    file_for_read.close();
    return true;
}

bool compare_files(const std::string & file_name_1,
    const std::string & file_name_2) {
    //std::cout<<"Comp"<< std::endl;
    std::vector < uint64_t > file_1, file_2;
    if (!(read_from_file(file_name_1, file_1) && read_from_file(file_name_2, file_2))) {
        std::cout << "Failed to open files_1" << std::endl;
        exit(1);
    }
    std::sort(file_1.begin(), file_1.end());
    if (file_2.size() != file_1.size()) {
        return false;
    }
    for (size_t i = 0; i < file_1.size(); i++) {
        if (file_1[i] != file_2[i]) {
            return false;
        }
    }
    return true;
}
