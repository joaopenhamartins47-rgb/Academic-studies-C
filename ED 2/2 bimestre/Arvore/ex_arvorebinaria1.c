#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TADarvore.h>


/*
Faça um algoritmo que retorne por referência ou por return o nível (ou profundidade)
de um dado nó de uma Árvore Binária de Busca
*/

//vou usar a estrategia de percorrer em camadas igual a de fila em lista gen

void nivel_arvore(arvore *raiz, int *nivel, arvore *info)
{
    fila *f, *qt;
    int qtde=0, achou = 0;
    *nivel = 1;
    if(raiz)
    {
        initF(&f);
        enqueue(&f, raiz);
        while(!isEmptyF(f) && !achou)
        {
            qt = f;
            while(qt)
            {
                qtde++;
                qt = qt->prox;
            }
            while(qtde>0 && !achou)
            {
                dequeue(&f, &raiz);
                if(raiz == info)
                    achou=1;
                else
                {
                    if(raiz->dir)
                        enqueue(&f, raiz->dir);
                    if(raiz->esq)
                        enqueue(&f, raiz->esq);
                }
                qtde--;
            }
            if(!achou)
                (*nivel)++;
        }
        if(!achou)
            *nivel = 0;
    }  
}

/*
Faça um algoritmo que retorne o pai de um dado nó de uma Árvore Binária de Busca
*/

//Ideia: Aqui da pra usar o pre-ordem e guardar o anterior na variavel atual

arvore *achar_pai(arvore *raiz, arvore *info)
{
    pilha *p;
    arvore *atual, *pai;
    int achou = 0;

    pai = NULL;

    if (raiz == NULL || info == NULL || raiz == info)
        return NULL;

    init(&p);
    push(&p, raiz);

    while (!isEmpty(p) && !achou)
    {
        pop(&p, &atual);

        if (atual->esq == info || atual->dir == info)
        {
            pai = atual;
            achou = 1;
        }
        else
        {
            if (atual->dir)
                push(&p, atual->dir);

            if (atual->esq)
                push(&p, atual->esq);
        }
    }

    while (!isEmpty(p))
        pop(&p, &atual);

    return pai;
}





int main(void)
{
    return 0;
}