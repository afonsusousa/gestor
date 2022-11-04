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

    /**@brief removes spaces from left
     * @param s string to process
     * */
    void ltrim(std::string &s);

    /**@brief removes spaces from right
     * @param s string to process
     * */
    void rtrim(std::string &s);

    /**@brief removes spaces from either side of the string
     * @param s string to process
     * */
    void trim(std::string &s);

    /**@brief prints error
    * @param s string to print
    * */
    void error(const std::string &s);

    /**@brief Filtra um vetor de acordo com um predicado
     * @param v vetor a filtrar
     * @param valid predicado
     * @return vetor filtrado
     * */
    template<class T, class Valid> std::vector<T> filter(const std::vector<T> &v, Valid valid);

    /**@brief Ordena um vetor
     * @brief Complexidade: O(nlogn)
     * @param v Vetor a ordenar
     * @param l Primeiro elemento do range
     * @param r Elemento à direita do range
     * @param comp Função de comparaçaõ
     * */
    template<class T, class Compare> void mergesort(std::vector<T> &v, const size_t &l, const size_t &r, Compare comp);

    /**@brief Recebe input
    * @param msg Mensagem a imprimir ("shell")
    * @param object Objeto para armazenar input
    * @param is Input stream
    * @param os Output stream
    * */
    template<class T> bool input(const std::string &msg, T &object, std::istream &is, std::ostream &os);

    /**@brief Justifica à direita
     * @param s string a justificar
     * @param sz tamanho final do string
     * @return string justificado
     * */
    std::string ljust(std::string s, size_t sz);

    /**@brief Justifica à direita
     * @param s string a justificar
     * @param sz tamanho final do string
     * @return string justificado
     * */
    std::string rjust(std::string s, size_t sz);

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

    /**@brief Ordena um vetor
     * @param v Vetor a ordenar
     * @param comp Função de comparaçaõ
     * */
    template<class T, class Compare> void mergesort(std::vector<T> &v, Compare comp){ utils::mergesort(v, 0, v.size(), comp); }

    /**@brief Ordena um vetor
     * @param v Vetor a ordenar
     * */
    template<class T> void mergesort(std::vector<T> &v){ utils::mergesort(v, std::less<T>()); }

    template<class T> bool utils::input(const std::string &msg, T &object, std::istream &is, std::ostream &os) {
        std::string input;
        std::stringstream ss; ss.exceptions(std::stringstream::failbit | std::stringstream::badbit);

        while (true) {
            os << msg; std::getline(is, input); utils::trim(input);
            if (input == "cancel") {
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

    /**@brief Decompõe string num vetor de comandos
     * @param s String a decompor
     * @return Vetor de comandos
     * */
    std::vector<std::string> parse_command(const std::string &s);

    void wait();
};


#endif //GESTOR_UTILS_H
