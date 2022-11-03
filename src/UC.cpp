//
// Created by afonsusousa on 10/29/22.
//

#include "../include/UC.h"

UC::UC(std::string codigo) : codigo(codigo){}

bool UC::operator<(const UC &u) const {
    return codigo < u.codigo;
}

void UC::addTurma(UCTurma *uct) const{
    turmas.push_back(uct);
}