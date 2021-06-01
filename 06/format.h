#pragma once

#include <sstream>
#include <vector>

struct Error
{
    std::string message;
    Error(const std::string& str) : message(str) {}
};

std::string f(const std::string &str, const std::vector<std::string> &args) {
    std::string res = "";
    std::string num = "";
    bool p = false;
    size_t len = str.size();
    int k = args.size();
    for (size_t i = 0; i < len; ++i) {
        if(p) {
            if (isdigit(str[i])) {
                num += str[i];
            } else if (str[i] == '}') {
                if(num == "") {
                    throw Error("FormatError: String is invalid");
                }
                int n;
                try {
                    n = std::stoi(num);
                } catch(const std::out_of_range&) {
                    throw Error("IndexError: index out of range");
                }
                if (n >= 0 && n < k)
                    res += args[n];
                else
                    throw Error("IndexError: index out of range");
                num = "";
                p = false;
            } else {
                throw Error("FormatError: String is invalid");
            }
        } else {
            if (str[i] == '{') {
                p = true;
            } else {
                res += str[i];
            }
        }
    }
    if(p) {
        throw Error("FormatError: String is invalid");
    }
    return res;
}

template<class Arg>
std::string to_string(const Arg& arg)
{
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

template<class Arg, class... Args>
inline std::string f(const std::string& str, std::vector<std::string>& arguments, const Arg& arg, const Args&... args) {
    arguments.push_back(to_string(arg));
    return f(str, arguments, args...);
}

template<class Arg, class... Args>
std::string format(const std::string& str, const Arg& arg, const Args&... args) {
    std::vector<std::string> arguments;
    std::string result;
    try {
        result = f(str, arguments, arg, args...);
    }
    catch (const Error &e)
    {
        throw e;
    }
    return result;
}
