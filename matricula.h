#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXS 51



    typedef struct{
        int codDisciplina;
        int anoLetivo;
        int codProfessor;

        int next;
    }matricula;
    

    void writematricula(FILE* fb, matricula* c, int pos);

    matricula* readmatricula(FILE* fb, int pos);

    int insertmatricula_bin(FILE* fb, matricula* c, int next_pos);

    void cadastrarmatricula(FILE* fbmatricula,FILE* fbprofessor,FILE* fbdisciplina, FILE* fbcomando);

    void lerarquivotextomatricula(FILE* fbmatricula, FILE* fbcomando);

    void inserirNaCabecamatricula(FILE* fbcomando, matricula* m);


    void printmatricula(FILE* fbmatricula, FILE* fbcomando);

    void printNodematricula(FILE* fbmatricula, int pos);

    void removerMatricula(FILE* fbMatricula, FILE* fbCourse, FILE* fbcomando);

    void removerMatricula_bin(FILE* fbMatricula, int codDisciplina, int anoLetivo);

    int insertmatricula_inOrder(FILE* fbcomando, matricula* new_m, int pos);

    int existeMatricula(FILE* fbcomando, matricula* new_m);