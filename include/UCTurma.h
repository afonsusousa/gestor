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
    /**@brief Código da UC
     * */
    std::string codUC;

    /**@brief Código da Turma
     * */
    std::string codTurma;

    /**@brief N de estudantes inscritos na Turma
     * */
    mutable int inscritos = 0;
public:
    /**@brief N max de estudantes que podem estar inscritos
     * */
    int cap = 30;

    UCTurma();
    UCTurma(std::string codUC, std::string codTurma);
    UCTurma(Turma turma);

    /**@brief Obter Código da UC
     * @return Código da UC
     * */
    std::string getCodUC() const;

    /**@brief Obter Código da Turma
     * @return Código da Turma
     * */
    std::string getCodTurma() const;

    /**@brief Incrementa o número de inscritos
     * @return Número de Inscritos
     * */
    int inscrever() const;

    /**@brief Desincrementa o número de inscritos
     * @return Número de Inscritos
     * */
    int desinscrever() const;

    /**@brief Obter o número de inscritos
     * @return Número de Inscritos
     * */
    int getInscritos() const;

    /**@brief Operator < overload
     * */
    bool operator<(const UCTurma &e) const;

    /**@brief Operator > overload
     * */
    bool operator>(const UCTurma &e) const;

    /**@brief Operator == overload
     * */
    bool operator==(const UCTurma &e) const;

    /**@brief Operator << overload
     * */
    friend std::ostream& operator<<(std::ostream &os, const UCTurma &n);
};


#endif //TRABALHO_UCTURMA_H
