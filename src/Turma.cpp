//
// Created by afonsusousa on 11/2/22.
//

#include "../include/Turma.h"

Turma::Turma(std::string coduc, std::string codturma) : codUC(coduc), codTurma(codturma){

}

std::string Turma::getCodUC() {
    return codUC;
}

std::string Turma::getCodTurma() {
    return codTurma;
}

bool Turma::operator==(const Turma &t) {
    return codUC == t.codUC && codTurma == t.codTurma;
}
