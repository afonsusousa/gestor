//
// Created by afonsusousa on 11/2/22.
//

#include <algorithm>
#include "Pedido.h"

Pedido::Pedido(Estudante *p, std::vector<Turma> a, std::vector<Turma> r) : estudante(p), a_adicionar(a), a_remover(r){}



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

    for (auto x: a_remover) {
        auto it = std::find(t.begin(), t.end(), x);
        if (it != t.end()) t.erase(it);
    }

    for (auto x: a_adicionar)
        t.push_back(x);

    return t;
}