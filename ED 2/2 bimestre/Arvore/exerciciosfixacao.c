
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

/*
Transformar uma arvore binaria em uma lista duplamente encadeada, seguindo em nivel
*/



struct arvore_encadeada
{
    struct arvore_encadeada *esq, *dir;
    int info;
};typedef struct arvore_encadeada aren;

//Como ele nao pede valor dos niveis, nao preciso guardar isso, entao eh so percorrer utilizando uma fila normalmente

void Tree_to_list(aren **inicio, arvore *raiz)
{
    arvore *atual, *ant;
    //Percorre em filas
    fila *f;
    initF(&f);
    if(raiz)
        enqueue(&f, raiz);
    *inicio = NULL;
    ant = NULL;
    while(!isEmptyF(f))
    {
        dequeue(&f, &atual);
        
        if(atual->esq)
            enqueue(&f, atual->esq);
        if(atual->dir)
            enqueue(&f, atual->dir);

        //Ligacoes
        atual->esq = ant;
        atual->dir = NULL;

        if(ant)
            ant->dir = atual;
        else
            *inicio = atual;
        ant = atual;
    }
}

int contar_nos(arvore *raiz)
{
    if(raiz)
    {
        return 1 + contar_nos(raiz->esq) + contar_nos(raiz->dir);
    }
    return 0;
}


void busca_exclusao(arvore *raiz, int info, arvore **ex, arvore **pai)
{
    *pai = raiz;
    while(raiz && raiz->info != info)
    {
        *pai = raiz;
        if(info < raiz->info)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }
    if(!raiz)
        pai = NULL;
    *ex = raiz;
}

void excluir_no_arvore(arvore **raiz, arvore *pai, arvore *e, char lado, int info)
{
    arvore *paisub, *sub, *filho;
    int aux;
    pai = NULL;
    e = NULL;
    busca_exclusao(*raiz, info, &e, &pai);
    if(!e)
        printf("Erro ao achar elemento!");
    else
    {
        //Primeiro caso de remocao, se o elemento for folha
        if(!e->esq && !e->dir)
        {
            //4 casos a considerar, se for raiz ou nao e se for remover da esquerda ou da direita
            if(e != pai)// 1
            {
                if(e->info < pai->info) //2
                    pai->esq = NULL; //Corta a conexao
                else //3
                    pai->dir = NULL;
            }
            else //4
                *raiz = NULL;
            free(e);
        }
        else
        {
            if(!e->esq || !e->dir) //2 caso de remocao, 1 filho
            {
                if(e != pai)
                {
                    if(!e->esq)
                    {
                        if(e->info < pai->info)
                            pai->esq = e->dir;
                        
                        else
                            pai->dir = e->dir;
                    }
                    else
                    {
                        if(e->info < pai->info)
                            pai->esq = e->esq;
                        
                        else
                            pai->dir = e->esq;
                    }
                }
                else
                {
                    if(!e->esq)
                        *raiz = e->dir;
                    else
                        *raiz = e->esq;
                }
                free(e);
                
            }
            else // 3 caso de remocao, 2 filhos
            {
                if(lado == 'd') // Acha o menor do lado direito
                {
                    paisub = e;
                    sub = e->dir;

                    while(sub->esq != NULL)
                    {
                        paisub = sub;
                        sub = sub->esq;
                    }
                }
                else // Acha o maior do lado esquerdo
                {
                    paisub = e;
                    sub = e->esq;

                    while(sub->dir != NULL)
                    {
                        paisub = sub;
                        sub = sub->dir;
                    }
                }

                aux = sub->info;

                // Chamada recursiva para excluir o sucessor ou predecessor
                excluir_no_arvore(raiz, paisub, sub, lado, aux);

                // Substitui o valor do elemento original
                e->info = aux;
            }
        }
    }
}


void perfeitamente_balanceada(arvore **raiz)
{
    arvore *atual, *e, *pai;
    int FB, qtdeE, qtdeD, aux;
    fila *f;
    initF(&f);
    if(*raiz)
        enqueue(&f, *raiz);
    while(!isEmptyF(f))
    {
        dequeue(&f, &atual);
        do
        {
            FB = qtdeD = qtdeE = 0;
            qtdeD = contar_nos(atual->dir);
            qtdeE = contar_nos(atual->esq);
            FB = qtdeD - qtdeE;
            if(FB < -1 || FB > 1)
            {
                //Guarda a info do no para exclusao
                aux = atual->info;

                //Anda com o atual
                if(!atual->esq)
                    atual = atual->dir;
                else if(!atual->dir)
                    atual = atual->esq;

                //Busca e faz a exclusao
                busca_exclusao(*raiz, aux, &e, &pai);

                if(FB < 0)
                    excluir_no_arvore(&*raiz, pai, e, 'e', aux);
                else
                    excluir_no_arvore(&*raiz, pai, e, 'd', aux);
            }
            
        } while (FB < -1 || FB > 1);

        if(atual->esq)
            enqueue(&f, atual->esq);
        if(atual->dir)
            enqueue(&f, atual->dir);
    }
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