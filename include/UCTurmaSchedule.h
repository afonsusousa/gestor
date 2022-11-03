//
// Created by afonsusousa on 10/30/22.
//

#ifndef GESTOR_UCTURMASCHEDULE_H
#define GESTOR_UCTURMASCHEDULE_H

#include <string>
#include <vector>
#include "Aula.h"
#include "UCTurma.h"

class UCTurmaSchedule {
public:
    UCTurmaSchedule();
    UCTurmaSchedule(std::string coduc, std::string codt);

    std::string codUC;
    std::string codTurma;
    mutable std::vector<Aula> horario;
    void addAula(const Aula &a) const;
    bool operator<(const UCTurmaSchedule &e) const;
};


#endif //GESTOR_UCTURMASCHEDULE_H
