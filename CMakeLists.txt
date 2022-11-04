cmake_minimum_required(VERSION 3.24)
project(gestor)

set(CMAKE_CXX_STANDARD 14)

add_executable(gestor
        src/GestorHorarios.cpp
        src/utils.cpp
        src/UCTurmaSchedule.cpp
        src/UCTurma.cpp
        src/UC.cpp
        src/Turma.cpp
        src/Pedido.cpp
        src/main.cpp
        src/Estudante.cpp
        src/Aula.cpp
        src/GestorHorarios_display.cpp
        src/GestorHorarios_lists.cpp src/GestorHorarios_cli.cpp)
include_directories("include")