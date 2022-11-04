//
// Created by afonsusousa on 11/3/22.
//

#include <stdexcept>
#include "../include/GestorHorarios.h"
#include "../include/utils.h"

void GestorHorarios::get_comp(int i, std::function<bool(const UCTurma&, const UCTurma&)> &cmp) {
    switch(i){
        case 0: cmp = [    ](const UCTurma &p1, const UCTurma &p2){ return p1 < p2;}; break;
        case 1: cmp = [    ](const UCTurma &p1, const UCTurma &p2){ return p1.getInscritos() < p2.getInscritos(); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void GestorHorarios::get_filter(int i, const std::string &str, std::function<bool(const UCTurma &)> &cmp) {
    switch(i) {
        case 0 : cmp = [str](const UCTurma &p) { return (std::string(p.getCodUC()).find(str) != std::string::npos); }; break;
        case 1 : cmp = [str](const UCTurma &p) { return (std::string(p.getCodTurma()).find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void GestorHorarios::get_filter(int i, const std::string &str, std::function<bool(const Estudante &)> &cmp) {
    switch(i) {
        case 0 : cmp = [str](const Estudante &p) { return (std::string(p.get_codigo()).find(str) != std::string::npos); }; break;
        case 1 : cmp = [str](const Estudante &p) { return (std::string(p.get_nome()).find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void GestorHorarios::get_comp(int i, std::function<bool(const Estudante &, const Estudante &)> &cmp) {
    switch(i){
        case 0: cmp = [    ](const Estudante &p1, const Estudante &p2){ return p1.get_codigo() < p2.get_codigo(); }; break;
        case 1: cmp = [    ](const Estudante &p1, const Estudante &p2){ return p1.get_nome() < p2.get_nome(); }; break;
        case 2: cmp = [    ](const Estudante &p1, const Estudante &p2){ return (p1.getHorario().size() < p2.getHorario().size()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void GestorHorarios::get_filter(const Turma &trm, std::function<bool(const Estudante &)> &cmp) {
    cmp = [trm](const Estudante &p) {return p.hasClass(trm);};
}

