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



int main(void)
{
    return 0;
}