//
// Created by afonsusousa on 10/29/22.
//

#include "../include/Aula.h"
#include <algorithm>
#include <string>

bool Aula::overlaps(const Aula &aula) {
    return weekday == aula.weekday && std::max(start, aula.start) <= std::min(start + duration, aula.start + duration);
}

Aula::Aula() {

}

Aula::Aula(std::string weekday, double start, double duration, std::string type) : weekday(weekday), start(start), duration(duration), type(type){


}


bool Aula::operator==(const Aula &aula) {
    return weekday == aula.weekday &&
    start == aula.start &&
    duration == aula.duration && type == aula.type;
}
