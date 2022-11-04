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

    /** @brief Código do EStudante
     * @returns Código do Estudante
     * */
    std::string get_codigo() const;

    /** @brief Nome do Estudante
     * @returns Nome do Estudante
     * */
    std::string get_nome() const;

    bool operator<(const Estudante &e) const;
    bool operator==(const Estudante &e) const;

    /** @brief Adiciona Turma ao horário do Estudante
     * @param t Turma a adicionar
     * */
    void addUCTurma(Turma t) const;

    /** @brief Horário do Estudante
     * @return Horário do Estudante
     * */
    std::vector<Turma> getHorario() const;

    /** @brief Altera o Horário do Estudante
     * @param v Novo horário
     * */
    void setHorario(std::vector<Turma> v) const;

    /** @brief Verifica se a turma está no horário
     * @param t Turma a verificar
     * @return Se a turma está no horário do estudante
     * */
    bool hasClass(const Turma &t) const;

    /**@brief Operator << overload
     * */
    friend std::ostream& operator<<(std::ostream &os, const Estudante &n);

private:
    /** @brief Código do Estudante
     * */
    std::string codigo;

    /** @brief Nome do EStudante
     * */
    std::string nome;

    /** @brief Horário do Estudante
     * */
    mutable std::vector<Turma> horario;
};

#endif //TRABALHO_ESTUDANTE_H
