#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXS 51

    typedef struct{
        char name[MAXS];
        char area;
    }Data_comando;

    typedef struct{
        int code;
        Data_comando data_comando;

        int next;
    }comando;

    void writecomando(FILE* fb, comando* m, int pos);

    comando* readcomando(FILE* fb, int pos);

    int insercomando_bin(FILE* fb, comando* m, int next_pos);

    void cadastrarCurso(FILE* fbcomando);

    void insertcomando(FILE* fbcomando, comando* m);

    
    int insertcomando_inOrder(FILE* fbcomando, comando* new_m, int pos);
    
    void lerArquivoTexto(FILE* fr, FILE* fbcomando);

    void lerArquivoTextoCurso(FILE* fr, FILE* fbcomando);

    void inserirNaCabeca(FILE* fbcomando, comando* m);

    void printcomando(FILE* fbcomando);

    void printNodecomando(FILE* fbcomando, int pos);

    int searchcomando(FILE* fbcomando, int key);

    int existeCurso(FILE* fbcomando, comando* new_m);