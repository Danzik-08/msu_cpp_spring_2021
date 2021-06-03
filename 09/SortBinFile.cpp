#include<stdio.h>

#include<iostream>

#include<fstream>

#include<queue>

#include<thread>

#include<pthread.h>

#include<string>

#include<condition_variable>

#include<mutex>

#include<algorithm>

#include<exception>

#include "SortBinFile.h"

void main_func(my_data cur_data) {
    uint64_t * cur_mem;
    size_t len = 0;
    uint64_t cur_elem = 0;
    std::ofstream cur_file;
    if (cur_data.cur_cnt) {
        cur_mem = cur_data.mem_2;
    } else {
        cur_mem = cur_data.mem_1;
    }
    while (true) {
        my_wait(2);
        if (!cur_data.cur_cnt) {
            cur_data.len_1 = 0;
            for (size_t i = 0; i < LEN; i++) {
                cur_data.main_file.read(reinterpret_cast < char * > ( & cur_elem), sizeof(cur_elem));
                if (!cur_data.main_file.eof()) {
                    cur_data.mem_1[i] = cur_elem;
                    cur_data.len_1++;
                } else {
                    break;
                }
            }
            cur_data.len_2 = 0;
            for (size_t i = 0; i < LEN; i++) {
                cur_data.main_file.read(reinterpret_cast < char * > ( & cur_elem), sizeof(cur_elem));
                if (!cur_data.main_file.eof()) {
                    cur_data.mem_2[i] = cur_elem;
                    cur_data.len_2++;

                } else {
                    break;
                }
            }
        }
        my_wait(2);
        if (cur_data.cur_cnt) {
            if (cur_data.len_2) {
                len = cur_data.len_2;
            } else {
                break;
            }
        } else if (cur_data.len_1) {
            len = cur_data.len_1;
        } else {
            break;
        }
        std::string name_file; {
            std::unique_lock < std::mutex > lock(cur_data.mutex_);
            name_file = std::to_string(cur_data.last_in_queu) + ".txt";
            cur_data.last_in_queu++;
        }
        std::sort(cur_mem, cur_mem + len);
        cur_file.open(name_file, std::ios::binary);
        for (size_t i = 0; i < len; i++) {
            cur_file.write(reinterpret_cast < char * > ( & cur_mem[i]), sizeof(uint64_t));
        }
        cur_file.close();
        if (!cur_data.len_1 || !cur_data.len_2) {
            break;
        }
    }
    my_wait(2);
    std::string file_1_name, file_2_name, result;
    while (true) {
        {
            std::unique_lock < std::mutex > lock(cur_data.mutex_);
            if (cur_data.last_in_queu == cur_data.last_readed_in_queu) {
                break;
            }
            file_2_name = std::to_string(cur_data.last_readed_in_queu + 1) + ".txt";
            file_1_name = std::to_string(cur_data.last_readed_in_queu) + ".txt";
            if (cur_data.last_in_queu - cur_data.last_readed_in_queu == 2) {
                result = "result.txt";
                cur_data.last_readed_in_queu += 2;
            } else {
                result = std::to_string(cur_data.last_in_queu) + +".txt";
                cur_data.last_readed_in_queu += 2;
                cur_data.last_in_queu++;
            }
        }
        my_merge(file_1_name, file_2_name, result, cur_mem, cur_mem + LEN / 2);
    }
    return;
}

void my_merge(const std::string & part_1,
    const std::string & part_2,
        const std::string & result, uint64_t * cur_mem_1, uint64_t * cur_mem_2) {
    std::ifstream file_part_1, file_part_2;
    std::ofstream file_result;
    file_part_1.open(part_1, std::ios::binary);
    file_part_2.open(part_2, std::ios::binary);
    file_result.open(result, std::ios::binary);
    if (!file_part_1.is_open() || !file_part_2.is_open() || !file_result.is_open()) {
        std::cout << "Failed to open files" << std::endl;
        exit(1);
    }
    uint64_t cur_elem;
    size_t mem_1_len = 0, mem_2_len = 0;
    size_t len_arr = LEN / 2;
    while (true) {
        for (size_t i = mem_1_len; i < len_arr; i++) {
            file_part_1.read(reinterpret_cast < char * > ( & cur_elem), sizeof(cur_elem));
            if (file_part_1) {
                mem_1_len++;
                cur_mem_1[i] = cur_elem;
            } else {
                break;
            }
        }
        for (size_t i = mem_2_len; i < len_arr; i++) {
            file_part_2.read(reinterpret_cast < char * > ( & cur_elem), sizeof(cur_elem));
            if (file_part_2) {
                mem_2_len++;
                cur_mem_2[i] = cur_elem;
            } else {
                break;
            }
        }
        if (mem_1_len && mem_2_len) {
            size_t cnt_1 = 0, cnt_2 = 0;
            while (mem_2_len > cnt_2 && mem_1_len > cnt_1) {
                if (cur_mem_1[cnt_1] >= cur_mem_2[cnt_2]) {
                    file_result.write(reinterpret_cast < char * > (cur_mem_2 + cnt_2), sizeof(uint64_t));
                    cnt_2++;
                } else {
                    file_result.write(reinterpret_cast < char * > (cur_mem_1 + cnt_1), sizeof(uint64_t));
                    cnt_1++;
                }
            }
            for (size_t i = 0; i < mem_1_len - cnt_1; i++) {
                cur_mem_1[i] = cur_mem_1[i + cnt_1];
            }
            mem_1_len -= cnt_1;
            for (size_t i = 0; i < mem_2_len - cnt_2; i++) {
                cur_mem_2[i] = cur_mem_2[i + cnt_2];
            }
            mem_2_len -= cnt_2;
        } else if (!mem_1_len && mem_2_len) {
            for (size_t i = 0; i < mem_2_len; i++) {
                file_result.write(reinterpret_cast < char * > (i + cur_mem_2), sizeof(uint64_t));
            }
            mem_2_len = 0;
        } else if (mem_1_len && !mem_2_len) {
            for (size_t i = 0; i < mem_1_len; i++) {
                file_result.write(reinterpret_cast < char * > (i + cur_mem_1), sizeof(uint64_t));
            }
            mem_1_len = 0;
        } else {
            break;
        }
    }
    file_part_1.close();
    file_part_2.close();
    file_result.close();
    return;
}

void my_wait(size_t threads_all) {
    static size_t thread_cnt_in = 0;
    static size_t thread_cnt_out = 0;
    static std::mutex mutex_;
    static std::condition_variable in ;
    static std::condition_variable out;
    std::unique_lock < std::mutex > lock(mutex_);
    thread_cnt_in++;
    if (thread_cnt_in < threads_all) {
        while (thread_cnt_in < threads_all) {
            in .wait(lock);
        }
    } else {
        thread_cnt_out = 0; in .notify_all();
    }
    thread_cnt_out++;
    if (thread_cnt_out < threads_all) {
        while (thread_cnt_out < threads_all) {
            out.wait(lock);
        }
    } else {
        thread_cnt_in = 0;
        out.notify_all();
    }
    return;
}
