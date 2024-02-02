#include "cabecalho.h"
#include "matricula.h"
#include "disciplina.h"
#include "professor.h"

    void writematricula(FILE* fb, matricula* c, int pos){
        fseek(fb, sizeof(cabeca) + sizeof(matricula)*pos, SEEK_SET);
        fwrite(c, 1, sizeof(matricula), fb);
    }

    matricula* readmatricula(FILE* fb, int pos){
        matricula* c = (matricula*)malloc(sizeof(matricula));

        fseek(fb, sizeof(cabeca) + sizeof(matricula)*pos, SEEK_SET);
        fread(c, 1, sizeof(matricula), fb);

        return c;
    }

    int insertmatricula_bin(FILE* fb, matricula* c, int next_pos){
        cabeca* h = readcabeca(fb);
        int insert_pos;

        c->next = next_pos;

        if(h->posLoose == -1){
            insert_pos = h->posTop;
            writematricula(fb, c, h->posTop);
            h->posTop++;
        }
        else{
            insert_pos = h->posLoose;
            matricula* cLoose = readmatricula(fb, h->posLoose);
            writematricula(fb, c, h->posLoose);    
            h->posLoose = cLoose->next;
            free(cLoose);
        }

        if(h->posHead == next_pos) h->posHead = insert_pos;
        writecabeca(fb, h);
        free(h);

        return insert_pos;
    }

    void cadastrarmatricula(FILE* fbmatricula,FILE* fbprofessor,FILE* fbdisciplina, FILE* fbcomando){
        matricula* m = (matricula*)malloc(sizeof(matricula));
        cabeca* h = readcabeca(fbcomando);
        printf("\n*Cadastrar distribuicao*\n\n");

        printcurso(fbdisciplina,fbcomando);
        printf("-> Digite o codigo da distribuicao: ");
        scanf("%d%*c", &m->codDisciplina);

        printf("-> Digite o ano: ");
        scanf("%d%*c", &m->anoLetivo);
        
        printprofe(fbprofessor,fbcomando);
        printf("-> Digite o id do professor:");
        scanf("%d%*c", &m->codProfessor);
        
       if(!existeMatricula(fbcomando,m)){
                 insertmatricula_inOrder(fbcomando,m,h->posHead);
        }

        free(m);
    }

        void lerarquivotextomatricula(FILE* fbmatricula, FILE* fbcomando){
        matricula* c = (matricula*)malloc(sizeof(matricula));
        cabeca* h = readcabeca(fbcomando);
        
        fscanf(fbmatricula,"%d;", &c->codDisciplina); 
      
        fscanf(fbmatricula,"%d;", &c->anoLetivo);
       
        fscanf(fbmatricula,"%d\n", &c->codProfessor);
        if(!existeMatricula(fbcomando,c)){
                 insertmatricula_inOrder(fbcomando,c,h->posHead);
        }

        free(c);
    }


    void inserirNaCabecamatricula(FILE* fbcomando, matricula* m){
        cabeca* h = readcabeca(fbcomando);

        m->next = h->posHead;

        if(h->posLoose == -1){
            writematricula(fbcomando, m, h->posTop);

            h->posHead = h->posTop;
            h->posTop++;
        }
        else{
            matricula* mLoose = readmatricula(fbcomando, h->posLoose);

            writematricula(fbcomando, m, h->posLoose);

            h->posHead = h->posLoose;
            h->posLoose = mLoose->next;            

            free(mLoose);
        }

        writecabeca(fbcomando, h);

        free(h);
    }



    void printmatricula(FILE* fbmatricula, FILE* fbcomando){
        printf("\nLISTA DE DISTRIBUICAO\n\n");

        cabeca* h = readcabeca(fbmatricula);

        if(h->posHead != -1){
            printf("%-10s%-10s%-10s\n", "COD", "ANO","ID PROFESSOR");
            printNodematricula(fbmatricula, h->posHead);
        }
        else printf("\nNAO TEM DISTRIBUICAO\n\n");

        free(h);
    }

    void printNodematricula(FILE* fbmatricula, int pos){
        if(pos != -1){
            matricula* c = readmatricula(fbmatricula, pos);
            int posNext = c->next;

            printf("%-10d%-10d%-10d\n", c->codDisciplina, c->anoLetivo,c->codProfessor);

            free(c);
            
            printNodematricula(fbmatricula, posNext);
        }
    }

    void removerMatricula(FILE* fbMatricula, FILE* fbCourse, FILE* fbcomando){
        int codDisciplina, anoLetivo;
        printf("\nREMOVER DISTRIBUICAO\n\n");

        printmatricula(fbMatricula, fbcomando);
        printf("\n-> DIGITE O CODIGO DE DISCIPLINA QUE DESEJA REMOVER: ");
        scanf("%d%*c", &codDisciplina);

        //printMatriculaPorDisciplina(fbMatricula, codDisciplina);
        printf("\n-> DIGITE O ANO LETIVO QUE DESEJA REMOVER: ");
        scanf("%d%*c", &anoLetivo);

        removerMatricula_bin(fbMatricula, codDisciplina, anoLetivo);
    }

    void removerMatricula_bin(FILE* fbMatricula, int codDisciplina, int anoLetivo){
        cabeca* h = readcabeca(fbMatricula);
        matricula* mAux = NULL;
        int posAux = h->posHead;
        int posAnt = h->posHead;

        //encontrar a posicao do nó
        while(posAux != -1 && ((mAux = readmatricula(fbMatricula, posAux)) != NULL && 
             (mAux->codDisciplina!=codDisciplina ||
             (mAux->codDisciplina ==  codDisciplina && mAux->anoLetivo != anoLetivo)))){
            
            posAnt = posAux;
            posAux = mAux->next;
            free(mAux);
            mAux = NULL;
        }

        if(posAux != -1){//nó encontrado
            if(posAux == posAnt) h->posHead = mAux->next;
            else{//remoção do meio
                matricula* mAnt = readmatricula(fbMatricula, posAnt);
                mAnt->next = mAux->next;
                writematricula(fbMatricula, mAnt, posAnt);
                free(mAnt);
            }
            mAux->next = h->posLoose;
            h->posLoose = posAux;
            writematricula(fbMatricula, mAux, posAux);
            writecabeca(fbMatricula, h);
            free(mAux);
        }

        free(h);
    }

    int insertmatricula_inOrder(FILE* fbcomando, matricula* new_m, int pos){
        if(pos == -1){
            int insert_pos = insertmatricula_bin(fbcomando, new_m, pos);
            return insert_pos;
        }
        else{
            matricula* m = readmatricula(fbcomando, pos);

            if(m->codDisciplina > new_m->codDisciplina){
                int insert_pos = insertmatricula_bin(fbcomando, new_m, pos);
                free(m);
                return insert_pos;
            }
            else{
                m->next = insertmatricula_inOrder(fbcomando, new_m, m->next);
                writematricula(fbcomando, m, pos);
                free(m);
                return pos;
            }
        }
    }


    int existeMatricula(FILE* fbcomando, matricula* new_m) {
  cabeca* h = readcabeca(fbcomando);
  matricula* mAux = NULL;
  int posAux = h->posHead;

  // encontrar a posicao do nó
  while(posAux != -1 && ((mAux = readmatricula(fbcomando, posAux)) != NULL && 
             (mAux->codDisciplina != new_m->codDisciplina ||
             (mAux->codDisciplina == new_m->codDisciplina && mAux->anoLetivo != new_m->anoLetivo)))){
            posAux = mAux->next;
            free(mAux);
            mAux = NULL;
  }

  free(h);

  return (posAux != -1); // se a posicao for -1, o registro nao existe
}