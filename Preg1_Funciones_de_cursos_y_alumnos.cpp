/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;
#include "Preg1_Funciones_de_cursos_y_alumnos.h"
#define INCREMENTO 5
void cargarCursosYEscalas( char ***&cursos, double *&cursos_cred, 
        double *arrEscalas, const char *nomcursos, const char *archescalas){
    ifstream input( nomcursos, ios::in);
    if( not input.is_open()){
        cout << "ERROR NO SE PUDO ABRIR EL ARCHIVO "<<nomcursos<<endl;
        exit(1);
    }
    lecturaCursos(arrEscalas, archescalas);
    //MEMORIA INCREMENTAL INICAILIZAMOS LOS PUNTEROS
    inicializarPunteros(cursos, cursos_cred);
    char *codigoCurso, *nombreCurso,*nombreProfesor;
    double creditosCurso;
    int codigoProfesor, nd = 0, cap = 0 ;
    while(true){
        lecturaDatos(codigoCurso, nombreCurso, creditosCurso, 
                codigoProfesor, nombreProfesor,input);
       // cout <<codigoCurso<<endl;
        if(input.eof()) break;
        if(nd ==cap){
            incrementarMemoria(cursos, cursos_cred, nd,cap);
        }
        asignarValores(cursos[nd-1], cursos_cred[nd-1],codigoCurso,
                nombreCurso,nombreProfesor,creditosCurso);
        nd++;
    }
}

void asignarValores( char **&cursos, double &creditos, char *codigoCurso,
        char *nombreCurso, char *nombreProfesor, double creditosCursos){
    creditos = creditosCursos;
    cursos = new char*[3];
    cursos[0] = codigoCurso;
    cursos[1] = nombreCurso;
    cursos[2] = nombreProfesor;
}
void incrementarMemoria(char ***&cursos, double *&cursos_cred, int &nd, int & cap){
    char ***auxCursos;
    double *auxCred;
    cap+=INCREMENTO;
    if(cursos == nullptr){
        cursos = new char **[cap]{};
        cursos_cred = new double [cap]{};
        nd = 1;
    }
    else{
        auxCursos = new char **[cap]{};
        auxCred = new double [cap]{};
        for(int i=0;i<nd;i++){
            auxCursos[i] = cursos[i];
            auxCred[i] = cursos_cred[i];
        }
        delete cursos;
        delete cursos_cred;
        cursos = auxCursos;
        cursos_cred = auxCred;
    }
}
void inicializarPunteros( char ***&cursos, double *&cursos_cred){
    cursos = nullptr;
    cursos_cred = nullptr;
}
void lecturaDatos(char *&codigoCurso,char *& nombreCurso,double & creditosCurso, 
                int &codigoProfesor,char *& nombreProfesor,ifstream &input){
    codigoCurso = leerCadena(input);
    if(input.eof()) return;
    nombreCurso = leerCadena(input);
    input >> creditosCurso;
    input.get();
    input >> codigoProfesor;
    input.get();
    nombreProfesor = leerCadena(input);
}

char* leerCadena(ifstream &input){
    char buffer[150],*cad;
    input.getline(buffer,150,',');
    cad = new char[strlen(buffer)+1];
    strcpy(cad, buffer);
    return cad;
}
void lecturaCursos(double *arrEscalas, const char *archescalas){
    ifstream escalas( archescalas, ios::in);
    if( not escalas.is_open()){
        cout << "ERROR NO SE PUDO ABRIR EL ARCHIVO "<<archescalas<<endl;
        exit(1);
    }
    int pos;
    double valorCredito;
    char car;
    while(true){
        escalas>>car;
        if(escalas.eof()) break;
        escalas >> pos;
        escalas.get();
        escalas >> valorCredito;
        arrEscalas[pos-1] = valorCredito;
    }
}

void pruebaDeCargaDeCursos( char ***cursos, double *cursos_cred, const char *
                                nombArch){
    ofstream output(nombArch, ios::out);
    if( not output.is_open()){
        cout << "ERROR: No se puede abrir el archivo "<<nombArch <<endl;
        exit(1);
    }
    for(int i=0;cursos[i];i++){
        imprimirCurso(cursos[i], cursos_cred[i],output);
    }
}

void imprimirCurso(char **curso, double credito, ofstream &output){
    char *codigo = curso[0];
    char *nombreCurso = curso[1];
    char *nombreProfesor = curso[2];
    output << setprecision(2);
    output <<fixed;
    output << left << setw(12)<<codigo  <<setw(3)<<" "<<
            setw(40)<<nombreCurso <<setw(3)<<" "
            <<
            setw(40)<< nombreProfesor << right << setw(6)<< credito;
}


void cargarAlumnos( int *&alumnos_cod, int **&alumnos, char ***&alumnos_nom_mod,
        const char*nomArch){
    ifstream input( nomArch, ios::in);
    if( not input.is_open()){
        cout << "ERROR: No se pudo abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    alumnos_cod = nullptr;
    alumnos = nullptr;
    alumnos_nom_mod = nullptr;
    int nd = 0, cap = 0;
    int codigo;
    int escala, porcentaje = 0;
    char *nombre, modalidad;
    while( true ){
        porcentaje = 0;
        leerAlumnos(codigo, nombre, modalidad, porcentaje, escala,input);
        if(input.eof()) break;
        if(nd == cap){
            incrementarEspacio(alumnos_cod, alumnos, alumnos_nom_mod,
                    nd,cap);
        }
        asignarDatosAlumno(alumnos_cod[nd-1], alumnos[nd-1], 
                alumnos_nom_mod[nd-1], codigo, nombre, modalidad, porcentaje,
                escala);
        nd++;
    }
    
}

void incrementarEspacio(int *&alumnos_cod, int **&alumnos, 
        char ***&alumnos_nom_cod, int &nd , int &cap){
    int *auxAlumnos_cod;
    int **auxAlumnos;
    char ***auxAlumnos_nom_cod;
    cap+=INCREMENTO;
    if( alumnos_cod == nullptr){
        alumnos_cod = new int [cap]{};
        alumnos = new int*[cap]{};
        alumnos_nom_cod = new char **[cap]{};
        nd = 1;
    }
    else{
        auxAlumnos_cod = new int [cap]{};
        auxAlumnos = new int*[cap]{};
        auxAlumnos_nom_cod = new char **[cap]{};
        for(int i=0;i<nd;i++){
            auxAlumnos_cod[i] = alumnos_cod[i];
            auxAlumnos[i] = alumnos[i];
            auxAlumnos_nom_cod[i] = alumnos_nom_cod[i];
        }
        delete alumnos_cod;
        delete alumnos;
        delete alumnos_nom_cod;
        alumnos_cod = auxAlumnos_cod;
        alumnos = auxAlumnos;
        alumnos_nom_cod = auxAlumnos_nom_cod;
    }
}
void leerAlumnos(int &codigo, char *&nombre,char & modalidad,
        int &porcentaje,int& escala,ifstream &input){
    char car;
    input >> codigo;
    if( input.eof()) return;
    input.get() ;
    nombre = leerCadena(input);
    input >> modalidad;
    if(modalidad == 'S' or modalidad == 'V'){
        if(modalidad == 'S'){
            input.get();
            input >> porcentaje;
            input.get();
            input >> car>> escala;  /// CAR PARA EL G Y ESCALA PARA EL NUMERO
        }else{
            input.get();
            input >> car >> escala;
        }       
    }
    else{
        // en este caso la modalidad agarro el valor de ',' ya que no hay modalidad
        //entonces modalidad es presencial
        // modalidad == 'G'
        modalidad = 'P';  // p de presencial
        input >> escala;
    }
}

void asignarDatosAlumno(int &codigoAlumno,int  *&alumno,   
        char **&alumnos_nom_mod,int  codigo,char *nombre,char modalidad, 
        int porcentaje, int escala){
    codigoAlumno = codigo;
    if(modalidad == 'S'){
        // se reserva mas memoria
        alumno = new int[3];
        alumno[0] = codigo;
        alumno[1] = escala;
        alumno[2] = porcentaje;
    }
    else{
        // solo se reseva 2
        alumno = new int[2];
        alumno[0] = codigo;
        alumno[1] = escala;
    }
    alumnos_nom_mod = new char *[2];
    alumnos_nom_mod[0] = nombre;
    alumnos_nom_mod[1] = new char;
    char *aux = alumnos_nom_mod[1] ;
    *aux = modalidad;
}

void pruebaDeCargaDeAlumnos( int *alumnos_cod, int **alumnos, 
        char ***alumnos_nom_mod,  const char*nomArch){
    ofstream output(nomArch, ios::out);
    if( not output.is_open()){
        cout << "ERROR: No se pudo abrir el archivo "<<nomArch<<endl;
        exit(1);
    }
    
    for(int i=0; alumnos_cod[i];i++){
        imprimirAlumno(alumnos[i],alumnos_nom_mod[i], output);
    }
}

void imprimirAlumno( int *alumno,char **nombremodalidad,
                ofstream &output){
    output << alumno[0]<<setw(4)<<alumno[1]<< setw(5) << " ";
    output << nombremodalidad[0] << setw(5)<<*nombremodalidad[1];
    output << endl;
}
/*202123703,MEC270,202302,14
202315643,MEC270,202202,13*/
void cargarNotas( char ***&cursos_cod, int ***&cursos_nota_sem_veces,
        double **&costos, int **alumnos, char ***alumnos_nom_mod, 
        double *escalas, char ***cursos, double *cursos_cred, const char *
                nomArch){
    ifstream input(nomArch,ios::in);
    if( not input.is_open()){
        cout << "ERROR: No se pudo abrir el archivo "<<nomArch;
        exit(1);
    }
    
    //MEM EXACTA
    char **bufferCod[200]{};
    int **bufferNotaSemVeces[200]{}, nDatos = 0;
    double *bufferCostos[200]{};
    int codigoAlumno, nota, ciclo,posAlumno,posCurso, escalaAlumno;
    char *codCurso;
    int nCursos[200]{},ultimoCiclo;
    while(true){
        lecturaNotas(codigoAlumno, codCurso, ciclo, nota,input);
        if(input.eof()) break;
        posAlumno = buscarAlumno(codigoAlumno, alumnos, escalaAlumno);
        if(posAlumno!=-1){// ya se en que alumno meterlo, y SI EXISTE
            posCurso = buscarCursoEnAlumno(codCurso, bufferCod[posAlumno],
                nCursos[posAlumno],ultimoCiclo,bufferNotaSemVeces[posAlumno]);
            //cout <<posCurso;
        // si es que no se encuentra se ingresa como uno nuevo
            cout <<posCurso <<endl;
            if(posCurso== -1 ){
                //cout <<posCurso << endl;
                ingresarCurso(codCurso, ciclo, nota, cursos_cred, 
                        escalas, escalaAlumno,
                        bufferCod[posAlumno],bufferNotaSemVeces[posAlumno],
                        bufferCostos[posAlumno],nCursos[posAlumno],cursos);
                for(int i= 0; bufferCod[posAlumno][i];i++){
                    cout << bufferCod[posAlumno][i]<<endl;
                }
            }
//            // aca ya se encontró y se debe actualizar
//            else{
//                int **auxNotaSemVeces = bufferNotaSemVeces[posAlumno];
//                double *auxCostos = bufferCostos[posAlumno];
//                actualizarCostos(auxNotaSemVeces[posCurso],auxCostos[posCurso],
//                        ultimoCiclo,ciclo, nota);
//            }
        }     
    }
}
void ingresarCurso( char *codCurso, int ciclo, int nota, double *cursos_cred,
        double *valorEscalas, int escalaAlumno, char **&codigoCursos,
        int **&NotaSemVecesCursos, double *&costosCursos, int &nCursos,
       char ***cursos ){
    //espacio para maximo 10 Cursos por alumno
    
    codigoCursos = new char *[10]{};
    NotaSemVecesCursos = new int *[10]{};
    codigoCursos[nCursos] = codCurso;
    int *NotaSemVecesCurso = NotaSemVecesCursos[nCursos];
    NotaSemVecesCurso = new int [3];
    NotaSemVecesCurso[0] = nota;
    NotaSemVecesCurso[1] = ciclo;
    NotaSemVecesCurso[2] = 1;
    costosCursos = new double[10]{};
    costosCursos[nCursos] = valorCurso(valorEscalas, escalaAlumno, cursos_cred,
            codCurso,cursos);
    nCursos++;
}
double valorCurso( double *valorEscalas, int escalaAlumno, double *cursos_cred,
        char *codCurso,char ***cursos){
    double valor = 0.0;
    //1ro el valor de la escala;
    double vEscala = valorEscalas[escalaAlumno-1];
    //ahora falta cant creditos
    int posCurso = buscarCurso(cursos, codCurso);
    double vCreditos = cursos_cred[posCurso];
    valor = vCreditos*vEscala;
    return valor;
}

int buscarCurso(char ***cursos, char *codCurso){
    for(int i=0;cursos[i];i++){
        char **aux = cursos[i];
        if( strcmp(codCurso,aux[0]) == 0 ){
            return i;
        }
    }
    
    return -1;
}
void lecturaNotas(int &codigoAlumno, char *&codCurso, int &ciclo, int &nota,
        ifstream &input){
    input >> codigoAlumno;
    if(input.eof()) return;
    input.get();
    codCurso = leerCadena(input);
    input >> ciclo;
    input.get();
    input >> nota;
}
int buscarCursoEnAlumno(char *codCurso, char **codigosCursos, int nCursos,
        int &ultimoCiclo, int **NotaSemVecesCursos){
    
    for(int i=0;i<nCursos;i++){
        char *cursoI = codigosCursos[i];
        //cout << aterrizaje <<endl;
        if(strcmp(cursoI,codCurso) == 0){
            int *aterrizajeAux = NotaSemVecesCursos[i];
            ultimoCiclo = aterrizajeAux[1];
            //cout <<i<<endl;
            return i;
        }
    }
    return -1;
}

int buscarAlumno( int codigoAlumno, int **alumnos, int &escalaAlumno){
    for(int i=0;alumnos[i];i++){
        int *aterrizaje = alumnos[i];
        if( aterrizaje[0] == codigoAlumno){
            escalaAlumno = aterrizaje[1];
            
            return i;
        }
    }
    return -1;
}

void actualizarCostos(int *&notasemveces,double &costo,
                        int ultimoCiclo,int ciclo, int nota){
    if(ciclo > ultimoCiclo){
        // si es mas actual se actualizan la nota y semeestre
        notasemveces[0] = nota;
        notasemveces[1] = ciclo;
    }
    // las veces siempre incrementa asi como el costo por el curso
    
    notasemveces[2]++;
    costo = notasemveces[2] * costo;
}