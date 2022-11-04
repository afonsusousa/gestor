//
// Created by afonsusousa on 10/29/22.
//

#include "../include/Aula.h"
#include "../include/Turma.h"
#include <algorithm>
#include <string>

bool Aula::overlaps(const Aula &aula) {
    return weekday == aula.weekday && std::max(start, aula.start) <= std::min(start + duration, aula.start + duration);
}

Aula::Aula() {}

Aula::Aula(Turma t, std::string day, double start, double duration, std::string type) : turma(t), start(start), duration(duration), type(type){
        if (day == "Monday") weekday = Monday;
        if (day == "Tuesday") weekday = Tuesday;
        if (day == "Wednesday") weekday = Wednesday;
        if (day == "Thursday") weekday = Thursday;
        if (day == "Friday" ) weekday = Friday;
        if (day == "Saturday") weekday = Saturday;
        if (day == "Sunday") weekday = Sunday;
}


bool Aula::operator==(const Aula &aula) const {
    return weekday == aula.weekday &&
    start == aula.start &&
    duration == aula.duration && type == aula.type;
}

bool Aula::operator<(const Aula &aula) const{
    if(weekday < aula.weekday) return true;
    if(weekday == aula.weekday) return start < aula.start;
    return false;
}

std::string Aula::day_string() const {
    switch (weekday) {
        case 0:            return "Monday";
        case 1:            return "Tuesday";
        case 2:            return "Wednesday";
        case 3:            return "Thursday";
        case 4:            return "Friday";
        case 5:            return "Saturday";
        case 6:            return "Sunday";
        default: return NULL;
    }
}

std::ostream &operator<<(std::ostream &os, const Aula &n) {
    os << n.turma.getCodTurma() << std::string(",")
    << n.turma.getCodUC() << std::string (",")
    << n.day_string() << std::string (",")
    << std::to_string(n.start) << std::string(",")
    << std::to_string(n.duration) << std::string(",")
    << n.type;
    return os;
}
