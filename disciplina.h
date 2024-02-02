#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXS 51

    typedef struct{
        char* name[MAXS];
        int comando_code;
        int serie;
    }Data_Course;

    typedef struct{
        int code;
        Data_Course data_course;

        int next;
    }Course;

    void writeCourse(FILE* fb, Course* c, int pos);

    Course* readCourse(FILE* fb, int pos);

    int insertCourse_bin(FILE* fb, Course* c, int next_pos);

    void cadastrarDisciplina(FILE* fbCourse, FILE* fbMajor);

    void lerarquivotextodiciplina(FILE* fbCourse, FILE* fbMajor);

    void inserirNaCabecadiciplina(FILE* fbMajor, Course* m);

    int insertdisciplina_inOrder(FILE* fbMajor, Course* new_m, int pos);

    void printCourse(FILE* fbCourse, FILE* fbMajor);

    void printNodeCourse(FILE* fbCourse, int pos);

    void printCourse_aux(FILE* fbCourse, FILE* fbMajor, int pos);

    void printNodedisci(FILE* fbmatricula, int pos);

    void printcurso(FILE* fbCourse, FILE* fbMajor);

    int existeDisciplina(FILE* fbMajor, Course* new_c);