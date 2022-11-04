//
// Created by afonsusousa on 10/29/22.
//

#ifndef TRABALHO_SLOT_H
#define TRABALHO_SLOT_H

#include <string>
#include "Turma.h"

class Aula {
public:
    Aula();
    Aula(Turma t, std::string weekday, double start, double duration, std::string type);

    /** @brief Representa dia da semana
     * */
    enum weekday{
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    } typedef Day;

    /** @brief Turma a que a aula corresponde
     * */
    Turma turma;

    /** @brief Dia da Semana
     * */
    Day weekday;

    /** @brief Hora de início
     * */
    double start;

    /** @brief Duração (em h)
     * */
    double duration;

    /** @brief Tipo de Aula
     * */
    std::string type;

    /** @brief Dia da semana
     * @return Dia da Semana
     * */
    std::string day_string() const;

    /** @brief Avalia sobreprosião de aula
     * @param aula Aula a avaliar
     * @return Se é sobreposta
     * */
    bool overlaps(const Aula &aula);

    /**@brief Operator == overload
     * */
    bool operator==(const Aula &aula) const;

    /**@brief Operator < overload
     * */
    bool operator<(const Aula &aula) const;

    /**@brief Operator << overload
     * */
    friend std::ostream& operator<<(std::ostream &os, const Aula &n);
};


#endif //TRABALHO_SLOT_H
