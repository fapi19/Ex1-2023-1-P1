/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: PC
 *
 * Created on 2 de octubre de 2023, 17:42
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Preg1_Funciones_de_cursos_y_alumnos.h"

/*
 * 
 */
int main(int argc, char** argv) {
    char ***cursos, ***alumnos_nom_mod;
    double *cursos_cred, escalas[5];
    int *alumnos_cod, **alumnos;
    cargarCursosYEscalas(cursos, cursos_cred, escalas, "Cursos.csv",
            "Escalas.csv");
    pruebaDeCargaDeCursos(cursos, cursos_cred, "PruebaCursos.txt");
    
    cargarAlumnos(alumnos_cod, alumnos, alumnos_nom_mod, "Alumnos.csv");
    pruebaDeCargaDeAlumnos( alumnos_cod, alumnos, alumnos_nom_mod,
            "PruebaAlumnos.txt");
    int ***cursos_nota_sem_veces;
    double **costos;
    char ***cursos_cod;
    cargarNotas(cursos_cod, cursos_nota_sem_veces, costos, alumnos, 
            alumnos_nom_mod, escalas, cursos, cursos_cred,
            "HistoriaDeNotas.csv");
    
    return 0;
}

