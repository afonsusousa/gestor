//
// Created by afonsusousa on 11/4/22.
//

#include "GestorHorarios.h"

const Estudante *GestorHorarios::escolherEstudante() {
    std::vector<Estudante> temp;
    for(auto x : estudantes) temp.push_back(x);


    while (true) {
        CLEAR(); print_list(temp);

        std::vector<std::string> ids = utils::parse_command(prompt("Nº Estudante: "));

        const Estudante * it = NULL;

        if(estudantes.find(Estudante(ids[0]))!= estudantes.end())
            it = &(*estudantes.find(Estudante(ids[0])));

        if (it == NULL) {
            utils::error("Estudante não existe!");
            continue;
        } else {
            return it;
        }
    }
    return nullptr;
}

const UCTurma *GestorHorarios::escolherTurma() {

    std::vector<UCTurma> temp;
    for(auto x : turmas) temp.push_back(x);


    while (true) {
        CLEAR();
        print_list(temp);
        std::vector<std::string> ids = utils::parse_command(prompt("(#):"));

        if(ids[0] == "back") return NULL;
        if(ids.size() != 1) {
            utils::error("Pick number:");
            continue;
        }

        const UCTurma * it = NULL;

        int index = std::stoi(ids[0]);

        if(index > temp.size() - 1 || index < 0){
            utils::error("Out of range!");
            continue;
        } else {
            if (turmas.find(temp.at(index)) != turmas.end())
                it = &(*turmas.find(temp.at(index)));
        }

        if (it == NULL) {
            utils::error("Somehow a Turma não existe!");
            continue;
        } else {
            return it;
        }
    }
}

const UCTurma *GestorHorarios::escolherTurma(const std::vector<Turma> &v) {
    std::vector<Turma> temp;
    for (auto x : v)
        temp.push_back(x);

    while (true) {
        CLEAR();
        print_list(temp);
        std::vector<std::string> ids = utils::parse_command(prompt("(#):"));

        if(ids[0] == "back") return NULL;
        if(ids.size() != 1) {
            utils::error("Pick number:");
            continue;
        }
        const UCTurma * it = NULL;
        int index = std::stoi(ids[0]);

        if(index > temp.size() - 1 || index < 0){
            utils::error("Out of range!");
            continue;
        } else {
            if (turmas.find(temp.at(index)) != turmas.end())
                it = &(*turmas.find(temp.at(index)));
        }

        if (it == NULL) {
            utils::error("Somehow a Turma não existe!");
            continue;
        } else {
            return it;
        }
    }
}

Pedido GestorHorarios::criarPedido() {

    Pedido p(escolherEstudante(), {}, {});


    while(true) {

        auto temp = p.getCandidate();

        CLEAR();
        print_list(temp);

        std::string answer, prompt = p.estudante->get_codigo() + ":\tadicionar(a)|remover(r): ";
        utils::input(prompt, answer, std::cin, std::cout);

        CLEAR();

        // ADD CLASSES TO PEDIDO

        if (answer == "a") {
            const UCTurma *turma;
            do {
                Pedido temp_p = p;

                turma = escolherTurma();
                if (turma == NULL) break;

                Turma t(turma->getCodUC(), turma->getCodTurma());

                temp_p.add_to_add(t);

                if (isCompatible(temp_p) != isCompatible(p) || !isCompatible(temp_p)) {

                    print_schedule(getAulas(temp_p.getCandidate()));
                    temp_p.pop_add();

                    utils::error("Turma Incompatível!");
                    continue;
                }
                p = temp_p;
            } while (true);
        }

        //REMOVE CLASSES FROM PEDIDO
        if (answer == "r") {

            const UCTurma *turma;

            do {
                turma = escolherTurma(temp);
                if (turma == NULL) break;

                Turma t(turma->getCodUC(), turma->getCodTurma());
                temp.erase(std::find(temp.begin(), temp.end(),t));
                if(!p.remove_from_remove(t)) p.add_to_remove(t);

            } while (true);
        }

        if(answer == "save") break;
    }

    return p;

}
