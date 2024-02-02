#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "curso.h"
#include "cabecalho.h"
#include "disciplina.h"
#include "professor.h"
#include "matricula.h"

FILE *initializeBinaryFile(char *arqName)
{
    FILE *fb = fopen(arqName, "r+b");

    if(fb == NULL){
        fb = fopen(arqName,"w+b");
        initializecabeca(fb);
    }

    return fb;
}

int main()
{
    int imprime;
    int escolha;
    int n = 0;
    char categoria;
    int cadastro;
    char txt[100];
    char nome_arquivo[100];
    FILE *fbcomando = initializeBinaryFile("comando.bin");
    FILE *fbCourse = initializeBinaryFile("Courses.bin");
    FILE *fbprofessor = initializeBinaryFile("Professor.bin");
    FILE *fbmatricula = initializeBinaryFile("matricula.bin");



  // Abre o arquivo
 FILE *curso = fopen(nome_arquivo, "r");


    while (escolha != 0)
    {

        printf("\n1-cadastrar\n2-ler arquivo texto\n 3-printar\n 4-remover distribuicao\n 0-sair\n");

        scanf("%d%*c", &escolha);

        switch (escolha)
        {

        case 1:
            printf("1-castrar curso\n2-cadastrar disciplina\n3-cadastrar professor\n4-cadastrar distribuicao\n");
            scanf("%d%*c", &cadastro);
            printf("quantos cadastros?\n");
            scanf("%d%*c", &n);
            if(cadastro == 1){
            for (int i = 0; i < n; i++)
            {
                cadastrarCurso(fbcomando);
            }
            }
            if(cadastro == 2){
                   for (int i = 0; i < n; i++)
            {
                cadastrarDisciplina(curso, fbCourse);
            }
            }
            if(cadastro == 3){
                   for (int i = 0; i < n; i++)
            {
                cadastrarprofessor(curso, fbprofessor);
            }
            }
            if(cadastro == 4){
                 for (int i = 0; i < n; i++)
            {
                cadastrarmatricula(curso,fbprofessor,fbCourse,fbmatricula);
            }
            }
            

            break;

        case 2:

        printf("Digite o nome do arquivo: ");
        scanf("%s", nome_arquivo);

        // Abre o arquivo
        FILE *curso = fopen(nome_arquivo, "r");


        while(fscanf(curso, "%c;", &categoria) != EOF){
             if(categoria == 'C'){
                
               lerArquivoTextoCurso(curso, fbcomando);
               
            }
            if(categoria == 'D'){
            
              lerarquivotextodiciplina(curso, fbCourse);
            }

            if(categoria == 'P'){
                lerarquivotextoprofessor(curso,fbprofessor);
            }
            if(categoria == 'M'){
                lerarquivotextomatricula(curso,fbmatricula);
            }
        }
            break;

        case 3:
            printf("1-imprimir curso\n2-imprimir disciplina\n3-imprimir professor\n4-imprimir distribuicao\n5-imprimir tudo\n");
            scanf("%d",&imprime);
            if(imprime == 1){
            printcomando(fbcomando);
            }
            if(imprime == 2){
            printCourse(fbCourse,fbcomando);
            }
            if(imprime == 3){
            printprofessor(fbprofessor,fbcomando);
            }
            if(imprime == 4){
            printmatricula(fbmatricula,fbcomando);
            }
            if(imprime == 5){
            printcomando(fbcomando);
            printCourse(fbCourse,fbcomando);
            printprofessor(fbprofessor,fbcomando);
            printmatricula(fbmatricula,fbcomando);
            }
            break;

        case 4:

            removerMatricula(fbmatricula, fbCourse, fbcomando);

            break;
    
        }
    
        }
    
    // for(int i = 0; i < 6; i++) cadastrarDisciplina(fbCourse, fbcomando);

    // printCourse(fbCourse, fbcomando);

    // comando* m = readcomando(fbcomando, searchcomando(fbcomando, 1));

    // printf("nome = %s\n", m->data_comando.name);

    return 0;
    }