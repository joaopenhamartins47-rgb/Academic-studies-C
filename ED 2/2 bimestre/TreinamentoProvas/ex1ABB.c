#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADarvore.h"


//Funcao pra exibir a arvore em nivel
typedef arvore Tree;


//Funcao contando o nivel

void percorrer_em_nivel(Tree *raiz)
{
    //Posso usar a msm logica da altura ou fazer do jeito que fiz no 1b, vou usar a logica da altura

    fila *f;
    initF(&f);
    int nivel = 1;
    enqueue(&f, raiz);
    enqueue(&f, NULL);

    while(!isEmptyF(f))
    {
        dequeue(&f, &raiz);
        if(raiz)
        {
            if(raiz->esq)
                enqueue(&f, raiz->esq);
            if(raiz->dir)
                enqueue(&f, raiz->dir);
            printf("%d n: %d, ", raiz->info, nivel);
        }
        else
        {
            nivel++;
            if(!isEmptyF(f))
                enqueue(&f, NULL);
        }
    }
}

//Transformar uma arvore em lista encadeada no percurso em nivel so alterando os nos

void Tree_to_listlevel(Tree *inicio)
{
    int primeiro=0;
    fila *f;
    initF(&f);
    Tree *aux = inicio;
    Tree *ant = NULL;
    enqueue(&f, aux);
    while(!isEmptyF(f))
    {
        dequeue(&f, &aux);
        if(aux->esq)
            enqueue(&f, aux->esq);
        if(aux->dir)
            enqueue(&f, aux->dir);

        if(ant)
            ant->dir = aux;

        aux->esq = ant;
        aux->dir = NULL;

        ant = aux;
        
    }
}

//Algoritmo de arvore perfeitamente balanceada nao recursivo








//Arvore AVL em disco, verificar se eh AVL ou nao em todos os nos e fazer a exclusao em disco






/*
5:-) Uma Árvore Binária de Busca (ABB) pode ser implementada em disco (arquivo
binário) ou em um vetor de registros, considerando que cada nó da árvore é um registro de
um arquivo binário ou vetor, conforme desenho a seguir:

 Arquivo da árvore
    esq info dir
0   4   10  1
1   2   12  3
2   0   11  0
3   0   14  0
4   5   8   6
5   0   6   0
6   0   9   0


Faça algoritmos para a ABB em disco e também em vetor de registros:
a) inserir na árvore ABB.

*/

struct regArquivo
{
    int esq, info, dir;
};typedef struct regArquivo regarq;

int tamanho(FILE *Ptrarq)
{
    int tam = 0;
    fseek(Ptrarq, 0, 2);
    tam =  ftell(Ptrarq)/sizeof(regarq);
    return tam;
}

void inserir_ABB_disco(int info)
{
    regarq dados, regdados;
    FILE *Ptrarq = fopen("dados.dat", "rb+");
    int pos = 0;
    int terminar=0, tam, lidos;
    if(!Ptrarq)
        Ptrarq = fopen("dados.dat", "wb+");
    if(!Ptrarq)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        tam = tamanho(Ptrarq);
        regdados.info = info;
        regdados.dir = 0;
        regdados.esq = 0;
        if(tam == 0)
        {
            fseek(Ptrarq, 0, 0);
            fwrite(&regdados, sizeof(regarq), 1, Ptrarq);
        }
        else
        {
            fseek(Ptrarq, 0, 0);
            lidos = fread(&dados, sizeof(regarq), 1, Ptrarq);
            if(lidos != 1)
                terminar = 1;
            while(!feof(Ptrarq) && !terminar)
            {
                if(info < dados.info)
                {
                    if(dados.esq == 0)
                    {
                        //Atualiza o pai e grava o novo no no final do arquivo
                        dados.esq = tam;
                        fseek(Ptrarq, pos*sizeof(regarq), 0);

                        fwrite(&dados, sizeof(regarq), 1, Ptrarq);
                        fseek(Ptrarq, tam*sizeof(regarq), 0);

                        fwrite(&regdados, sizeof(regarq), 1, Ptrarq);
                        terminar = 1;
                    }
                    else
                    {
                        pos = dados.esq;
                        fseek(Ptrarq, pos*sizeof(regarq), 0);
                        fread(&dados, sizeof(regarq), 1, Ptrarq);
                        
                    }

                }
                else if(info > dados.info)
                {
                    if(dados.dir == 0)
                    {
                        //Atualiza o pai e grava o novo no no final do arquivo
                        dados.dir = tam;
                        fseek(Ptrarq, pos*sizeof(regarq), 0);

                        fwrite(&dados, sizeof(regarq), 1, Ptrarq);
                        fseek(Ptrarq, tam*sizeof(regarq), 0);

                        fwrite(&regdados, sizeof(regarq), 1, Ptrarq);
                        terminar = 1;
                    }
                    else
                    {
                        pos = dados.dir;
                        fseek(Ptrarq, pos*sizeof(regarq), 0);
                        fread(&dados, sizeof(regarq), 1, Ptrarq);
                        
                    }
                }
                else
                    terminar = 1;
            }
        }
        fclose(Ptrarq);

    }

}
/*
b) percorrer a árvore ABB em nível ou profundidade.
c) percorrer a árvore ABB em pré-ordem, in-ordem, pós-ordem de forma recursiva e
também iterativa.
d) fazer o algoritmo da exclusão da árvore ABB.
e) fazer o algoritmo de balanceamento da árvore ABB.
f) excluir todos os nodos da árvore ABB.
*/

/*Ideias:


Ate agora vou dividir os conhecimentos em chunks

1 - Percorrer arvore em nivel sabendo o nivel e contando, utiliza o algoritmo que guarda NULL sempre que empilhar 
2 - Transformar arvore em disco, usando fseek e percorrendo
3 - Balanceamento de arvore AVL, exclusao e balanceamento de arvore ABB usando FB e FB_filho se necessario

*/

int main(void)
{
    return 0;
}
