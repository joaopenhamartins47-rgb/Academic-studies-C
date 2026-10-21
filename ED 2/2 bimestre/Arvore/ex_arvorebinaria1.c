#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TADarvore.h>

#define TF 30
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

//Utilizando pilha

int nivel_prof(arvore *raiz, int info)
{
    pilha *p;
    int nivel = 0; 
    init(&p);
    //A ideia desse algoritmo eh colocar na pilha todos os nos de cima e ir acrescentando o nivel enquanto retira da fila para contar a profundidade
    while(raiz && raiz->info != info)
    {
        push(&p, raiz);
        if(info < raiz->info)
            raiz = raiz->esq;
        else
            raiz = raiz->dir;
    }
    if(raiz)
    {
        while(!isEmpty(p))
        {
            nivel++;
            pop(&p, &raiz);
        }
        return nivel;
    }
    while (!isEmpty(p))
        pop(&p, &raiz);
        
    return -1;
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

//4:-) Faça um algoritmo para tornar uma árvore Vazia (free em todos os nodos da árvore).

//Para retirar todos os nodos eu posso usar o pos-ordem

void esvaziar_arvoreR(arvore **raiz)
{
    if(*raiz)
    {
        esvaziar_arvoreR(&(*raiz)->esq);
        esvaziar_arvoreR(&(*raiz)->dir);
        free(*raiz);
        //Para evitar dangling pointer
        *raiz = NULL;
    }
}

void esvaziar_arvoreI(arvore **raiz)
{
    //Para o algoritmo pos-ordem iterativo, a gente simula o pre-ordem, mas indo para a direita ao inves da esquerda e guardando numa segunda pilha
    arvore *aux = *raiz;
    pilha *p, *p2;
    if(*raiz)
    {
        init(&p); init(&p2);
        push(&p, aux);
        while(!isEmpty(p))
        {
            if(aux) //fundamental para voltar na arvore
            {
                pop(&p, &aux);
                while(aux)
                {
                    push(&p, aux);
                    push(&p2, aux);
                    aux = aux->dir;
                }
            }
            pop(&p, &aux);
            aux = aux->esq;
            if(aux)
                push(&p, aux);
        }
        while(!isEmpty(p2))
        {
            pop(&p2, &aux);
            free(aux);
        }
        *raiz = NULL;
    }
}

/*
6 - Um vetor numérico pode ser utilizado para representar uma árvore ABB. Para isso
você precisa percorrer a árvore utilizando as contas:
Ramificação esquerda: pai*2+1
Ramificação direita: pai*2+2
Faça algoritmos para:
a) inserir na árvore ABB.
b) percorrer a árvore ABB em nível ou profundidade.
c) percorrer a árvore ABB em pré-ordem, in-ordem, pós-ordem de forma recursiva e
também iterativa.
*/

void inicializar_arvore_vet(int vet[])
{
    int i = 0;
    for( ; i<TF; i++)
    {
        vet[i] = 0;
    }
}


void insercao_arvore_vetor(int vet[], int valor)
{
    int i = 0;
    int achou = 0;
    if(vet[i] == 0)
        vet[i] = valor;
    else
    {
        while(i < TF && vet[i] != 0 && !achou)
        {
            if(valor < vet[i])
                i = i*2+1;
            else if(valor > vet[i])
                i = i*2+2;
            else
                achou = 1;
        }
        if(i < TF && !achou)
            vet[i] = valor;
    }
}


/*
Nível 1 — Fixar quando usar fila ou pilha
Exercício 1 — Percorrer em nível
Faça uma função que imprima todos os valores da ABB em nível, utilizando uma fila, sem recursão.
*/

void imprimir_em_nivel(arvore *raiz)
{
    if(!raiz)
        printf("Raiz nula!\n");
    else
    {
        fila *f;
        init(&f);
        enqueue(&f, raiz);
        while(!isEmptyF(f))
        {
            dequeue(&f, &raiz);
            printf("%d ", raiz->info);
            if(raiz->esq)
                enqueue(&f, raiz->esq);
            if(raiz->dir)
                enqueue(&f, raiz->dir);
        }
    }
}




int main(void)
{
    int vet[TF];
    inicializar_arvore_vet(vet);
    return 0;
}