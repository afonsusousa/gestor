//
// Created by afonsusousa on 11/2/22.
//

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
