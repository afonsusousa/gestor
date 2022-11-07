//
// Created by afonsusousa on 11/4/22.
//

#include "GestorHorarios.h"

Turma GestorHorarios::escolherTurma(std::vector<UCTurma> &v){

    std::vector<UCTurma> temp;
    for (auto x : v)
        temp.push_back(x);

    while (true) {
        CLEAR();
        prints_list(temp);
        std::vector<std::string> ids = utils::parse_command(prompt("(#) or \"back\"to return: "));

        if(ids[0] == "back") return {};
        if(ids.size() != 1) {
            utils::error("Pick number:");
            continue;
        }

        int index; try { index = std::stoi(ids[0]);} catch(const std::invalid_argument &e){ utils::error("invalid code"); continue; }

        if(index > temp.size() - 1 || index < 0){
            utils::error("Out of range!");
            continue;
        } else {
            return Turma(temp.at(index).getCodUC(), temp.at(index).getCodTurma());
        }
    }
}

const UCTurma *GestorHorarios::escolherUCTurma() {

    std::vector<UCTurma> temp;
    for(auto x : turmas) temp.push_back(x);


    while (true) {
        CLEAR();
        prints_list(temp);
        std::vector<std::string> ids = utils::parse_command(prompt("(#) or \"back\"to return:"));

        if(ids[0] == "back") return nullptr;
        if(ids.size() != 1) {
            utils::error(" Numero:");
            continue;
        }

        const UCTurma * it = nullptr;

        int index; try { index = std::stoi(ids[0]);} catch(const std::invalid_argument &e){ utils::error("invalid code"); continue; }

        if(index > temp.size() - 1 || index < 0){
            utils::error("Out of range!");
            continue;
        } else {
            if (turmas.find(temp.at(index)) != turmas.end())
                it = &(*turmas.find(temp.at(index)));
        }

        if (it == nullptr) {
            utils::error("Somehow a Turma não existe!");
            continue;
        } else {
            return it;
        }
    }
}

const UCTurma *GestorHorarios::escolherUCTurma(const std::vector<Turma> &v) {
    std::vector<Turma> temp;
    for (auto x : v)
        temp.push_back(x);

    while (true) {
        CLEAR();
        prints_list(temp);
        std::vector<std::string> ids = utils::parse_command(prompt("(#):"));

        if(ids[0] == "back") return NULL;
        if(ids.size() != 1) {
            utils::error("Pick number:");
            continue;
        }
        const UCTurma * it = NULL;
        int index; try { index = std::stoi(ids[0]);} catch(const std::invalid_argument &e){ utils::error("invalid code"); continue; }

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

bool GestorHorarios::criarPedido(Pedido &p) {

    while(true) {

        auto temp = p.getCandidate();

        CLEAR();
        print_list(temp);

        std::string answer, prompt = "(" + p.estudante->get_codigo() + "):\n(a)dicionar | (r)emover | (b)ack( | (s)ave > ";
        utils::input(prompt, answer, std::cin, std::cout);

        CLEAR();

        // ADD CLASSES TO PEDIDO

        if (answer == "a" || answer == "adicionar") {
            const UCTurma *turma;
            do {
                Pedido temp_p = p;

                turma = escolherUCTurma();
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
        if (answer == "r" || answer == "remover") {

            const UCTurma *turma;

            do {
                turma = escolherUCTurma(temp);
                if (turma == NULL) break;

                Turma t(turma->getCodUC(), turma->getCodTurma());
                temp.erase(std::find(temp.begin(), temp.end(),t));
                if(!p.remove_from_add(t)) p.add_to_remove(t);

            } while (true);
        }

        if(answer == "b" || answer == "back") return true;
        if(answer == "s" || answer == "save") break;
    }

    return false;

}

