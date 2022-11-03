//
// Created by afonsusousa on 10/29/22.
//

#ifndef TRABALHO_GESTORHORARIOS_H
#define TRABALHO_GESTORHORARIOS_H

#include <functional>
#include <queue>
#include "Estudante.h"
#include "UCTurmaSchedule.h"
#include "UC.h"
#include "Pedido.h"
#include <set>

class GestorHorarios {
public:
    GestorHorarios();
    std::set<Estudante> estudantes;
    std::set<UCTurmaSchedule> horario_turmas;
    std::set<UCTurma> turmas;
    std::queue<Pedido> pedidos;

private:


    static void list_sort_getcomp(int i, std::function<bool(const UCTurma&, const UCTurma&)> &cmp);
    static void list_filter_getvalid(int i, const std::string &str, std::function<bool(const UCTurma&)> &cmp);

    static void list_sort_getcomp(int i, std::function<bool(const Estudante&, const Estudante&)> &cmp);
    static void list_filter_getvalid(int i, const std::string &str, std::function<bool(const Estudante &)> &cmp);
    static void list_filter_getvalid(int i, const Turma &trm, std::function<bool(const Estudante &)> &cmp);
    template<class T> void list(std::vector<T> &v) const;

    void processPedido(Pedido &p);
    bool isCompatible(Pedido &p);
    bool canEnroll(const Pedido &p);
    std::vector<Aula> getAulas(const std::vector<Turma> &t) const;
    std::vector<UCTurma> getTurmas(std::string codUC);
    void print_list(const std::set<Estudante> &v);
    void print_list(std::vector<UCTurma>);
    void print_list(std::vector<Aula>);

    int maxDifference(const std::vector<UCTurma> &v) const;


    void read_ucs(std::string filename);
    void read_students(std::string filename);
    void read_classes(std::string filename);
};


#endif //TRABALHO_GESTORHORARIOS_H
