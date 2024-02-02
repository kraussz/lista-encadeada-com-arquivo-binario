#include <stdio.h>
#include <string.h>
#include <stdlib.h>

    typedef struct{
        int posHead;
        int posLoose;
        int posTop;
    }cabeca;

    void writecabeca(FILE* fb, cabeca* h);

    cabeca* readcabeca(FILE* fb);

    void initializecabeca(FILE* fb);

