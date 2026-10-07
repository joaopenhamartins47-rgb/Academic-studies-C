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
            *aux = raiz->info;
        else
        {
            localizaNo(raiz->esq, info, &*aux);
            if(!aux)
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


int main(void)
{
    return 0;
}