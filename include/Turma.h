//
// Created by afonsusousa on 11/2/22.
//

#ifndef GESTOR_TURMA_H
#define GESTOR_TURMA_H


#include <string>

class Turma {
public:
    Turma();
    Turma(std::string coduc, std::string codturma);
    std::string getCodUC() const;
    std::string getCodTurma() const;
    bool operator==(const Turma& t);
private:
    std::string codUC;
    std::string codTurma;

};


#endif //GESTOR_TURMA_H
