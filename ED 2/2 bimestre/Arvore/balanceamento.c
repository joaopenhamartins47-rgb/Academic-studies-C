#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADarvore.h"

void contar_nos(arvore *raiz, int *quantidade)
{
    if (raiz != NULL)
    {
        (*quantidade)++;
        contar_nos(raiz->esq, quantidade);
        contar_nos(raiz->dir, quantidade);
    }
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

void balanceamento(arvore **raiz)
{
    arvore *no, *e, *pai;
    int aux, qtdeE, qtdeD, FB;
    fila *f;
    initF(&f);
    enqueue(&f, *raiz);
    while(!isEmptyF(f))
    {
        dequeue(&f, &no);
        do
        {
            qtdeD = qtdeE = 0; //Inicializa as qtde
            contar_nos(no->dir, &qtdeD);
            contar_nos(no->esq, &qtdeE);
            FB = qtdeD - qtdeE;
            if(FB < -1 || FB > 1)
            {
                aux = no->info;
                if(!no->esq)
                    no = no->dir;
                else if(!no->dir)
                    no = no->esq;
                busca_exclusao(*raiz, aux, &e, &pai);
                if(FB < 0) //Quer dizer que ele ta na esquerda, o desbalanceamento
                   excluir_no_arvore(&*raiz, pai, e, 'e', aux); 
                
                else
                    excluir_no_arvore(&*raiz, pai, e, 'd', aux);
                insereABB(&*raiz, aux);
            }

        } while (FB<-1 || FB > 1);
        


        if(no->esq)
            enqueue(&f, no->esq);
        if(no->dir)
            enqueue(&f, no->dir);
    }
}

int main(void)
{
    return 0;
}