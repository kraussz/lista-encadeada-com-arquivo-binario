#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#define MAXS 51

    typedef struct{
        char* name[MAXS];
    }Data_professor;

    typedef struct{
        int code;
        Data_professor data_professor;

        int next;
    }professor;

    void writeprofessor(FILE* fb, professor* c, int pos);

    professor* readprofessor(FILE* fb, int pos);

    int insertprofessor_bin(FILE* fb, professor* c, int next_pos);

    void cadastrarprofessor(FILE* fbprofessor, FILE* fbcomando);

    void lerarquivotextoprofessor(FILE* fbprofessor, FILE* fbcomando);

    void inserirNaCabecaprofessor(FILE* fbcomando, professor* m);


    void printprofessor(FILE* fbprofessor, FILE* fbcomando);

    void printNodeprofessor(FILE* fbprofessor, int pos);

void printNodeprofe(FILE* fbprofessor, int pos);

void printprofe(FILE* fbprofessor, FILE* fbcomando);

int existeProfessor(FILE* fbcomando, professor* new_c);

int insertprofessor_inOrder(FILE* fbcomando, professor* new_m, int pos);