//
// Created by afonsusousa on 11/2/22.
//

#include "../include/Turma.h"

Turma::Turma(std::string coduc, std::string codturma) : codUC(coduc), codTurma(codturma){

}

std::string Turma::getCodUC() const{
    return codUC;
}

std::string Turma::getCodTurma() const{
    return codTurma;
}

bool Turma::operator==(const Turma &t) {
    return codUC == t.codUC && codTurma == t.codTurma;
}

Turma::Turma() {

}

std::ostream& operator<<(std::ostream &os, const Turma &n){
    os << n.codUC << std::string(",") << n.codTurma;
    return os;
}