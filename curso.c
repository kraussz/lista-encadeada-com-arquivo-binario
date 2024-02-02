#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "curso.h"
#include "cabecalho.h"

    void writecomando(FILE* fb, comando* m, int pos){
        fseek(fb, sizeof(cabeca) + sizeof(comando)*pos, SEEK_SET);
        fwrite(m, 1, sizeof(comando), fb);
    }

    comando* readcomando(FILE* fb, int pos){
        comando* m = (comando*)malloc(sizeof(comando));

        fseek(fb, sizeof(cabeca) + sizeof(comando)*pos, SEEK_SET);
        fread(m, 1, sizeof(comando), fb);

        return m;
    }

    int insercomando_bin(FILE* fb, comando* m, int next_pos){
        cabeca* h = readcabeca(fb);
        int insert_pos;

        m->next = next_pos;

        if(h->posLoose == -1){
            insert_pos = h->posTop;
            writecomando(fb, m, h->posTop);
            h->posTop++;
        }
        else{
            insert_pos = h->posLoose;
            comando* mLoose = readcomando(fb, h->posLoose);
            writecomando(fb, m, h->posLoose);    
            h->posLoose = mLoose->next;
            free(mLoose);
        }

        if(h->posHead == next_pos) h->posHead = insert_pos;
        writecabeca(fb, h);
        free(h);

        return insert_pos;
    }

    void cadastrarCurso(FILE* fbcomando){
        comando* m = (comando*)malloc(sizeof(comando));

        printf("\n*Cadastrar Curso*\n\n");

        printf("-> Digite o codigo do curso: ");
        scanf("%d%*c", &m->code);

        printf("-> Digite o nome do curso: ");
        scanf("%[^\n]%*c", m->data_comando.name);
        m->data_comando.name[50] = '\0';

        printf("-> Digite a area do curso: ");
        scanf("%c%*c", &m->data_comando.area);

        insertcomando(fbcomando, m);

        free(m);
    }

    void lerArquivoTexto(FILE* fr, FILE* fbcomando){
       
        
        
        
    }

    void lerArquivoTextoCurso(FILE* fr, FILE* fbcomando){
        comando* c = (comando*)malloc(sizeof(comando));

        fscanf(fr, "%d;", &c->code);
        fscanf(fr, "%[^;]%*c", c->data_comando.name);
        fscanf(fr, "%c\n", &c->data_comando.area);
        if(!existeCurso(fbcomando,c)){
        inserirNaCabeca(fbcomando, c);
        }
        free(c);
    }

    void insertcomando(FILE* fbcomando, comando* m){
        cabeca* h = readcabeca(fbcomando);

        inserirNaCabeca(fbcomando, m);

        free(h);
    }

    void inserirNaCabeca(FILE* fbcomando, comando* m){
        cabeca* h = readcabeca(fbcomando);

        m->next = h->posHead;

        if(h->posLoose == -1){
          

            writecomando(fbcomando, m, h->posTop);

            h->posHead = h->posTop;
            h->posTop++;
        }
        else{
            comando* mLoose = readcomando(fbcomando, h->posLoose);

            writecomando(fbcomando, m, h->posLoose);

            h->posLoose = mLoose->next;            

            free(mLoose);
        }

        writecabeca(fbcomando, h);

        free(h);
    }

    int insertcomando_inOrder(FILE* fbcomando, comando* new_m, int pos){
        if(pos == -1){
            int insert_pos = insercomando_bin(fbcomando, new_m, pos);
            return insert_pos;
        }
        else{
            comando* m = readcomando(fbcomando, pos);

            if(m->code > new_m->code){
                int insert_pos = insercomando_bin(fbcomando, new_m, pos);
                free(m);
                return insert_pos;
            }
            else{
                m->next = insertcomando_inOrder(fbcomando, new_m, m->next);
                writecomando(fbcomando, m, pos);
                free(m);
                return pos;
            }
        }
    }

    void printcomando(FILE* fbcomando){
        printf("\n*LISTA DE CURSOS*\n\n");

        cabeca* h = readcabeca(fbcomando);

        if(h->posHead != -1){
            printf("%-10s%-60s%-5s\n", "COD", "NOME", "AREA");

            printNodecomando(fbcomando, h->posHead);
        }
        else printf("\nNAO HA CURSOS CADASTRADOS...\n\n");

        free(h);
    }

    void printNodecomando(FILE* fbcomando, int pos){
        if(pos != -1){
            comando* m = readcomando(fbcomando, pos);
            int posNext = m->next;

            printf("%-10d%-60s%-5c\n", m->code, m->data_comando.name, m->data_comando.area);

            free(m);
            
            printNodecomando(fbcomando, posNext);
        }
    }

    int searchcomando(FILE* fbcomando, int key){
        cabeca* h = readcabeca(fbcomando);
        int pos = h->posHead;

        while(pos != -1){
            comando* m = readcomando(fbcomando, pos);

            if(m->code == key){
                free(m);
                break;
            }
            else pos = m->next;

            free(m);
        }

        free(h);
        return pos;
    }
    

   int existeCurso(FILE* fbcomando, comando* new_m) {
  cabeca* h = readcabeca(fbcomando);
  comando* mAux = NULL;
  int posAux = h->posHead;

  // encontrar a posicao do nó
  while(posAux != -1 && ((mAux = readcomando(fbcomando, posAux)) != NULL && 
             mAux->code != new_m->code)){
            posAux = mAux->next;
            free(mAux);
            mAux = NULL;
  }

  free(h);

  return (posAux != -1); // se a posicao for -1, o registro nao existe
}
