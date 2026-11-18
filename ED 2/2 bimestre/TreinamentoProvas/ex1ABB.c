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

//Transformar uma arvore em lista encadeada no percurso em nivel so alterando os nos

void Tree_to_listlevel(Tree *inicio)
{
    int primeiro=0;
    fila *f;
    initF(&f);
    Tree *aux = inicio;
    Tree *ant = NULL;
    enqueue(&f, aux);
    while(!isEmptyF(f))
    {
        dequeue(&f, &aux);
        if(aux->esq)
            enqueue(&f, aux->esq);
        if(aux->dir)
            enqueue(&f, aux->dir);

        if(ant)
            ant->dir = aux;

        aux->esq = ant;
        aux->dir = NULL;

        ant = aux;
        
    }
}

//Algoritmo de arvore perfeitamente balanceada nao recursivo








//Arvore AVL em disco, verificar se eh AVL ou nao em todos os nos e fazer a exclusao em disco






/*
5:-) Uma Árvore Binária de Busca (ABB) pode ser implementada em disco (arquivo
binário) ou em um vetor de registros, considerando que cada nó da árvore é um registro de
um arquivo binário ou vetor, conforme desenho a seguir:

 Arquivo da árvore
    esq info dir
0   4   10  1
1   2   12  3
2   0   11  0
3   0   14  0
4   5   8   6
5   0   6   0
6   0   9   0


Faça algoritmos para a ABB em disco e também em vetor de registros:
a) inserir na árvore ABB.

*/

struct regArquivo
{
    int esq, info, dir;
};typedef struct regArquivo regarq;

int tamanho(FILE *Ptrarq)
{
    int tam = 0;
    fseek(Ptrarq, 0, 2);
    tam =  ftell(Ptrarq)/sizeof(regarq);
    return tam;
}

void inserir_ABB_disco(int info)
{
    regarq dados, regdados;
    FILE *Ptrarq = fopen("dados.dat", "rb+");
    int pos = 0;
    int terminar=0, tam, lidos;
    if(!Ptrarq)
        Ptrarq = fopen("dados.dat", "wb+");
    if(!Ptrarq)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        tam = tamanho(Ptrarq);
        regdados.info = info;
        regdados.dir = 0;
        regdados.esq = 0;
        if(tam == 0)
        {
            fseek(Ptrarq, 0, 0);
            fwrite(&regdados, sizeof(regarq), 1, Ptrarq);
        }
        else
        {
            fseek(Ptrarq, 0, 0);
            lidos = fread(&dados, sizeof(regarq), 1, Ptrarq);
            if(lidos != 1)
                terminar = 1;
            while(!feof(Ptrarq) && !terminar)
            {
                if(info < dados.info)
                {
                    if(dados.esq == 0)
                    {
                        //Atualiza o pai e grava o novo no no final do arquivo
                        dados.esq = tam;
                        fseek(Ptrarq, pos*sizeof(regarq), 0);

                        fwrite(&dados, sizeof(regarq), 1, Ptrarq);
                        fseek(Ptrarq, tam*sizeof(regarq), 0);

                        fwrite(&regdados, sizeof(regarq), 1, Ptrarq);
                        terminar = 1;
                    }
                    else
                    {
                        pos = dados.esq;
                        fseek(Ptrarq, pos*sizeof(regarq), 0);
                        fread(&dados, sizeof(regarq), 1, Ptrarq);
                        
                    }

                }
                else if(info > dados.info)
                {
                    if(dados.dir == 0)
                    {
                        //Atualiza o pai e grava o novo no no final do arquivo
                        dados.dir = tam;
                        fseek(Ptrarq, pos*sizeof(regarq), 0);

                        fwrite(&dados, sizeof(regarq), 1, Ptrarq);
                        fseek(Ptrarq, tam*sizeof(regarq), 0);

                        fwrite(&regdados, sizeof(regarq), 1, Ptrarq);
                        terminar = 1;
                    }
                    else
                    {
                        pos = dados.dir;
                        fseek(Ptrarq, pos*sizeof(regarq), 0);
                        fread(&dados, sizeof(regarq), 1, Ptrarq);
                        
                    }
                }
                else
                    terminar = 1;
            }
        }
        fclose(Ptrarq);

    }

}
/*
b) percorrer a árvore ABB em nível ou profundidade.
*/
//TAD temporario de fila dinamica de inteiros para a ABB em disco
struct FilaDisco
{
    int info;
    struct FilaDisco *prox;
};typedef struct FilaDisco filaDisco;

void initFD(filaDisco **f)
{
    *f = NULL;
}

void enqueueD(filaDisco **f, int info)
{
    filaDisco *novo, *aux;

    novo = malloc(sizeof(filaDisco));
    if(novo)
    {
        novo->info = info;
        novo->prox = NULL;

        if(*f == NULL)
            *f = novo;
        else
        {
            aux = *f;
            while(aux->prox)
                aux = aux->prox;
            aux->prox = novo;
        }
    }
}

void dequeueD(filaDisco **f, int *info)
{
    filaDisco *aux;

    if(*f)
    {
        aux = *f;
        *info = aux->info;
        *f = aux->prox;
        free(aux);
    }
}

int isEmptyFD(filaDisco *f)
{
    return f == NULL;
}

void percorrer_ABB_disco()
{
    FILE *Ptrarq = fopen("dados.dat", "rb");
    filaDisco *f;
    int pos;
    initFD(&f);
    if(!Ptrarq)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        regarq dados;
        int tam = tamanho(Ptrarq);
        fseek(Ptrarq, 0, 0);
        if(tam != 0)
        {
            fread(&dados, sizeof(regarq), 1, Ptrarq);
            if(dados.esq != 0)
                enqueueD(&f, dados.esq);
            if(dados.dir != 0)
                enqueueD(&f, dados.dir);
            printf("%d ", dados.info);
            while(!isEmptyFD(f))
            {
                dequeueD(&f, &pos);
                fseek(Ptrarq, pos*sizeof(regarq), 0);
                fread(&dados, sizeof(regarq), 1, Ptrarq);
                printf("%d ", dados.info);

                if(dados.esq != 0)
                    enqueueD(&f, dados.esq);
                
                if(dados.dir != 0)
                    enqueueD(&f, dados.dir);
                
            }
        }
        fclose(Ptrarq);
    }
}
/*

c) percorrer a árvore ABB em pré-ordem, in-ordem, pós-ordem de forma recursiva e
também iterativa.

*/
//TAD temporario de pilha dinamica de inteiros para a ABB em disco
struct PilhaDisco
{
    int info;
    struct PilhaDisco *prox;
};typedef struct PilhaDisco pilhaDisco;

void initPD(pilhaDisco **p)
{
    *p = NULL;
}

void pushD(pilhaDisco **topo, int info)
{
    pilhaDisco *novo = malloc(sizeof(pilhaDisco));

    if(novo)
    {
        novo->info = info;
        novo->prox = *topo;
        *topo = novo;
    }
}

void popD(pilhaDisco **topo, int *info)
{
    pilhaDisco *aux;

    if(*topo)
    {
        aux = *topo;
        *info = aux->info;
        *topo = aux->prox;
        free(aux);
    }
}

int isEmptyPD(pilhaDisco *topo)
{
    return topo == NULL;
}

void ABB_preordem_disco()
{
    //O pre ordem faz uma busca andando todos a esquerda e depois verifica se tem um na direita quando a esquerda eh vazia, ou usa-se uma pilha que guarda sempre o da direita e depois o da esquerda, vou fazer do segundo jeito
    pilhaDisco *p;
    int tam, pos;
    initPD(&p);
    FILE *Ptrarq = fopen("dados.dat", "rb");
    regarq dados;
    if(!Ptrarq)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        tam = tamanho(Ptrarq);
        fseek(Ptrarq, 0, 0);
        if(tam == 0)
            printf("Arquivo vazio!\n");
        else
        {
            fread(&dados, sizeof(regarq), 1, Ptrarq);
            if(dados.dir != 0)
                pushD(&p, dados.dir);
            if(dados.esq != 0)
                pushD(&p, dados.esq);
                
            printf("%d ", dados.info);
            while(!isEmptyPD(p))
            {
                popD(&p, &pos);

                fseek(Ptrarq, pos*sizeof(regarq), 0);
                fread(&dados, sizeof(regarq), 1, Ptrarq);

                printf("%d ", dados.info);

                if(dados.dir != 0)
                    pushD(&p, dados.dir);
                if(dados.esq != 0)
                    pushD(&p, dados.esq);
            }
        }
        fclose(Ptrarq);
        
    }
}

void ABB_emordem_disco()
{
    //Percorre a esquerda, visita o no e depois percorre a direita
    pilhaDisco *p;
    int tam, pos;
    initPD(&p);
    FILE *Ptrarq = fopen("dados.dat", "rb");
    regarq dados;
    if(!Ptrarq)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        tam = tamanho(Ptrarq);
        fseek(Ptrarq, 0, 0);
        if(tam == 0)
            printf("Arquivo vazio!\n");
        else
        {
            pos = 0;
            while(pos != -1 || !isEmptyPD(p))
            {
                //Guarda a posicao do no atual e desce para a esquerda
                while(pos != -1)
                {
                    pushD(&p, pos);
                    fseek(Ptrarq, pos*sizeof(regarq), 0);
                    fread(&dados, sizeof(regarq), 1, Ptrarq);

                    if(dados.esq != 0)
                        pos = dados.esq;
                    else
                        pos = -1;
                }

                //Volta ao no que estava esperando na pilha
                popD(&p, &pos);
                fseek(Ptrarq, pos*sizeof(regarq), 0);
                fread(&dados, sizeof(regarq), 1, Ptrarq);

                printf("%d ", dados.info);

                if(dados.dir != 0)
                    pos = dados.dir;
                else
                    pos = -1;
            }
        }
        fclose(Ptrarq);

    }
}

//O pos ordem segue a mesma logica do em ordem, a diferenca eh que precisa colocar invertido numa segunda pilha, percorrendo dessa vez da direita pra esquerda

void ABB_posordem_disco()
{
    //Percorre a esquerda, visita o no e depois percorre a direita
    pilhaDisco *p, *p2;
    int tam, pos;
    initPD(&p);
    initPD(&p2);
    FILE *Ptrarq = fopen("dados.dat", "rb");
    regarq dados;
    if(!Ptrarq)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        tam = tamanho(Ptrarq);
        fseek(Ptrarq, 0, 0);
        if(tam == 0)
            printf("Arquivo vazio!\n");
        else
        {
            pos = 0;
            while(pos != -1 || !isEmptyPD(p))
            {
                //Guarda a posicao do no atual e desce para a esquerda
                while(pos != -1)
                {
                    pushD(&p, pos);
                    pushD(&p2, pos);
                    fseek(Ptrarq, pos*sizeof(regarq), 0);
                    fread(&dados, sizeof(regarq), 1, Ptrarq);

                    if(dados.dir != 0)
                        pos = dados.dir;
                    else
                        pos = -1;
                }

                //Volta ao no que estava esperando na pilha
                popD(&p, &pos);
                fseek(Ptrarq, pos*sizeof(regarq), 0);
                fread(&dados, sizeof(regarq), 1, Ptrarq);


                if(dados.esq != 0)
                    pos = dados.esq;
                else
                    pos = -1;
            }
            while(!isEmptyPD(p2))
            {
                popD(&p, &pos);
                fseek(Ptrarq, pos*sizeof(regarq), 0);
                fread(&dados, sizeof(regarq), 1, Ptrarq);
                printf("%d ", dados.info);
            }
        }
        fclose(Ptrarq);

    }
}

/*
d) fazer o algoritmo da exclusão da árvore ABB.
*/
void exclusao_ABB_disco(int info)
{
    regarq dados, pai, filho, sucessor, paiSucessor;
    int pos = 0, terminar = 0;
    int posPai = 0, posFilho;
    int posSucessor, posPaiSucessor;
    FILE *Ptrarq = fopen("dados.dat", "rb+");
    if(!Ptrarq)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        //A raiz fica na posicao 0, mas 0 nos campos esq e dir indica filho vazio

        //Funcao para achar o no para a exclusao
        fread(&dados, sizeof(regarq), 1, Ptrarq);
        while(!feof(Ptrarq) && !terminar && dados.info != info)
        {
            //Guarda o pai antes de descer para poder atualizar o indice do filho
            posPai = pos;
            pai = dados;
            if(info < dados.info)
                pos = dados.esq;
            else
                pos = dados.dir;

            if(pos == 0)
                terminar = 1;
            else
            {
                fseek(Ptrarq, pos*sizeof(regarq), 0);
                fread(&dados, sizeof(regarq), 1, Ptrarq);
            }
        }

        if(!feof(Ptrarq) && !terminar && dados.esq != 0 && dados.dir != 0)
        {
            //O sucessor eh o menor no da subarvore direita
            posPaiSucessor = pos;
            posSucessor = dados.dir;
            fseek(Ptrarq, posSucessor*sizeof(regarq), 0);
            fread(&sucessor, sizeof(regarq), 1, Ptrarq);
            while(!feof(Ptrarq) && sucessor.esq != 0)
            {
                //Guarda o pai para atualizar a ligacao depois da descida
                posPaiSucessor = posSucessor;
                paiSucessor = sucessor;
                posSucessor = sucessor.esq;
                fseek(Ptrarq, posSucessor*sizeof(regarq), 0);
                fread(&sucessor, sizeof(regarq), 1, Ptrarq);
            }

            if(!feof(Ptrarq))
            {
                dados.info = sucessor.info;

                //O sucessor pode ter um filho a direita. Esse filho ocupa o lugar dele
                if(posPaiSucessor == pos)
                    dados.dir = sucessor.dir;
                else
                {
                    paiSucessor.esq = sucessor.dir;
                    fseek(Ptrarq, posPaiSucessor*sizeof(regarq), 0);
                    fwrite(&paiSucessor, sizeof(regarq), 1, Ptrarq);
                }

                //O registro antigo do sucessor fica no arquivo, fora da arvore
                fseek(Ptrarq, pos*sizeof(regarq), 0);
                fwrite(&dados, sizeof(regarq), 1, Ptrarq);
            }
        }
        else if(!feof(Ptrarq) && !terminar)
        {
            //Se o no for folha, posFilho fica 0 e a ligacao fica vazia
            if(dados.esq != 0)
                posFilho = dados.esq;
            else
                posFilho = dados.dir;

            if(pos != 0)
            {
                //O pai passa a apontar para o filho do no excluido ou para 0
                if(pai.esq == pos)
                    pai.esq = posFilho;
                else
                    pai.dir = posFilho;

                fseek(Ptrarq, posPai*sizeof(regarq), 0);
                fwrite(&pai, sizeof(regarq), 1, Ptrarq);
            }
            else if(posFilho != 0)
            {
                //A raiz precisa ficar na posicao 0, entao copia o registro do filho inteiro
                fseek(Ptrarq, posFilho*sizeof(regarq), 0);
                fread(&filho, sizeof(regarq), 1, Ptrarq);
                if(!feof(Ptrarq))
                {
                    fseek(Ptrarq, 0, 0);
                    fwrite(&filho, sizeof(regarq), 1, Ptrarq);
                }
            }
            else
            {
                //Sem raiz, a arvore fica vazia. O modo wb zera o arquivo
                fclose(Ptrarq);
                Ptrarq = fopen("dados.dat", "wb");
                if(!Ptrarq)
                    printf("Erro ao abrir arquivo!\n");
            }
        }
        if(Ptrarq)
            fclose(Ptrarq);
    }
}
/*


e) fazer o algoritmo de balanceamento da árvore ABB.
f) excluir todos os nodos da árvore ABB.
*/

/*Ideias:


Ate agora vou dividir os conhecimentos em chunks

1 - Percorrer arvore em nivel sabendo o nivel e contando, utiliza o algoritmo que guarda NULL sempre que empilhar
2 - Transformar arvore em disco, usando fseek e percorrendo
3 - Balanceamento de arvore AVL, exclusao e balanceamento de arvore ABB usando FB e FB_filho se necessario

*/

int main(void)
{
    return 0;
}
