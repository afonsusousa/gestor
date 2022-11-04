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

    /**@brief Obter horário
     * @return Horário
     * */
    std::vector<Aula> get_horario() const;

    /**@brief Adiciona aula
     * @param a Aula a adicionar
     * */
    void addAula(const Aula &a) const;

    /**@brief Operator < overload
     * */
    bool operator<(const UCTurmaSchedule &e) const;

private:

    /**@brief Código da UC
     * */
    std::string codUC;

    /**@brief Código da UC
     * */
    std::string codTurma;

    /**@brief Horário
     * */
    mutable std::vector<Aula> horario;

};


#endif //GESTOR_UCTURMASCHEDULE_H
