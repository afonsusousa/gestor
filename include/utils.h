//
// Created by afonsusousa on 11/2/22.
//

#ifndef GESTOR_UTILS_H
#define GESTOR_UTILS_H

#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>
#include <algorithm>
#include <sstream>

namespace utils {

    void ltrim(std::string &s);
    void rtrim(std::string &s);
    void trim(std::string &s);
    bool isCancel(std::string s);
    void error(const std::string &s);

    template<class T, class Valid> std::vector<T> filter(const std::vector<T> &v, Valid valid);
    template<class T, class Compare> void mergesort(std::vector<T> &v, const size_t &l, const size_t &r, Compare comp);
    template<class T> bool input(const std::string &msg, T &object, std::istream &is, std::ostream &os);
    template<class T, class Func> bool input(const std::string &msg, Func f , T &object, std::istream &is, std::ostream &os);

    template<class T, class Valid> std::vector<T> utils::filter(const std::vector<T> &v, Valid valid){
        std::vector<T> ret;
        for(T p:v){
            if(valid(p)){
                ret.push_back(p);
            }
        }
        return ret;
    }

    template<class T, class Compare> void utils::mergesort(std::vector<T> &v, const size_t &l, const size_t &r, Compare comp){
        if(r-l <= 1) return;
        size_t m = l + (r-l)/2;
        utils::mergesort(v,l,m,comp); utils::mergesort(v,m,r,comp);
        size_t i = l, j = m;
        std::vector<T> w(r-l);
        size_t k = 0;
        while(i != m && j != r){
            if(!comp(v[j],v[i])) w[k++] = v[i++];
            else w[k++] = v[j++];
        }
        while(i != m) w[k++] = v[i++];
        while(j != r) w[k++] = v[j++];
        std::copy(w.begin(), w.end(), v.begin()+(long)l);
    }
    template<class T, class Compare> void mergesort(std::vector<T> &v, Compare comp){ utils::mergesort(v, 0, v.size(), comp); }

    template<class T               > void mergesort(std::vector<T> &v){ utils::mergesort(v, std::less<T>()); }

    template<class T> bool utils::input(const std::string &msg, T &object, std::istream &is, std::ostream &os) {
        std::string input;
        std::stringstream ss; ss.exceptions(std::stringstream::failbit | std::stringstream::badbit);

        while (true) {
            os << msg; std::getline(is, input); utils::trim(input);
            if (utils::isCancel(input)) {
                os << "Operation cancelled.\n"; return false;
            }
            ss.clear(); ss.str(input);
            try {
                ss >> object;
                return true;
            } catch (const std::ios_base::failure &ios_fail) {
                std::cerr << "ERROR: Input failed.\n";
            } catch (const std::exception &ex) {
                std::cerr << "ERROR: " << ex.what() << "\n";
            }
        }
    }

    template<class T, class Func> bool utils::input(const std::string &msg, Func f , T &object, std::istream &is, std::ostream &os) {
        std::string input;

        while (true) {
            os << msg; std::getline(is, input); utils::trim(input);
            if (utils::isCancel(input)) {
                os << "Operation cancelled.\n"; return false;
            }
            try {
                f(object, input);
                return true;
            } catch (const std::ios_base::failure &ios_fail) {
                std::cerr << "ERROR: Input failed.\n";
            } catch (const std::exception &ex) {
                std::cerr << "ERROR: " << ex.what() << "\n";
            }
        }
    }
};


#endif //GESTOR_UTILS_H
