#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "cabecalho.h"

    void writecabeca(FILE* fb, cabeca* h){
        fseek(fb, 0, SEEK_SET);
        fwrite(h, 1, sizeof(cabeca), fb);
    }

    cabeca* readcabeca(FILE* fb){
        cabeca* h = (cabeca*)malloc(sizeof(cabeca));

        fseek(fb, 0, SEEK_SET);
        fread(h, 1, sizeof(cabeca), fb);

        return h;
    }

    void initializecabeca(FILE* fb){
        cabeca* h = (cabeca*)malloc(sizeof(cabeca));

        h->posHead = -1;
        h->posLoose = -1;
        h->posTop = 0;

        writecabeca(fb, h);

        free(h);
    }