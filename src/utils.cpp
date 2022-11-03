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