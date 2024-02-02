
#include "cabecalho.h"
#include "professor.h"

    void writeprofessor(FILE* fb, professor* c, int pos){
        fseek(fb, sizeof(cabeca) + sizeof(professor)*pos, SEEK_SET);
        fwrite(c, 1, sizeof(professor), fb);
    }

    professor* readprofessor(FILE* fb, int pos){
        professor* c = (professor*)malloc(sizeof(professor));

        fseek(fb, sizeof(cabeca) + sizeof(professor)*pos, SEEK_SET);
        fread(c, 1, sizeof(professor), fb);

        return c;
    }

    int insertprofessor_bin(FILE* fb, professor* c, int next_pos){
        cabeca* h = readcabeca(fb);
        int insert_pos;

        c->next = next_pos;

        if(h->posLoose == -1){
            insert_pos = h->posTop;
            writeprofessor(fb, c, h->posTop);
            h->posTop++;
        }
        else{
            insert_pos = h->posLoose;
            professor* cLoose = readprofessor(fb, h->posLoose);
            writeprofessor(fb, c, h->posLoose);    
            h->posLoose = cLoose->next;
            free(cLoose);
        }

        if(h->posHead == next_pos) h->posHead = insert_pos;
        writecabeca(fb, h);
        free(h);

        return insert_pos;
    }

    void cadastrarprofessor(FILE* fbprofessor, FILE* fbcomando){
        professor* c = (professor*)malloc(sizeof(professor));

        printf("\n*Cadastrar professor*\n\n");

        printf("-> Digite o codigo da professor: ");
        scanf("%d%*c", &c->code);

        printf("-> Digite o nome da professor: ");
        scanf("%[^\n]%*c", c->data_professor.name);
        c->data_professor.name[50] = '\0';
 if(!existeProfessor(fbcomando,c)){
        inserirNaCabecaprofessor(fbcomando,c);
 }
        free(c);
    }

        void lerarquivotextoprofessor(FILE* fbprofessor, FILE* fbcomando){
        professor* c = (professor*)malloc(sizeof(professor));
        cabeca * h = readcabeca(fbcomando);

        fscanf(fbprofessor,"%d;", &c->code);        
        fscanf(fbprofessor,"%[^\n]%*c", c->data_professor.name);
        if(!existeProfessor(fbcomando,c)){
                insertprofessor_inOrder(fbcomando,c,h->posHead);
        }
        free(c);
    }


    void inserirNaCabecaprofessor(FILE* fbcomando, professor* m){
        cabeca* h = readcabeca(fbcomando);

        m->next = h->posHead;

        if(h->posLoose == -1){
          

            writeprofessor(fbcomando, m, h->posTop);

            h->posHead = h->posTop;
            h->posTop++;
        }
        else{
            professor* mLoose = readprofessor(fbcomando, h->posLoose);

            writeprofessor(fbcomando, m, h->posLoose);

            h->posLoose = mLoose->next;            

            free(mLoose);
        }
        writecabeca(fbcomando, h);

        free(h);
        }



    void printprofessor(FILE* fbprofessor, FILE* fbcomando){
        printf("\n*LISTA DE PROFESSORES*\n\n");

        cabeca* h = readcabeca(fbprofessor);

        if(h->posHead != -1){
            printf("%-10s%-60s\n", "COD", "NOME");
            printNodeprofessor(fbprofessor, h->posHead);

        }
        else printf("\nNAO TEM PROFESSOR\n\n");

        free(h);
    }

    void printNodeprofessor(FILE* fbprofessor, int pos){
        if(pos != -1){
            professor* c = readprofessor(fbprofessor, pos);
            int posNext = c->next;

            printf("%-5d%-10s\n", c->code, c->data_professor.name);

            free(c);
            
            printNodeprofessor(fbprofessor, posNext);
        }
    }

    void printprofe(FILE* fbprofessor, FILE* fbcomando){
        printf("\n*LISTA DE PROFESSORES*\n\n");

        cabeca* h = readcabeca(fbprofessor);

        if(h->posHead != -1){
            printf("%-10s%-60s\n", "COD", "NOME");
            printNodeprofe(fbprofessor, h->posHead);

        }
        else printf("\nNAO TEM PROFESSOR\n\n");

        free(h);
    }

    void printNodeprofe(FILE* fbprofessor, int pos){
        if(pos != -1){
            professor* c = readprofessor(fbprofessor, pos);
            int posNext = c->next;

            printf("%-10d%-60s\n",c->code,c->data_professor.name);

            free(c);
            
            printNodeprofe(fbprofessor, posNext);
        }
    }


 

    int existeProfessor(FILE* fbcomando, professor* new_c) {
  cabeca* h = readcabeca(fbcomando);
  professor* cAux = NULL;
  int posAux = h->posHead;

  // encontrar a posicao do nó
  while(posAux != -1 && ((cAux = readprofessor(fbcomando, posAux)) != NULL && 
             cAux->code != new_c->code)){
            posAux = cAux->next;
            free(cAux);
            cAux = NULL;
  }

  free(h);

  return (posAux != -1); // se a posicao for -1, o registro nao existe
}

int insertprofessor_inOrder(FILE* fbcomando, professor* new_m, int pos){
        if(pos == -1){
            int insert_pos = insertprofessor_bin(fbcomando, new_m, pos);
            return insert_pos;
        }
        else{
            professor* m = readprofessor(fbcomando, pos);

            if(m->code > new_m->code){
                int insert_pos = insertprofessor_bin(fbcomando, new_m, pos);
                free(m);
                return insert_pos;
            }
            else{
                m->next = insertprofessor_inOrder(fbcomando, new_m, m->next);
                writeprofessor(fbcomando, m, pos);
                free(m);
                return pos;
            }
        }
    }