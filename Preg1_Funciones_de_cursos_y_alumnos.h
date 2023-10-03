/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Preg1_Funciones_de_cursos_y_alumnos.h
 * Author: PC
 *
 * Created on 2 de octubre de 2023, 17:45
 */

#ifndef PREG1_FUNCIONES_DE_CURSOS_Y_ALUMNOS_H
#define PREG1_FUNCIONES_DE_CURSOS_Y_ALUMNOS_H


void cargarCursosYEscalas( char ***&, double *&, 
        double *, const char *, const char *);
void lecturaCursos(double *, const char *);
void lecturaDatos(char *&,char *& ,double & , 
                int &,char *& ,ifstream &);
char* leerCadena(ifstream &);
void inicializarPunteros( char ***&, double *&);
void incrementarMemoria(char ***&, double *&, int &, int & );
void asignarValores( char **&, double &, char *,
        char *, char *, double );
void pruebaDeCargaDeCursos( char ***, double *, const char *  );
void imprimirCurso(char **, double , ofstream &);
void cargarAlumnos( int *&, int **&, char ***&, const char*);
void leerAlumnos(int &, char *&,char & , int &,int& ,ifstream &);
void asignarDatosAlumno(int &,int  *&,  char **&,int  codigo,char *,char , 
        int , int );
void incrementarEspacio(int *&, int **&,  char ***&, int & , int &);
void pruebaDeCargaDeAlumnos( int *, int **, char ***,  const char*);
void imprimirAlumno( int *,char **,   ofstream &);
void cargarNotas( char ***&, int ***&,
        double **&, int **, char ***, 
        double *, char ***, double *, const char *
                );
void ingresarCurso( char *codCurso, int ciclo, int nota, double *cursos_cred,
        double *valorEscalas, int escalaAlumno, char **&codigoCursos,
        int **&NotaSemVecesCursos, double *&costosCursos, int &nCursos,
       char ***cursos );
double valorCurso( double *valorEscalas, int escalaAlumno, double *cursos_cred,
        char *codCurso,char ***cursos);
int buscarCurso(char ***cursos, char *codCurso);
void lecturaNotas(int &codigoAlumno, char *&codCurso, int &ciclo, int &nota,
        ifstream &input);
int buscarCursoEnAlumno(char *codCurso, char **codigosCursos, int nCursos,
        int &ultimoCiclo, int **NotaSemVecesCursos);
int buscarAlumno( int codigoAlumno, int **alumnos, int &escalaAlumno);
void actualizarCostos(int *&notasemveces,double &costo,
                        int ultimoCiclo,int ciclo, int nota);
#endif /* PREG1_FUNCIONES_DE_CURSOS_Y_ALUMNOS_H */

