//
// Created by afonsusousa on 11/3/22.
//

#include "../include/GestorHorarios.h"
#include "../include/utils.h"
#include <set>
#include <iostream>

void GestorHorarios::CLEAR() const {

}

void GestorHorarios::print_list(std::vector<Estudante> &v) {
    std::cout << "\n"
                 " ESTUDANTES\n"
                 "\n"
                 "╒════════════════╤══════════════════════╤═════════════════╕\n"
                 "│ Código[0]      │ Nome [1]             │ N Inscricões [2]│\n"
                 "╞════════════════╪══════════════════════╪═════════════════╡\n";

    for(const Estudante p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p.get_codigo()                   ,10) << "\t │ "
                  << utils::ljust((std::string)p.get_nome()                     ,20) << "\t│ "
                  << utils::rjust(std::to_string(p.getHorario().size())     ,16) << "│\n";
    }
    std::cout << "╘════════════════╧══════════════════════╧═════════════════╛\n"
              << std::flush;
}

void GestorHorarios::print_list(std::vector<UCTurma> &v) {
    int i = 0;

    std::cout << "\n"
                 " TURMAS \n"
                 "╒════════════════╤══════════════════════╤═════════════════╕\n"
                 "│ Código UC [0]  │ Código Turma [1]     │ N Inscritos  [2]│\n"
                 "╞════════════════╪══════════════════════╪═════════════════╡\n";

    for(const UCTurma t:v){
        std::cout << "│ "
                  << utils::ljust((std::string)t.getCodUC()                  ,10) << "\t │ "
                  << utils::ljust((std::string)t.getCodTurma()                     ,20) << "\t│ "
                  << utils::rjust(std::to_string(t.getInscritos())     ,16) << "│ (" << i << ")\n";
        i++;
    }
    std::cout << "╘════════════════╧══════════════════════╧═════════════════╛\n"
              << std::flush;
}


void GestorHorarios::print_list(std::vector<Turma> &v) {
    int i = 0;
    std::cout << "\n"
                 " TURMAS \n"
                 "╒════════════════╤══════════════════════╕\n"
                 "│ Código UC [0]  │ Código Turma [1]     │\n"
                 "╞════════════════╪══════════════════════╡\n";

    for(const Turma t:v){
        std::cout << "│ "
                  << utils::ljust((std::string)t.getCodUC()                  ,10) << "\t │ "
                  << utils::ljust((std::string)t.getCodTurma()                     ,20) << "\t│ (" << i << ")\n";
        i++;
    }
    std::cout << "╘════════════════╧══════════════════════╛\n"
              << std::flush;
}

void GestorHorarios::print_schedule(const std::vector<Aula> &v) {

    std::vector<Aula> vec = v;
    utils::mergesort(vec);

    int day = -1;

    std::cout << std::endl;

    for(auto a : vec){
        if(a.weekday > day) {
            std::cout << a.day_string() << ":\n";
            day = a.weekday;
        }
        std::cout << "\t" << a.turma.getCodUC() << "/" << a.turma.getCodTurma() << "\t" << a.start << "h  \tD:" << a.duration << "h\tTipo: " << a.type << std::endl;
    }
    std::cout << std::endl;

}
