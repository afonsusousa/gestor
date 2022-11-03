//
// Created by afonsusousa on 10/29/22.
//

#ifndef TRABALHO_SLOT_H
#define TRABALHO_SLOT_H

#include <string>

class Aula {
public:
    Aula();
    Aula(std::string weekday, double start, double duration, std::string type);
    std::string weekday;
    double start;
    double duration;
    std::string type;
    bool overlaps(const Aula &slot);
    bool operator==(const Aula &aula);
};


#endif //TRABALHO_SLOT_H
