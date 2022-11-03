//
// Created by afonsusousa on 11/3/22.
//

#include "GestorHorarios.h"
#include "utils.h"
#include <set>
#include <iostream>

void GestorHorarios::print_list(const std::set<Estudante> &v) {
    std::cout << "\n"
                 " ESTUDANTES\n"
                 "\n"
                 "╒════════════════╤═══════════════════════════╤═════════════════╕\n"
                 "│ Código [0]     │ Nome [1]                  │ N Inscricões [2]│\n"
                 "╞════════════════╪═══════════════════════════╪═════════════════╡\n";

    for(const Estudante p:v){
        std::cout << "│ "
                  << utils::ljust((std::string)p.get_codigo()                   ,10) << "\t │ "
                  << utils::ljust((std::string)p.get_nome()                     ,22) << "\t │ "
                  << utils::rjust(std::to_string(p.getHorario().size())     ,16) << "│\n";
    }
    std::cout << "╘════════════════╧═══════════════════════════╧═════════════════╛\n"
              << std::flush;
}