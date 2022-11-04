//
// Created by afonsusousa on 10/29/22.
//

#ifndef TRABALHO_GESTORHORARIOS_H
#define TRABALHO_GESTORHORARIOS_H

#if defined(_WIN32)
#define CLEAR_MACRO() system("cls"  )
#elif defined(unix) || defined(__unix__) || defined(__unix)
#define CLEAR_MACRO() system("clear")
#endif

#include <functional>
#include <queue>
#include "Estudante.h"
#include "UCTurmaSchedule.h"
#include "UC.h"
#include "Pedido.h"
#include "utils.h"
#include <set>

const std::string OPSTR = "Operation$ ";

class GestorHorarios {
public:
    GestorHorarios();
    std::set<Estudante> estudantes;
    std::set<UCTurmaSchedule> horario_turmas;
    std::set<UCTurma> turmas;
    std::queue<Pedido> pedidos;

private:
    void CLEAR() const;

    static void get_comp(int i, std::function<bool(const UCTurma&, const UCTurma&)> &cmp);
    static void get_filter(int i, const std::string &str, std::function<bool(const UCTurma&)> &cmp);

    static void get_comp(int i, std::function<bool(const Estudante&, const Estudante&)> &cmp);
    static void get_filter(int i, const std::string &str, std::function<bool(const Estudante &)> &cmp);
    static void get_filter(const Turma &trm, std::function<bool(const Estudante &)> &cmp);


    void processPedido(Pedido &p);
    bool isCompatible(Pedido &p);
    bool canEnroll(const Pedido &p);
    std::vector<Aula> getAulas(const std::vector<Turma> &t) const;
    std::vector<UCTurma> getTurmas(std::string codUC);

    int maxDifference(const std::vector<UCTurma> &v) const;

    const Estudante* escolherEstudante();
    const UCTurma *escolherTurma(const std::vector<Turma> &v);
    const UCTurma *escolherTurma();
    Pedido criarPedido();

    bool editarHorario();



    void read_ucs(std::string filename);
    void read_students(std::string filename);
    void read_classes(std::string filename);

    std::string prompt() const;

    void wait();

    void print_list(std::vector<UCTurma>&v);
    void print_schedule(const std::vector<Aula> &v);
    void print_list(std::vector<Estudante> &v);
    void print_list(std::vector<Turma> &v);



    template<class T>
    void list(std::vector<T> &v) {
        const std::vector<T> original = v;
        while(true){
            CLEAR();
            print_list(v);
            // list_commands<T>(t);
            std::vector<std::string> s = utils::parse_command(prompt());
            if(s.size() >= 1){
                if(s[0] == "sort"){
                    if(s.size() != 2){ utils::error("wrong number of arguments"); continue; }
                    int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid NUM"); continue; }
                    std::function<bool(const T&, const T&)> cmp;
                    try{
                        get_comp(i, cmp);
                        utils::mergesort(v,cmp);
                    }catch(const std::invalid_argument &e){ utils::error(e.what()); }
                }else
                if(s[0] == "search"){
                    if(s.size() != 3){ utils::error("wrong number of arguments"); continue; }
                    int i; try{ i = stoi(s[1]); } catch(const std::invalid_argument &e){ utils::error("invalid NUM"); continue; }
                    std::function<bool(const T&)> cmp;
                    try{
                        get_filter(i, s[2], cmp);
                        v = utils::filter(v,cmp);
                    }catch(const std::invalid_argument &e){ utils::error(e.what()); }
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

    std::string prompt(std::string s) const;
};


#endif //TRABALHO_GESTORHORARIOS_H
