//
// Created by afonsusousa on 11/2/22.
//

#include "utils.h"

void utils::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
}

void utils::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(), s.end());
}

void utils::trim(std::string &s) {
    ltrim(s); rtrim(s);
}

bool utils::isCancel(std::string s) {
    return s == "cancel";
}

void utils::error(const std::string &s){
    std::cerr << "Error: " << s << std::endl;
    //wait();
}

std::string utils::ljust(std::string s, size_t sz){
    if(sz < 3) throw std::invalid_argument("size less than 3");
    if(s.size() < sz) s = s + std::string(sz-s.size(), ' ');
    if(s.size() > sz) s = s.substr(0,sz-3) + "...";
    return s;
}

std::string utils::rjust(std::string s, size_t sz){
    if(sz < 3) throw std::invalid_argument("size less than 3");
    if(s.size() < sz) s = std::string(sz-s.size(), ' ') + s;
    if(s.size() > sz)s = s.substr(0,sz-3) + "...";
    return s;
}