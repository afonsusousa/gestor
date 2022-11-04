//
// Created by afonsusousa on 10/29/22.
//

#include "../include/Estudante.h"
#include <algorithm>
#include <functional>

Estudante::Estudante(std::string codigo, std::string nome) : codigo(codigo), nome(nome){}

bool Estudante::operator<(const Estudante &e) const{
    return this->codigo < e.codigo;
}

Estudante::Estudante() {

}


bool Estudante::operator==(const Estudante &e) const {
    return codigo == e.codigo;
}

void Estudante::addUCTurma(Turma t) const {
    horario.push_back(t);
}

std::vector<Turma> Estudante::getHorario() const{
    return horario;
}

std::string Estudante::get_codigo() const {
    return codigo;
}

std::string Estudante::get_nome() const {
    return nome;
}

bool Estudante::hasClass(const Turma &t) const{

    return std::find_if(horario.begin(), horario.end(),
                        [t] (const Turma &p) {return t.getCodUC() == p.getCodUC() && t.getCodTurma() == p.getCodTurma();}) != horario.end();
}

Estudante::Estudante(std::string codigo) : codigo(codigo) {

}

void Estudante::setHorario(std::vector<Turma> t) const {
    horario = std::move(t);
}

std::ostream &operator<<(std::ostream &os, const Estudante &n) {
    for(auto x : n.getHorario()){
        os << n.get_codigo() << std::string(",")
        << n.get_nome() << std::string(",")
        << x.getCodUC() << std::string(",")
        << x.getCodTurma() << std::string ("\n");
    }
    return os;
}
