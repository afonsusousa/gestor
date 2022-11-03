//
// Created by afonsusousa on 10/29/22.
//

#include "../include/UCTurma.h"

UCTurma::UCTurma(std::string codUC, std::string codTurma) : codUC(codUC), codTurma(codTurma){}

UCTurma::UCTurma() {
}

bool UCTurma::operator<(const UCTurma &e) const {
    if (codUC != e.codUC) {
        return codUC < e.codUC;
    } else {
        return codTurma < e.codTurma;
    }
}

std::string UCTurma::getCodUC() const{
    return codUC;
}

std::string UCTurma::getCodTurma() const{
    return codTurma;
}

int UCTurma::inscrever() const {
    inscritos++;
    return inscritos;
}

bool UCTurma::operator==(const UCTurma &e) const {
    return codUC == e.codUC && codTurma == e.codTurma;
}

int UCTurma::getInscritos() const {
    return inscritos;
}

UCTurma::UCTurma(Turma turma) : codUC(turma.getCodUC()), codTurma(turma.getCodTurma()){

}
