#include <stdio.h>
#include <stdlib.h>


struct Arvore
{
    int info;
    struct Arvore *esq, *dir;
};typedef struct Arvore arvore;

arvore* criaNo(int info)
{
    arvore *novo = (arvore*)malloc(sizeof(arvore));
    novo->info = info;
    novo->dir = novo->esq = NULL;
    return novo;
}

void localizaNo(arvore *raiz, int info, arvore **aux)
{
    if(raiz)
    {
        if(raiz->info == info)
            *aux = raiz;
        else
        {
            localizaNo(raiz->esq, info, &*aux);
            if(!*aux)
                localizaNo(raiz->dir, info, &*aux);
        }
    }
}

void insere(arvore **raiz, int info, int info_pai, arvore *pai, char direcao)
{
    arvore *aux = NULL;
    if(*raiz == NULL)
        *raiz = criaNo(info);
    else
    {
        localizaNo(*raiz, info_pai, &aux);
        if(aux)
        {
            if(direcao == 'e' && aux->esq == NULL)
                aux->esq = criaNo(info);
            else if(direcao == 'd' && aux->dir == NULL)
                aux->dir = criaNo(info);
        }
    }
}

//Como percorrer arvores binarias?

//Basicamente ha 3 jeitos de se percorrer arvores binarias, o jeito pre-ordem, em-ordem e pos-ordem

//Os 3 jeitos de forma recursiva
void pre_ordem(arvore *raiz) //Imprime de cima ate embaixo, indo primeiro pela esquerda e depois um passo a direita
{
    if(raiz)
    {
        printf("%d", raiz->info);
        pre_ordem(raiz->esq);
        pre_ordem(raiz->dir);
    }
}

void em_ordem(arvore *raiz) //Imprime os elementos em ordem seguindo os padros ABB de arvore binaria
{
    if(raiz)
    {
        em_ordem(raiz->esq);
        printf("%d", raiz->info);
        em_ordem(raiz->dir);
    }
}

void pos_ordem(arvore *raiz) //Imprime os elementos de baixo pra cima, bom para exclusoes
{
    if(raiz)
    {
        pos_ordem(raiz->esq);
        pos_ordem(raiz->dir);
        printf("%d", raiz->info);
    }
}



int main(void)
{
    return 0;
}