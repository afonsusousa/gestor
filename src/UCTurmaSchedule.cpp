//
// Created by afonsusousa on 10/30/22.
//

#include <iostream>
#include "../include/UCTurmaSchedule.h"
#include "../include/UCTurma.h"

UCTurmaSchedule::UCTurmaSchedule() = default;

UCTurmaSchedule::UCTurmaSchedule(std::string coduc, std::string codt) : codUC(coduc), codTurma(codt) {}

bool UCTurmaSchedule::operator<(const UCTurmaSchedule &e) const {
    if(this->codUC < e.codUC) return true;
    if(this->codUC == e.codUC && this->codTurma < e.codTurma) return true;
    return false;
}

void UCTurmaSchedule::addAula(const Aula &a) const {
    horario.push_back(a);
}


std::vector<Aula> UCTurmaSchedule::get_horario() const {
    return horario;
}

