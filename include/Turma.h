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

    /**@brief Obter o código da UC
     * @return Código da UC
     * */
    std::string getCodUC() const;

    /**@brief Obter o código da Turma
     * @return Código da Turma
     * */
    std::string getCodTurma() const;

    /**@brief Operator == overload
     * */
    bool operator==(const Turma& t);

    /** @brief Overload of operator<< */
    friend std::ostream& operator<<(std::ostream &os, const Turma &n);


private:

    /**@brief Código da UC
     * */
    std::string codUC;

    /**@brief Código da Turma
     * */
    std::string codTurma;

};


#endif //GESTOR_TURMA_H
