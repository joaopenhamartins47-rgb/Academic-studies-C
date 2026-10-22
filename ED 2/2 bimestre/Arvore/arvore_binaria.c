#include <stdio.h>
#include <stdlib.h>
#include <TADarvore.h>



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


//Agora de forma iterativa, temos 2 jeitos padroes de codigo, seguindo a logica do pre-ordem, em-ordem e pos-ordem
void pre_ordemI(arvore *raiz) //Nesse codigo tem 2 partes, uma que avanca todas da esquerda e outra que coloca na pilha o elemento da direita, pra depois ser percorrido
{
    pilha *p;
    init(&p);
    push(&p, raiz);
    while(!isEmpty(p))
    {
        if(raiz)
        {
            pop(&p, &raiz);
            while(raiz)
            {
                printf("%d", raiz->info);
                push(&p, raiz);
                raiz = raiz->esq;
            }
        }
        pop(&p, &raiz);
        raiz = raiz->dir;
        if(raiz)
            push(&p, raiz);
    }
}

//Outro jeito guardando na pilha sempre o elemento da direita
void pre_ordem_pilha(arvore *raiz)
{
    pilha *p;
    init(&p);
    push(&p, raiz);
    while(!isEmpty(p))
    {
        pop(&p, &raiz);
        printf("%d", raiz->info);
        if(raiz->dir)
            push(&p, raiz->dir);
        if(raiz->esq)
            push(&p, raiz->esq);
    }
}

void em_ordemI(arvore *raiz) 
{
    pilha *p;
    init(&p);
    push(&p, raiz);
    while(!isEmpty(p))
    {
        if(raiz)
        {
            pop(&p, &raiz);
            while(raiz)
            {
                push(&p, raiz);
                raiz = raiz->esq;
            }
        }
        pop(&p, &raiz);
        printf("%d", raiz->info);
        raiz = raiz->dir;
        if(raiz)
            push(&p, raiz);
    }
}

//No pos-ordem Iterativo, muito usado em casos de exclusao por exemplo, a ideia eh vc ter duas pilhas, uma para percorrer a estrura da arvore msm e outra pra guadar os dados a fim de exibir depois invertido (ja que eh uma pilha). Diferente do pre-ordem, aqui vc percorre pela direita e depois guarda o da esquerda se tiver
void pos_ordemI(arvore *raiz) 
{
    pilha *p, *p2;
    init(&p);
    init(&p2);
    push(&p, raiz);
    while(!isEmpty(p))
    {
        if(raiz)
        {
            pop(&p, &raiz);
            while(raiz)
            {
                push(&p2, raiz);
                push(&p, raiz);
                raiz = raiz->dir;
            }
        }
        pop(&p, &raiz);
        raiz = raiz->esq;
        if(raiz)
            push(&p, raiz);
    }
    while(!isEmpty(p2))
    {
        pop(&p2, &raiz);
        printf("%d", raiz->info);
    }
}


//Exercicio de arvore binaria ABB

/*
Exercício 1 — Implementar a inserção de uma ABB
Crie uma função com esta assinatura:
void insereABB(arvore **raiz, int info);


Requisitos:
1. A árvore começa vazia.
2. O primeiro valor inserido se torna a raiz.
3. Cada valor seguinte percorre a árvore comparando valores até encontrar uma posição livre.
4. Valores duplicados não devem ser inseridos.
5. Você não pode informar manualmente o pai nem a direção de inserção.
*/


void insereABB(arvore **raiz, int info)
{
    arvore *aux = *raiz, *pai = NULL;
    int igual = 0;
    arvore *novo = (arvore*)malloc(sizeof(arvore));
    novo->info = info;
    novo->esq = novo->dir = NULL;
    if(!*raiz)
        *raiz = novo;
    else
    {
        //Procura pelo pai para inserir
        while(aux && !igual)
        {
            if(aux->info > info)
            {
                pai = aux;
                aux = aux->esq;
            }
            else if(aux->info < info)
            {
                pai = aux;
                aux = aux->dir;
            }
            else
                igual = 1;
        }
        if(igual)
        {
            printf("Elemento ja existente!\n");
            free(novo);
        }
        else
        {
            if(pai)
            {
                if(pai->info > info && pai->esq == NULL)
                    pai->esq = novo;
                else if(pai->info < info && pai->dir == NULL)
                    pai->dir = novo;
            }
        }
    }
}


//Insercao em arvore ABB

//Para a insercao em arvore ABB podemos ter varios algoritmos, como por exemplo o aux para percorrer e a gravacao no ant que representa o pai, ou simplesmente ir andando verificando ate que uma flag seja diferente de 0. O que vou estar usando eh a segunda forma


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

//Agora para inserir de forma recursiva, utiliza-se a mesma ideia da forma iterativa, porem com a recursividade presente

void insereABBR(arvore **raiz, int info)
{
    if(!*raiz)
        *raiz = criaNo(info);
    else
    {
        if(info < (*raiz)->info)
            insereABBR(&(*raiz)->esq, info);
        else
            insereABBR(&(*raiz)->dir, info);
    }
}


//Anotacoes Aula busca e exclusao em arvore ABB

//Para a busca em arvore ABB podemos fazer do jeito recursivo ou iterativo

//---Jeito iterativo---

arvore *buscaABBI(arvore *raiz, int info)
{
    while(raiz && raiz->info != info)
    {
        if(info < raiz->info)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }
    return raiz;
}

//--Jeito recursivo--

arvore *buscaABBR(arvore *raiz, int info)
{
    if(!raiz || raiz->info == info)
        return raiz;
    if(info < raiz->esq)
        return buscaABBR(raiz->esq, info);
    return buscaABBR(raiz->dir, info);
}

//Busca que retorna o elemento a ser excluido e o pai
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

/*Para a exclusao de um determinado no em uma arvore ABB devemos tratar 3 casos
1 - Quando o elemento for folha
2 - Quando o elemento tem 1 filho
3 - Quando o elemento tem 2 filhos

Casos a considerar:

Exclusao da raiz:
e diferente do pai
e igual ao pai

Exclusao do lado esquerdo 
Exclusao do lado direito
*/

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






int main(void)
{
    return 0;
}