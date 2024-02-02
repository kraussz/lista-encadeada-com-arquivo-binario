#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "disciplina.h"
#include "curso.h"
#include "cabecalho.h"

    void writeCourse(FILE* fb, Course* c, int pos){
        fseek(fb, sizeof(cabeca) + sizeof(Course)*pos, SEEK_SET);
        fwrite(c, 1, sizeof(Course), fb);
    }

    Course* readCourse(FILE* fb, int pos){
        Course* c = (Course*)malloc(sizeof(Course));

        fseek(fb, sizeof(cabeca) + sizeof(Course)*pos, SEEK_SET);
        fread(c, 1, sizeof(Course), fb);

        return c;
    }

    int insertCourse_bin(FILE* fb, Course* c, int next_pos){
        cabeca* h = readcabeca(fb);
        int insert_pos;

        c->next = next_pos;

        if(h->posLoose == -1){
            insert_pos = h->posTop;
            writeCourse(fb, c, h->posTop);
            h->posTop++;
        }
        else{
            insert_pos = h->posLoose;
            Course* cLoose = readCourse(fb, h->posLoose);
            writeCourse(fb, c, h->posLoose);    
            h->posLoose = cLoose->next;
            free(cLoose);
        }

        if(h->posHead == next_pos) h->posHead = insert_pos;
        writecabeca(fb, h);
        free(h);

        return insert_pos;
    }

    void cadastrarDisciplina(FILE* fbCourse, FILE* fbcomando){
        Course* c = (Course*)malloc(sizeof(Course));

        printf("\n*Cadastrar Disciplina*\n\n");

        printf("-> Digite o codigo da disciplina: ");
        scanf("%d%*c", &c->code);

        printf("-> Digite o nome da disciplina: ");
        scanf("%[^\n]%*c", c->data_course.name);
        c->data_course.name[50] = '\0';

        
        printf("-> Digite o codigo do curso a qual a disciplina pertence: ");
        scanf("%d%*c", &c->data_course.comando_code);

        printf("-> Digite a serie da disciplina: ");
        scanf("%d%*c", &c->data_course.serie);
        if(!existeDisciplina(fbcomando,c)){
        inserirNaCabecadiciplina(fbcomando,c);
        }
        free(c);
    }

        void lerarquivotextodiciplina(FILE* fbCourse, FILE* fbcomando){
        Course* c = (Course*)malloc(sizeof(Course));


        fscanf(fbCourse,"%d;", &c->code);        
        fscanf(fbCourse,"%[^;]%*c", c->data_course.name);
        fscanf(fbCourse,"%d;", &c->data_course.comando_code);
        fscanf(fbCourse,"%d\n", &c->data_course.serie);
            if(!existeDisciplina(fbcomando,c)){
                inserirNaCabecadiciplina(fbcomando,c);
            }
        free(c);
    }

    void insertCourse(FILE* fbCourse, FILE* fbcomando, Course* c){
        cabeca* h = readcabeca(fbCourse);

        //insertCourse_inOrder(fbCourse, fbcomando, c, h->posHead);

        free(h);
    }
    void inserirNaCabecadiciplina(FILE* fbcomando, Course* m){
        cabeca* h = readcabeca(fbcomando);

        m->next = h->posHead;

        if(h->posLoose == -1){
          

            writeCourse(fbcomando, m, h->posTop);

            h->posHead = h->posTop;
            h->posTop++;
        }
        else{
            Course* mLoose = readCourse(fbcomando, h->posLoose);

            writeCourse(fbcomando, m, h->posLoose);

            h->posLoose = mLoose->next;            

            free(mLoose);
        }
        writecabeca(fbcomando, h);

        free(h);
        }

    int insertCourse_inOrder(FILE* fbCourse, FILE* fbcomando, Course* new_c, int pos){
        if(pos == -1){
            int insert_pos = insertCourse_bin(fbCourse, new_c, pos);
            return insert_pos;
        }
        else{
            Course* c = readCourse(fbCourse, pos);

            if(c->data_course.comando_code > new_c->data_course.comando_code ||
            ((c->data_course.comando_code == new_c->data_course.comando_code) &&
            (c->code > new_c->code))){
                int insert_pos = insertCourse_bin(fbCourse, new_c, pos);
                free(c);
                return insert_pos;
            }
            else{
                c->next = insertCourse_inOrder(fbCourse, fbcomando, new_c, c->next);
                writeCourse(fbCourse, c, pos);
                free(c);
                return pos;
            }
        }
    }

    void printCourse(FILE* fbCourse, FILE* fbcomando){
        printf("\n*LISTA DE DISCIPLINAS*\n\n");

        cabeca* h = readcabeca(fbCourse);

        if(h->posHead != -1){
            printf("%-10s%-60s%-10s%-60s\n", "COD", "NOME", "SERIE","comando_CODE");
            printCourse_aux(fbCourse, fbcomando, h->posHead);
          //  printNodeCourse(fbCourse, h->posHead);
        }
        else printf("\nNAO HA DISCIPLINAS CADASTRADAS...\n\n");

        free(h);
    }

    void printNodeCourse(FILE* fbCourse, int pos){
        if(pos != -1){
            Course* c = readCourse(fbCourse, pos);
            int posNext = c->next;

            printf("%-5d%-10d%-60s%-5d\n", c->data_course.comando_code, c->code, c->data_course.name, c->data_course.serie);

            free(c);
            
            printNodeCourse(fbCourse, posNext);
        }
    }

    void printCourse_aux(FILE* fbCourse, FILE* fbcomando, int pos){
        if(pos != -1){
            Course* c = readCourse(fbCourse, pos);
            int comando_code = c->data_course.comando_code;
            int c_next = -1;

            comando* m = readcomando(fbcomando, searchcomando(fbcomando, comando_code));
            
            

            while(c->data_course.comando_code == comando_code){
                printf("%-10d%-60s%-10d%-60d\n", c->code, c->data_course.name, c->data_course.serie,c->data_course.comando_code);

                c_next = c->next;
                if(c_next == -1) break;
                c = readCourse(fbCourse, c_next);
            }

            free(m);
            free(c);
            printCourse_aux(fbCourse, fbcomando, c_next);
        }
    }

       void printNodedisci(FILE* fbmatricula, int pos){
        if(pos != -1){
            Course* c = readCourse(fbmatricula, pos);
            int posNext = c->next;

            printf("%-10d%-60s\n",c->code,c->data_course.name);

            free(c);
            
            printNodedisci(fbmatricula, posNext);
        }
    }


    void printcurso(FILE* fbCourse, FILE* fbcomando){
        printf("\n*LISTA DE DISCIPLINAS*\n\n");

        cabeca* h = readcabeca(fbCourse);

        if(h->posHead != -1){
            printf("%-10s%-60s\n", "COD", "NOME");
          printNodedisci(fbCourse, h->posHead);
        }
        else printf("\nNAO HA DISCIPLINAS CADASTRADAS...\n\n");

        free(h);
    }

    int existeDisciplina(FILE* fbcomando, Course* new_c) {
  cabeca* h = readcabeca(fbcomando);
  Course* cAux = NULL;
  int posAux = h->posHead;

  // encontrar a posicao do nó
  while(posAux != -1 && ((cAux = readCourse(fbcomando, posAux)) != NULL && 
             cAux->code != new_c->code)){
            posAux = cAux->next;
            free(cAux);
            cAux = NULL;
  }

  free(h);

  return (posAux != -1); // se a posicao for -1, o registro nao existe
}
