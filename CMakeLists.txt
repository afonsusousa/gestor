cmake_minimum_required(VERSION 3.24)
project(gestor)

set(CMAKE_CXX_STANDARD 14)

add_executable(gestor
        src/GestorHorarios.cpp
        src/utils.cpp
        src/UCTurmaSchedule.cpp
        src/UCTurma.cpp
        src/Turma.cpp
        src/Pedido.cpp
        src/main.cpp
        src/Estudante.cpp
        src/Aula.cpp
        src/GestorHorarios_display.cpp
        src/GestorHorarios_lists.cpp src/GestorHorarios_cli.cpp)
include_directories("include")

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)