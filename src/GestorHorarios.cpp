//
// Created by afonsusousa on 10/29/22.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include "../include/GestorHorarios.h"
#include "../include/utils.h"



GestorHorarios::GestorHorarios() {
    read_ucs("../data/classes_per_uc.csv");
    read_classes("../data/classes.csv");
    read_students("../data/students_classes.csv");



    Pedido p = criarPedido();

    std::cout << estudantes.begin()->getHorario().size() << std::endl;

    processPedido(p);

    std::cout << estudantes.begin()->getHorario().size() << std::endl;

}

std::string GestorHorarios::prompt() const {
    std::cout << OPSTR;
    std::string ret;
    std::getline(std::cin, ret);
    return ret;
}

std::string GestorHorarios::prompt(std::string s) const {
    std::cout << s;
    std::string ret;
    std::getline(std::cin, ret);
    return ret;
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
        Aula aula(Turma(fields[1], fields[0]),fields[2], std::stod(fields[3]),std::stod(fields[4]),fields[5]);
        it.first->addAula(aula);
    }
}



bool GestorHorarios::isCompatible(Pedido &p) {

    std::vector<Turma> t = p.getCandidate();

    auto a = getAulas(t);

    for(int i = 0; i < a.size(); i++){
        for(int j = i+1; j < a.size()-1; j++){
            if(a.at(i).overlaps(a.at(j)) && a.at(i).type == a.at(j).type)
                return false;
        }
    }

    return true;
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

        std::find(aux.begin(), aux.end(),(UCTurma(turma)))->inscrever();

        if(maxdiff >= 4){
            if(maxDifference(aux) > maxdiff) {
                return false;
            }
        }
    }

    return true;
}

std::vector<UCTurma> GestorHorarios::getTurmas(std::string codUC) {

    std::vector<UCTurma> ret;

    auto is_UC = [codUC](const UCTurma &t) {return t.getCodUC() == codUC;};

    auto first = std::find_if(turmas.begin(), turmas.end(), is_UC);
    auto last = std::find_if(turmas.rbegin(), turmas.rend(), is_UC);

    for(auto x = first; x->getCodTurma() != last->getCodTurma(); x++)
        ret.push_back(*x);

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

    if(canEnroll(p)){
        p.estudante->setHorario(p.getCandidate());
    }
}








