//
// Created by afonsusousa on 10/29/22.
//

#ifndef TRABALHO_UC_H
#define TRABALHO_UC_H

#include <vector>
#include "UCTurma.h"

class UC {
public:
    UC();
    UC(std::string codigo);
    std::string codigo;
    mutable std::vector<UCTurma> turmas;
    bool operator<(const UC &u) const;
    void addTurma(const UCTurma &uct) const;
};


#endif //TRABALHO_UC_H
