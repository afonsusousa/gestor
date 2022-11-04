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
    Pedido(const Estudante *p, std::vector<Turma>, std::vector<Turma>);

    /**@brief Estudante a cujo o Pedido é relativo
     * */
    const Estudante *estudante;

    /**@brief Obter Turmas a serem adicionadas pelo pedido
     * @return Turmas
     * */
    std::vector<Turma> get_a_adicionar() const;

    /**@brief Obter Turmas a serem removidas pelo pedido
     * @return Turmas
     * */
    std::vector<Turma> get_a_remover() const;

    /**@brief Obter Turmas resultantes do pedido
     * @return Turmas
     * */
    std::vector<Turma> getCandidate();

    /**@brief Adiciona turma à lista de remoção
     * @param t Turma
     * @return Verdadeiro se a turma foi adicionada
     * */
    bool add_to_remove(Turma &t);

    /**@brief Adiciona turma à lista de inscrição
     * @param t Turma
     * */
    void add_to_add(Turma &t);

    /**@brief Remove a última turma adicionada
     * */
    void pop_add();

    /**@brief Remove turma da lista de remoção
     * @param t Turma
     * */
    bool remove_from_remove(Turma &t);


private:

    /**@brief Lista de turmas a serem adicionadas ao horário
     * */
    std::vector<Turma> a_adicionar;

    /**@brief Lista de turmas a serem removidas do horário
     * */
    std::vector<Turma> a_remover;
};


#endif //GESTOR_PEDIDO_H
