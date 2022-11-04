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

    enum weekday{
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    } typedef Day;

    Turma turma;
    Day weekday;
    double start;
    double duration;
    std::string type;
    std::string day_string();
    bool overlaps(const Aula &slot);
    bool operator==(const Aula &aula) const;
    bool operator<(const Aula &aula) const;
};


#endif //TRABALHO_SLOT_H
