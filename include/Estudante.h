//
// Created by afonsusousa on 10/29/22.
//

#ifndef TRABALHO_ESTUDANTE_H
#define TRABALHO_ESTUDANTE_H

#include <string>
#include <vector>
#include <list>
#include "UCTurma.h"
#include "Turma.h"

class Estudante {
public:
    Estudante();
    Estudante(std::string codigo, std::string nome);

    Estudante(std::string codigo);

    std::string get_codigo() const;
    std::string get_nome() const;
    bool operator<(const Estudante &e) const;
    bool operator==(const Estudante &e) const;
    void addUCTurma(Turma t) const;
    std::vector<Turma> getHorario() const;
    void setHorario(std::vector<Turma>) const;
    bool hasClass(const Turma &t) const;

private:
    std::string codigo;
    std::string nome;
    mutable std::vector<Turma> horario;
};


#endif //TRABALHO_ESTUDANTE_H
