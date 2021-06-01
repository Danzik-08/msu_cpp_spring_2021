#include <iostream>
#include "format.h"
#include <cassert>

std::stringstream ss_error;

void Test1() {
    assert(format("{1}+{1} = {0}", 2, "one") == "one+one = 2");
    std::stringstream ss;
    ss << format("{0} + {1} + {0} = {2}", 1, 2, 4);
    std::string s;
    getline(ss, s);
    assert(s == "1 + 2 + 1 = 4");
}

void Test2() {
    std::string s;
    try {
        s = format("{0} {1} {2} {3} {4}", 1, 2, 3, 4);
    } catch (const Error &e) {
        ss_error << e.message << std::endl;
    }
    getline(ss_error, s);
    assert(s == "IndexError: index out of range");
    try {
        s = format("{0}{12", 1);
    } catch (const Error &e) {
        ss_error << e.message << std::endl;
    }
    getline(ss_error, s);
    assert(s == "FormatError: String is invalid");
    try {
        s = format("{11111111111111111111111111}", 1);
    } catch (const Error &e) {
        ss_error << e.message << std::endl;
    }
    getline(ss_error, s);
    assert(s == "IndexError: index out of range");
}

int main()
{
    Test1();
    Test2();

    std::cout << "Success!\n";

    return 0;
}
