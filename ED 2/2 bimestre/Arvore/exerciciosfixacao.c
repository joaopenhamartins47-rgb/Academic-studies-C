
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADarvore.h"

arvore *criaNo(int info)
{
    arvore *novo = (arvore*)malloc(sizeof(arvore));
    novo->info = info;
    novo->dir = novo->esq = NULL;
    return novo;
}

void insereABB(arvore **raiz, int info)
{
    arvore *aux;
    int achou = 0;
    if(!*raiz)
        *raiz = criaNo(info);
    else
    {
        aux = *raiz;
        while(!achou)
        {
            if(info < aux->info)
                if(!aux->esq)
                {
                    aux->esq = criaNo(info);
                    achou = 1;
                }
                else
                    aux = aux->esq;
            else
                if(!aux->dir)
                {
                    aux->dir = criaNo(info);
                    achou = 1;
                }
                else
                    aux = aux->dir;
        }
    }
}

/*
Enunciado
Implemente a função:
void imprimir_zigzag(arvore *raiz);


Ela deverá imprimir os nós da ABB por nível, alternando o sentido da impressão a cada nível:
- Nível 0: da esquerda para a direita.
- Nível 1: da direita para a esquerda.
- Nível 2: da esquerda para a direita.
- Nível 3: da direita para a esquerda.
- E assim sucessivamente.
*/

//Aqui vou estar utilizando uma pilha pro pre-ordem e gravando em par e impar em ordens diferentes 
//Funcao auxiliar para contar elementos na pilha

int cont_pilha(pilha **p)
{
    int cont = 0;
    pilha *aux;
    arvore *no;

    init(&aux);

    while(!isEmpty(*p))
    {
        pop(p, &no);
        push(&aux, no);
        cont++;
    }

    while(!isEmpty(aux))
    {
        pop(&aux, &no);
        push(p, no);
    }

    return cont;
}

void imprimir_zigzag(arvore *raiz)
{
    pilha *p, *p2, *aux;
    init(&p);
    init(&p2);

    int nivel = 0, qtde = 0;

    if(!raiz)
        printf("Nao ha elementos!");
    else
    {
        push(&p, raiz);

        while(!isEmpty(p))
        {
            qtde = cont_pilha(&p);

            while(qtde > 0)
            {
                pop(&p, &raiz);
                printf("%d ", raiz->info);

                if(nivel % 2 == 0)
                {
                    if(raiz->esq)
                        push(&p2, raiz->esq);

                    if(raiz->dir)
                        push(&p2, raiz->dir);
                }
                else
                {
                    if(raiz->dir)
                        push(&p2, raiz->dir);

                    if(raiz->esq)
                        push(&p2, raiz->esq);
                }

                qtde--;
            }

            printf("\n");
            aux = p;
            p = p2;
            p2 = aux;

            nivel++;
        }
    }
}

/*
Exercício 2 — Encontrar e imprimir o caminho até um elemento na ABB

*/

void imprimir_caminho(arvore *raiz, int valor)
{
    int igual = 0;
    while(raiz && raiz->info != valor && !igual)
    {
        printf("%d -> ", raiz->info);
        if(valor < raiz->info)
            raiz = raiz->esq;
        else if(valor > raiz->info)
            raiz = raiz->dir;
        else
            igual = 1;
    }

    if(!igual && raiz)
        printf("%d\n", raiz->info);
}



int main(void)
{
    arvore *raiz;
    raiz = NULL;
    insereABB(&raiz, 50);
    insereABB(&raiz, 30);
    insereABB(&raiz, 70);
    insereABB(&raiz, 20);
    insereABB(&raiz, 40);
    insereABB(&raiz, 60);
    insereABB(&raiz, 80);
    insereABB(&raiz, 10);
    insereABB(&raiz, 25);
    insereABB(&raiz, 65);
    imprimir_zigzag(raiz);
    imprimir_caminho(raiz, 65);
    return 0;
}