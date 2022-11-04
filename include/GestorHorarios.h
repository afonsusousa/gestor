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

    /** @brief Obter função de comparação entre UCTurmas
     * @param i Critério a ser comparado
     * @param cmp Referência da função que guardará a função obtida
     * */
    static void get_comp(int i, std::function<bool(const UCTurma&, const UCTurma&)> &cmp);

    /** @brief Obter função de comparação entre Estudantes
     * @param i Critério a ser comparado
     * @param cmp Referência da função que guardará a função obtida
     * */
    static void get_comp(int i, std::function<bool(const Estudante&, const Estudante&)> &cmp);

    /** @brief Obter predicado para filtragem de UCTurma
     * @param i Critério a ser filtrado
     * @param str Valor a filtrar
     * @param cmp Referência da função que guardará a predicado obtido
     * */
    static void get_filter(int i, const std::string &str, std::function<bool(const UCTurma&)> &cmp);

    /** @brief Obter predicado para filtragem de Estudante
     * @param i Critério a ser filtrado
     * @param str Valor a filtrar
     * @param cmp Referência da função que guardará o predicado obtido
     * */
    static void get_filter(int i, const std::string &str, std::function<bool(const Estudante &)> &cmp);

    /** @brief Obter predicado para filtragem de Estudante (por Turma)
     * @param trm Turma a filtrar
     * @param cmp Referência da função que guardará a função selecionada
     * */
    static void get_filter(const UCTurma *trm, std::function<bool(const Estudante &)> &cmp);

    /** @brief Processa pedido
     * @param p Pedido a ser processado
     * */
    bool processPedido(Pedido &p);

    /** @brief Verifica se as turmas do horário resultante de um pedido são compatíveis
     * @param p Pedido a analisar
     * @return Se são compatíveis
     * */
    bool isCompatible(Pedido &p);

    /** @brief Verifica se o estudante se pode inscrever nas turmas desejadas
     * @param p Pedido a analisar
     * @return Se a inscrição é possível
     * */
    bool canEnroll(const Pedido &p);

    /** @brief Analisa a diferença máxima entre no nº de inscritos em cada turma
     * @param v Turmas
     * @return Diferença máxima
     * */
    int maxDifference(const std::vector<UCTurma> &v) const;

    /** @brief Procura as aulas de um horário
     * @param t Horário (turmas)
     * @return Aulas do Horário
     * */
    std::vector<Aula> getAulas(const std::vector<Turma> &t) const;

    /** @brief Procura turmas de determinada UC
     * @param codUC UC a procurar
     * @return Turmas da UC
     * */
    std::vector<UCTurma> getTurmas(std::string codUC);

    /** @brief Esccolher estudante
     * @return Estudante escolhido
     * */
    const Estudante* escolherEstudante();

    Turma escolherTurma(std::vector<UCTurma> &v);

    /** @brief Esccolher UCTurma
     * @param v Lista de turmas para escolher
     * @return UCTurma escolhida
     * */
    const UCTurma *escolherUCTurma(const std::vector<Turma> &v);

    /** @brief Esccolher UCTurma
     * @return UCTurma escolhida
     * */
    const UCTurma *escolherUCTurma();

    /**@brief Criar novo pedido
     * @return Pedido criado
     * */
    bool criarPedido(Pedido &p);

    /**@brief Imprime menu principal
     * @return Falso no caso de algum erro
     * */
    bool menu();

    /**@brief Imprime Menu de Listagens
     * return Falso no caso de algum erro
     * */
    bool list_menu();

    /**@brief Lê as UCs/Turmas a partir de um ficheiro
     * @param filename Path do ficheiro
     * */
    void read_ucs(std::string filename);

    /**@brief Lê as UCs/Turmas a partir de um ficheiro
     * @param filename Path do ficheiro
     * */
    void read_students(std::string filename);

    /**@brief Lê as UCs/Turmas a partir de um ficheiro
     * @param filename Path do ficheiro
     * */
    void read_classes(std::string filename);

    void write_ucs(std::string filename);
    void write_classes(std::string filename);
    void write_students(std::string filename);

    /**@brief Imprime uma lista de UCTurmas
     * @param v Lista a imprimir
     * */
    void print_list(std::vector<UCTurma>&v);

    /**@brief Imprime horário
     * @param v Horário a imprimir
     * */
    void print_schedule(const std::vector<Aula> &v);

    /**@brief Imprime uma lista de Estudantes
     * @param v Lista a imprimir
     * */
    void print_list(std::vector<Estudante> &v);

    /**@brief Imprime uma lista de Turmas
     * @param v Lista a imprimir
     * */
    void print_list(std::vector<Turma> &v);

    /**@brief Imprime uma lista de Turmas (+ índice)
     * @param v Lista a imprimir
     * */
    void prints_list(std::vector<Turma> &v);

    /**@brief Imprime uma lista de UCTurmas (+ índice)
     * @param v Lista a imprimir
     * */
    void prints_list(std::vector<UCTurma> &v);

    /**@brief Recebe input
     * @return Input
     * */
    std::string prompt() const;

    /**@brief Recebe input
     * @param s Mensagem a imprimir ("shell")
     * @return Input*/
    std::string prompt(std::string s) const;

    /**@brief Lists commands for class*/
    template<class T> static void list_commands();


    /**@brief Imprime listagem, filtra, ordena
     * @param v Lista
     * */
    void list(std::vector<Estudante> &v);

    /**@brief Imprime listagem, filtra, ordena
     * @param v Lista
     * */
    void list(std::vector<UCTurma> &v);
};


#endif //TRABALHO_GESTORHORARIOS_H
