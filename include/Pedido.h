//
// Created by afonsusousa on 11/2/22.
//

#ifndef GESTOR_PEDIDO_H
#define GESTOR_PEDIDO_H

#include <string>
#include <vector>
#include "Turma.h"
#include "Estudante.h"

class Pedido {
public:
    Pedido(Estudante *p);
    Pedido(Estudante *p, std::vector<Turma>, std::vector<Turma>);

    Estudante *estudante;

    std::string get_codigo_estudante() const;
    std::vector<Turma> get_a_adicionar() const;
    std::vector<Turma> get_a_remover() const;

private:

    std::vector<Turma> a_adicionar;
    std::vector<Turma> a_remover;
};


#endif //GESTOR_PEDIDO_H
