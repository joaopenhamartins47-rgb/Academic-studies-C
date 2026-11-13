#include <stdio.h>
#include <stdlib.h>
#include "TADarvore.h"

typedef arvore Tree;


Tree *criaNo(int info)
{
    Tree *novo = (Tree*)malloc(sizeof(Tree));
    novo->esq = novo->dir = NULL;
    novo->info = info;

    return novo;
}

void rotacao_esq(Tree **P)
{
    //Se rotaciona pra esquerda, olha pra direita

    Tree *Q, *temp;
    Q = (*P)->dir;
    temp = Q->esq;

    //Faz a rotacao
    Q->esq = *P;
    (*P)->dir = temp;
    *P = Q;
}

void rotacao_direita(Tree **P)
{
    //Se rotaciona pra direita, olha pro da esquerda
    Tree *Q, *temp;
    Q = (*P)->esq;
    temp = Q->dir;

    //Faz a rotacao
    Q->dir = *P;
    (*P)->esq = temp;
    *P = Q;
}


//altura = max(esq,dir)+1

int altura(Tree *raiz)
{
    int esq, dir;

    if(raiz)
    {
        esq = altura(raiz->esq);
        dir = altura(raiz->dir);

        if(esq > dir)
            return esq + 1;
        else
            return dir + 1;
    }
    return 0;
}



//Pai negativo, olha o filho da esquerda
//Pai positivo, olha o filho da direita
//Filho positivo, rotaciona a esquerda
//Filho negativo, rotaciona a direita
//Se sao sinais diferentes, rotaciona o filho e depois o pai

void insereAVL(Tree **raiz, int info, char *flag)
{
    //A ideia aqui eh inserir normalmente e depois rotacionar de acordo com as regras de rotacao
    int FB, FB_filho;
    //Recursividade
    if(!*raiz)
    {
        *raiz = criaNo(info);
        *flag = 1;
    }
    else if(info < (*raiz)->info)
        insereAVL(&(*raiz)->esq, info, &*flag);
    else 
        insereAVL(&(*raiz)->dir, info, &*flag);

    //Se ja foi inserido, faz os casos de balanceamento da AVL
    if(*flag == 1)
    {
        FB = altura((*raiz)->dir) - altura((*raiz)->esq);

        if(FB == 2)
        {
            *flag = 0;
            
            FB_filho = altura((*raiz)->dir->dir) - altura((*raiz)->dir->esq);

            if(FB_filho == 1)
                rotacao_esq(&*raiz);

            else //Quer dizer que eh negativo, entao rotaciona os 2
            {
                rotacao_direita(&(*raiz)->dir); //Primeiro rotaciona o filho
                rotacao_esq(&*raiz);
            }
            
        }
        else if(FB == -2)
        {
            *flag = 0;
            
            FB_filho = altura((*raiz)->esq->dir) - altura((*raiz)->esq->esq);

            if(FB_filho == -1)
                rotacao_direita(&*raiz);

            else //Caso pai -2 filho 1
            {
                rotacao_esq(&(*raiz)->esq); //Rotaciona o filho
                rotacao_direita(&*raiz);
            }
        }
    }
}

//Insercao AVL iterativa
void insere_AVL_iterativo(Tree **raiz, int info, char *flag)
{
    int FB, FB_filho;
    pilha *p;
    Tree *aux, *pai;
    *flag = 0;
    aux = *raiz;
    init(&p);
    if(!*raiz)
    {
        *raiz = criaNo(info);
        *flag = 1;
    }
    else
    {
        while(aux && !*flag)
        {
            push(&p, aux);
            if(info < (aux)->info)
            {
                if(!aux->esq)
                {
                    aux->esq = criaNo(info);
                    *flag = 1;
                }
                else
                    aux = aux->esq;
            }
    
            else
            {
                if(!aux->dir)
                {
                    aux->dir = criaNo(info);
                    *flag = 1;
                }
                else
                    aux = aux->dir;
            }
        }
    }
    if(*flag == 1)
    {
        while(!isEmpty(p) && *flag)
        {
            pop(&p, &aux);
            FB = altura(aux->dir) - altura(aux->esq);

            if(FB == 2 || FB == -2)
            {
                if(FB == 2)
                {
                    FB_filho = altura(aux->dir->dir) - altura(aux->dir->esq);

                    if(FB_filho == 1)
                        rotacao_esq(&aux);
                    else
                    {
                        rotacao_direita(&aux->dir);
                        rotacao_esq(&aux);
                    }
                }
                else
                {
                    FB_filho = altura(aux->esq->dir) - altura(aux->esq->esq);

                    if(FB_filho == -1)
                        rotacao_direita(&aux);
                    else //sinais diferentes
                    {
                        rotacao_esq(&aux->esq);
                        rotacao_direita(&aux);
                    }
                }

                if(isEmpty(p))
                    *raiz = aux;
                else
                {
                    pop(&p, &pai);
                    if(info < pai->info)
                        pai->esq = aux;
                    else
                        pai->dir = aux;
                }
                *flag = 0;
            }
        }
    }
    while(!isEmpty(p))
        pop(&p, &aux);
}



//Exercicio AVL: Conta folhas
int conta_folhas_AVL(Tree *raiz)
{
    if(raiz)
    {
        if(!raiz->esq && !raiz->dir)
            return 1;
        return conta_folhas_AVL(raiz->esq) + conta_folhas_AVL(raiz->dir);
    }
    return 0;
}

//Exercicio AVL: Achar maior elemento
int maior_elemento(Tree *raiz)
{
    if (!raiz)
    {
        printf("Arvore vazia!\n");
        return 0;
    }

    while (raiz->dir) 
        raiz = raiz->dir;
    

    return raiz->info;
}



int main(void)
{
    return 0;
}
