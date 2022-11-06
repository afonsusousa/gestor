//
// Created by afonsusousa on 11/3/22.
//

#include <stdexcept>
#include "../include/GestorHorarios.h"
#include "../include/utils.h"

void GestorHorarios::get_comp(int i, std::function<bool(const UCTurma&, const UCTurma&)> &cmp) {
    switch(i){
        case 0: cmp = [    ](const UCTurma &p1, const UCTurma &p2){ return p1 > p2;}; break;
        case 1: cmp = [    ](const UCTurma &p1, const UCTurma &p2){ return p1 > p2;}; break;
        case 2: cmp = [    ](const UCTurma &p1, const UCTurma &p2){ return p1.getInscritos() > p2.getInscritos(); }; break;

        case 3: cmp = [    ](const UCTurma &p1, const UCTurma &p2){ return p1 < p2;}; break;
        case 4: cmp = [    ](const UCTurma &p1, const UCTurma &p2){ return p1 < p2;}; break;
        case 5: cmp = [    ](const UCTurma &p1, const UCTurma &p2){ return p1.getInscritos() < p2.getInscritos(); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void GestorHorarios::get_filter(int i, const std::string &str, std::function<bool(const UCTurma &)> &cmp) {
    switch(i) {
        case 0 : cmp = [str](const UCTurma &p) { return (std::string(p.getCodUC()).find(str) != std::string::npos); }; break;
        case 1 : cmp = [str](const UCTurma &p) { return (std::string(p.getCodTurma()).find(str) != std::string::npos); }; break;
        case 2 : cmp = [str](const UCTurma &p) { return (std::to_string(p.getInscritos()).find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void GestorHorarios::get_filter(int i, const std::string &str, std::function<bool(const Estudante &)> &cmp) {
    switch(i) {
        case 0 : cmp = [str](const Estudante &p) { return (std::string(p.get_codigo()).find(str) != std::string::npos); }; break;
        case 1 : cmp = [str](const Estudante &p) { return (std::string(p.get_nome()).find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}
void GestorHorarios::get_comp(int i, std::function<bool(const Estudante &, const Estudante &)> &cmp) {
    switch(i){
        case 0: cmp = [    ](const Estudante &p1, const Estudante &p2){ return p1.get_codigo() > p2.get_codigo(); }; break;
        case 1: cmp = [    ](const Estudante &p1, const Estudante &p2){ return p1.get_nome() > p2.get_nome(); }; break;
        case 2: cmp = [    ](const Estudante &p1, const Estudante &p2){ return (p1.getHorario().size() > p2.getHorario().size()); }; break;
        case 3: cmp = [    ](const Estudante &p1, const Estudante &p2){ return p1.get_codigo() < p2.get_codigo(); }; break;
        case 4: cmp = [    ](const Estudante &p1, const Estudante &p2){ return p1.get_nome() < p2.get_nome(); }; break;
        case 5: cmp = [    ](const Estudante &p1, const Estudante &p2){ return (p1.getHorario().size() < p2.getHorario().size()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void GestorHorarios::get_filter(const UCTurma *trm, std::function<bool(const Estudante &)> &cmp) {
    cmp = [trm](const Estudante &p) {return p.hasClass(Turma(trm->getCodUC(), trm->getCodTurma()));};
}

template<> void GestorHorarios::list_commands<Estudante>(){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m             Ordenar por propriedade \033[4mNUM\033[0m [0-2]\n"
              << "    sortd \033[4mNUM\033[0m            Ordenar por propriedade (descendente) \033[4mNUM\033[0m [0-2]\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"     Restringir list a elementos que contenham \033[4mSTR\033[0m na propriedade \033[4mNUM\033[0m [0-2]\n"
              << "    searh_turma          Selecionar turma e filtrar\n"
              << "    horario \033[4mNUM\033[0m          Imprimir horario do estudante \033[4mNUM\033[0m \n"
              << "    select \033[4mNUM\033[0m           Selecionar  estudante e criar pedido \033[4mNUM\033[0m [Nº Estudante]\n"
              << "    reset                Limpar critérios\n"
              << "    back                \n";
    std::cout << std::endl;
}

template<> void GestorHorarios::list_commands<UCTurma>(){
    std::cout << "\n"
              << "COMMANDS:\n\n"
              << "    sort \033[4mNUM\033[0m            Ordenar por propriedade \033[4mNUM\033[0m [0-2] (1 == 0)\n"
              << "    sortd \033[4mNUM\033[0m           Ordenar por propriedade (descendente) \033[4mNUM\033[0m [0-2] (1 == 0)\n"
              << "    search \033[4mNUM\033[0m \"\033[4mSTR\033[0m\"    Restringir list a elementos que contenham \033[4mSTR\033[0m na propriedade \033[4mNUM\033[0m [0-2]\n"
              << "    horario             Selecionar turma e imprimir horario \n"
              << "    reset               Limpar critérios\n"
              << "    back                \n";
    std::cout << std::endl;
}

void GestorHorarios::list(std::vector<UCTurma> &v){
    const std::vector<UCTurma> original = v;
    while(true){
        CLEAR();
        print_list(v);
        list_commands<UCTurma>();
        std::vector<std::string> s = utils::parse_command(prompt());
        if(s.size() >= 1){
            if(s[0] == "sort"){
                if(s.size() != 2){ utils::error("wrong number of arguments"); continue; }
                int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid NUM"); continue; }
                std::function<bool(const UCTurma&, const UCTurma&)> cmp;
                try{
                    get_comp(i, cmp);
                    utils::mergesort(v,cmp);
                }catch(const std::invalid_argument &e){ utils::error(e.what()); }
            }else
                if(s[0] == "sortd"){
                if(s.size() != 2){ utils::error("wrong number of arguments"); continue; }
                int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid NUM"); continue; }
                std::function<bool(const UCTurma&, const UCTurma&)> cmp;
                try{
                    get_comp(i+3, cmp);
                    utils::mergesort(v,cmp);
                }catch(const std::invalid_argument &e){ utils::error(e.what()); }
            }else
            if(s[0] == "search"){
                if(s.size() != 3){ utils::error("wrong number of arguments"); continue; }
                int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid NUM"); continue; }
                std::function<bool(const UCTurma&)> cmp;
                try{
                    get_filter(i, s[2], cmp);
                    v = utils::filter(v,cmp);
                }catch(const std::invalid_argument &e){ utils::error(e.what()); }
            }else
                if(s[0] == "horario"){

                    Turma turma = escolherTurma(v);
                    auto aulas = getAulas({turma});
                    print_schedule(aulas);
                    utils::wait();
                }else
            if(s[0] == "reset"){
                if(s.size() != 1) utils::error("wrong number of arguments");
                else              v = original;
            }else
            if(s[0] == "back"){
                if(s.size() != 1) utils::error("wrong number of arguments");
                else              return;
            }else utils::error("unrecognized command");
        }
    }
}

void GestorHorarios::list(std::vector<Estudante> &v){
    const std::vector<Estudante> original = v;
    while(true){
        CLEAR();
        print_list(v);
        list_commands<Estudante>();
        std::vector<std::string> s = utils::parse_command(prompt());
        if(s.size() >= 1){
            if(s[0] == "sort"){
                if(s.size() != 2){ utils::error("wrong number of arguments"); continue; }
                int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid NUM"); continue; }
                std::function<bool(const Estudante&, const Estudante&)> cmp;
                try{
                    get_comp(i, cmp);
                    utils::mergesort(v,cmp);
                }catch(const std::invalid_argument &e){ utils::error(e.what()); }
            }else
            if(s[0] == "sortd"){
                if(s.size() != 2){ utils::error("wrong number of arguments"); continue; }
                int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid NUM"); continue; }
                std::function<bool(const Estudante&, const Estudante&)> cmp;
                try{
                    get_comp(i+3, cmp);
                    utils::mergesort(v,cmp);
                }catch(const std::invalid_argument &e){ utils::error(e.what()); }
            }else
            if(s[0] == "search"){
                if(s.size() != 3){ utils::error("wrong number of arguments"); continue; }
                int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid NUM"); continue; }
                std::function<bool(const Estudante&)> cmp;
                try{
                    get_filter(i, s[2], cmp);
                    v = utils::filter(v,cmp);
                }catch(const std::invalid_argument &e){ utils::error(e.what()); }
            }else
            if(s[0] == "search_turma"){
                if(s.size() != 1){ utils::error("wrong number of arguments"); continue; }
                std::function<bool(const Estudante&)> cmp;
                try{
                    get_filter(escolherUCTurma(), cmp);
                    v = utils::filter(v,cmp);
                }catch(const std::invalid_argument &e){ utils::error(e.what()); }
            }else
                if(s[0] == "horario"){

                    if(s.size() != 2){ utils::error("wrong number of arguments"); continue; }
                    int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid code"); continue; }
                    const std::vector<Turma> aulas;
                    auto x = estudantes.find(Estudante(s[1]));
                    if(x != estudantes.end()) {
                        print_schedule(getAulas(x->getHorario()));
                    } else utils::error("Estudante inválido!");
            }else
            if(s[0] == "select"){
                if(s.size() != 2){ utils::error("wrong number of arguments"); continue; }
                int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid code"); continue; }
                auto x = estudantes.find(Estudante(s[1]));
                if(x != estudantes.end()) {
                    Pedido p(&(*x), {}, {});
                    if(!criarPedido(p)) { pedidos.push(p); return; };
                }
            }
            else
            if(s[0] == "reset"){
                if(s.size() != 1) utils::error("wrong number of arguments");
                else              v = original;
            }else
            if(s[0] == "back"){
                if(s.size() != 1) utils::error("wrong number of arguments");
                else              return;
            }else utils::error("unrecognized command");
        }
    }
}



