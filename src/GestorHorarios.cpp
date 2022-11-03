//
// Created by afonsusousa on 10/29/22.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <functional>
#include <error.h>
#include "../include/GestorHorarios.h"
#include "../include/utils.h"


GestorHorarios::GestorHorarios() {
    read_ucs("../data/classes_per_uc.csv");
    read_classes("../data/classes.csv");
    read_students("../data/students_classes.csv");

    std::vector<Estudante> result;
    std::vector<Turma> ar = {Turma("L.EIC001","1LEIC05")};
    std::vector<Turma> aa;
    Estudante x = *estudantes.begin();

    std::cout << x.getHorario().size()<< std::endl;

    processPedido(p);

    std::cout << x.getHorario().size()<< std::endl;

}

void GestorHorarios::read_students(std::string filename) {
    int nfields = 4;

    std::ifstream file;
    file.open(filename);

    std::string line;
    std::vector<std::string> fields(nfields, "");

    getline(file, line); //consumir cabeçalho

    while (getline(file, line)) {

        std::istringstream s(line);

        for (int i = 0; i < nfields; i++)
            getline(s, fields[i], ',');

        Estudante estudante(fields[0], fields[1]);

        Turma turma(fields[2],
                    fields[3].substr(0,fields[3].size()-1)); //for some reason a whitespace is being read after class code...

        auto es = estudantes.insert(estudante);
        es.first->addUCTurma(turma);
        auto it = turmas.find(UCTurma(turma.getCodUC(), turma.getCodTurma()));
        if(it == turmas.end()) std::cout << 1 <<std::endl;
                it->inscrever();
    }

}

void GestorHorarios::read_ucs(std::string filename) {
    int nfields = 2;

    std::ifstream file;
    file.open(filename);

    std::string line;
    std::vector<std::string> fields(nfields, "");

    getline(file, line); //consumir cabeçalho

    while (getline(file, line)) {

        std::istringstream s(line);

        for (int i = 0; i < nfields; i++) getline(s, fields[i], ',');

        turmas.insert(UCTurma(fields[0],
                              fields[1].substr(0,fields[1].size()-1))); //for some reason a whitespace is being read after class code...
    }
}

void GestorHorarios::read_classes(std::string filename) {
    int nfields = 6;

    std::ifstream file;
    file.open(filename);

    std::string line;
    std::vector<std::string> fields(nfields, "");

    getline(file, line); //consumir cabeçalho

    while (getline(file, line)) {

        std::istringstream s(line);

        for (int i = 0; i < nfields; i++) getline(s, fields[i], ',');

        auto it = horario_turmas.insert(UCTurmaSchedule(fields[1], fields[0]));
        Aula aula(fields[2], std::stod(fields[3]),std::stod(fields[4]),fields[5]);
        it.first->addAula(aula);
    }
}


void GestorHorarios::list_sort_getcomp(int i, std::function<bool(const Estudante &, const Estudante &)> &cmp) {
    switch(i){
        case 0: cmp = [    ](const Estudante &p1, const Estudante &p2){ return p1.get_codigo() < p2.get_codigo(); }; break;
        case 1: cmp = [    ](const Estudante &p1, const Estudante &p2){ return p1.get_nome() < p2.get_nome(); }; break;
        case 2: cmp = [    ](const Estudante &p1, const Estudante &p2){ return (p1.getHorario().size() < p2.getHorario().size()); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void GestorHorarios::list_sort_getcomp(int i, std::function<bool(const UCTurma&, const UCTurma&)> &cmp) {
    switch(i){
        case 0: cmp = [    ](const UCTurma &p1, const UCTurma &p2){ return p1 < p2;}; break;
        case 1: cmp = [    ](const UCTurma &p1, const UCTurma &p2){ return p1.getInscritos() < p2.getInscritos(); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void GestorHorarios::list_filter_getvalid(int i, const std::string &str, std::function<bool(const UCTurma &)> &cmp) {
    switch(i) {
        case 0 : cmp = [str](const UCTurma &p) { return (std::string(p.getCodUC()).find(str) != std::string::npos); }; break;
        case 1 : cmp = [str](const UCTurma &p) { return (std::string(p.getCodTurma()).find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}


void GestorHorarios::list_filter_getvalid(int i, const std::string &str, std::function<bool(const Estudante &)> &cmp) {
    switch(i) {
        case 0 : cmp = [str](const Estudante &p) { return (std::string(p.get_codigo()).find(str) != std::string::npos); }; break;
        case 1 : cmp = [str](const Estudante &p) { return (std::string(p.get_nome()).find(str) != std::string::npos); }; break;
        default: throw std::invalid_argument("NUM outside range");
    }
}

void GestorHorarios::list_filter_getvalid(int i, const Turma &trm, std::function<bool(const Estudante &)> &cmp) {
    cmp = [trm](const Estudante &p) {return p.hasClass(trm);};
}

template<class T>
void GestorHorarios::list(std::vector<T> &v) const {
    const std::vector<T> original = v;
    while(true){
        // CLEAR();
        //print_list(v, t);
        // list_commands<T>(t);
        std::vector<std::string> s = {"sort", "2"};
        if(s.size() >= 1){
            //====SORT==========================================================
            if(s[0] == "sort"){
                if(s.size() != 2){ utils::error("wrong number of arguments"); continue; }
                int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid NUM"); continue; }
                std::function<bool(const T&, const T&)> cmp;
                try{
                    list_sort_getcomp(i, cmp);
                    utils::mergesort(v,cmp);
                }catch(const std::invalid_argument &e){ utils::error(e.what()); }
            }else
                //====SEARCH========================================================
            if(s[0] == "search"){
                if(s.size() != 3){ utils::error("wrong number of arguments"); continue; }
                int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid NUM"); continue; }
                std::function<bool(const T&)> cmp;
                try{
                    list_filter_getvalid(i, s[2], cmp);
                    v = utils::filter(v,cmp);
                }catch(const std::invalid_argument &e){ utils::error(e.what()); }
            }else
                //====RESET=========================================================
            if(s[0] == "reset"){
                if(s.size() != 1) utils::error("wrong number of arguments");
                else              v = original;
            }else
                //====BACK==========================================================
            if(s[0] == "back"){
                if(s.size() != 1) utils::error("wrong number of arguments");
                else              return;
            }else utils::error("unrecognized command");
        }
    }
}

bool GestorHorarios::isCompatible(Pedido &p, std::vector<Turma> &res) {

    std::vector<Turma> t;
    for(auto x : p.estudante->getHorario())
        t.push_back(x);

    for(auto x : p.get_a_remover())
        t.erase(std::find(t.begin(), t.end(),x));

    for(auto x : p.get_a_adicionar())
        t.push_back(x);

    auto a = getAulas(t);

    for(int i = 0; i < a.size(); i++){
        for(int j = i+1; j < a.size()-1; j++){
            if(a.at(i).overlaps(a.at(j)) && a.at(i).type == a.at(j).type)
                return false;
        }
    }

    res = t; return true;
}

std::vector<Aula> GestorHorarios::getAulas(const std::vector<Turma> &t) const{
    std::vector<Aula> ret;

    for(auto x : t){
        std::vector<Aula> a = horario_turmas.find(UCTurmaSchedule(x.getCodUC(), x.getCodTurma()))->horario;
        for(auto h : a)
            ret.push_back(h);
    }

    return ret;
}

bool GestorHorarios::canEnroll(const Pedido &p) {

    auto a = p.get_a_adicionar();

    for(auto turma : a){

        UCTurma t = *turmas.find(UCTurma(turma));
        if(t.getInscritos()+1 >= t.cap) return false;

        std::vector<UCTurma> aux = getTurmas(turma.getCodUC());
        int maxdiff = maxDifference(aux);

        int i = std::find(aux.begin(), aux.end(), UCTurma(turma))->inscrever();

        if(maxdiff >= 4){
            if(maxDifference(aux) > maxdiff)
                return false;
        }
    }

    return true;
}

std::vector<UCTurma> GestorHorarios::getTurmas(std::string codUC) {

    std::vector<UCTurma> ret;

    auto is_UC = [codUC](const UCTurma &t) {return t.getCodUC() == codUC;};

    auto it = std::find_if(turmas.begin(), turmas.end(), is_UC);

    do {
        ret.push_back(*it);
    } while(is_UC(*(++it)));

    return ret;
}

int GestorHorarios::maxDifference(const std::vector<UCTurma> &v) const {

    int minElement = v.at(0).getInscritos();
    int maxDiff = v.at(1).getInscritos() - v.at(0).getInscritos();

    for(int i = 1; i < v.size(); i++){

        if(v.at(i).getInscritos() - minElement> maxDiff)
            maxDiff = v.at(i).getInscritos() - minElement;

        if(v.at(i).getInscritos() < minElement)
            minElement = v.at(i).getInscritos();
    }

    return maxDiff;
}

void GestorHorarios::processPedido(Pedido &p) {
    std::vector<Turma> res;

    if(canEnroll(p) && isCompatible(p, res)){
        p.estudante->setHorario(res);
    }
}
