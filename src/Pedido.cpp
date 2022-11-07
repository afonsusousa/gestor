//
// Created by afonsusousa on 11/2/22.
//

#include <algorithm>
#include "Pedido.h"

Pedido::Pedido(const Estudante *p, std::vector<Turma> a, std::vector<Turma> r) : estudante(p), a_adicionar(a), a_remover(r){}



std::vector<Turma> Pedido::get_a_adicionar() const{
    return a_adicionar;
}

std::vector<Turma> Pedido::get_a_remover() const{
    return a_remover;
}

Pedido::Pedido(Estudante *p) : estudante(p){

}

std::vector<Turma> Pedido::getCandidate() {

    std::vector<Turma> t;

    for (auto x: estudante->getHorario())
        t.push_back(x);

    for (auto x: a_adicionar)
        t.push_back(x);

    for (auto x: a_remover) {
        auto it = std::find(t.begin(), t.end(), x);
        if (it != t.end()) t.erase(it);
    }

    return t;
}

bool Pedido::add_to_remove(Turma &t) {
    if(estudante->hasClass(t)) { a_remover.push_back(t); return true;}
    return false;
}

bool Pedido::remove_from_add(Turma &t) {
    auto x = std::find(a_adicionar.begin(), a_adicionar.end(), t);
    if(x != a_adicionar.end()) {
        a_adicionar.erase(x);
        return true;
    }
    return false;
}

void Pedido::add_to_add(Turma &t) {
    a_adicionar.push_back(t);
}

void Pedido::pop_add() {
    a_adicionar.pop_back();
}

std::ostream &operator<<(std::ostream &os, const Pedido &n) {
    os << n.estudante->get_codigo() << std::string(":\n");

    os << std::string("\tA remover:\n");
    for(auto x : n.get_a_remover()){
        os << std::string("\t") << x.getCodUC() << x.getCodTurma() << std::string("\n");
    }

    os << std::string("\tA adicionar:\n");
    for(auto x : n.get_a_adicionar()){
        os << std::string("\t") << x.getCodUC() << x.getCodTurma() << std::string("\n");
    }
    
    return os;
}
