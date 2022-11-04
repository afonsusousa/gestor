//
// Created by afonsusousa on 10/29/22.
//

#ifndef TRABALHO_UCTURMA_H
#define TRABALHO_UCTURMA_H

#include <string>
#include "Aula.h"
#include "Turma.h"

class UCTurma {
private:
    std::string codUC;
    std::string codTurma;
    mutable int inscritos = 0;
public:
    int cap = 30;

    UCTurma();
    UCTurma(std::string codUC, std::string codTurma);
    std::string getCodUC() const;
    std::string getCodTurma() const;
    int inscrever() const;
    int desinscrever() const;
    int getInscritos() const;
    bool operator<(const UCTurma &e) const;
    bool operator==(const UCTurma &e) const;

    UCTurma(Turma turma);
};


#endif //TRABALHO_UCTURMA_H
