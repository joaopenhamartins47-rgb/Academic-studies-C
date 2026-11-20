#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADarvore.h"


//Funcao pra exibir a arvore em nivel
typedef arvore Tree;

struct regArquivo
{
    int esq, info, dir;
};typedef struct regArquivo regarq;


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

//Arvore AVL em disco, verificar se eh AVL ou nao em todos os nos e fazer a exclusao em disco

//Funcao para verificar a altura dado uma arvore em disco, para motivos de revisao vou fazer a funcao usando arvore em memoria e depois arvore em disco

int altura_recursiva_memoria(Tree *raiz)
{
    int esq, dir;

    if(raiz)
    {
        esq = altura_recursiva_memoria(raiz->esq);
        dir = altura_recursiva_memoria(raiz->dir);

        if(esq > dir)
            return 1 + esq;
        else
            return 1 + dir;
    }
    return 0;
}

typedef struct FilaDisco filaDisco;
void initFD(filaDisco **f);
void enqueueD(filaDisco **f, int info);
void dequeueD(filaDisco **f, int *info);
int isEmptyFD(filaDisco *f);

int altura_disco(FILE *Ptrarq, int pos)
{
    //Aqui vou usar a ideia de guardar o NULL e acrescentar a altura
    regarq dados;
    int h = 0, valor;
    filaDisco *f;
    initFD(&f);
    fseek(Ptrarq, pos*sizeof(regarq), 0);
    fread(&dados, sizeof(regarq), 1, Ptrarq);
    if(!feof(Ptrarq))
    {
        h=1;
        if(dados.esq != 0)
            enqueueD(&f, dados.esq);
        if(dados.dir != 0)
            enqueueD(&f, dados.dir);
        if(!isEmptyFD(f))
            enqueueD(&f, 0);

        while(!isEmptyFD(f))
        {
            dequeueD(&f, &valor);
            if(valor != 0)
            {
                fseek(Ptrarq, valor*sizeof(regarq), 0);
                fread(&dados, sizeof(regarq), 1, Ptrarq);
                if(dados.esq != 0)
                    enqueueD(&f, dados.esq);
                if(dados.dir != 0)
                    enqueueD(&f, dados.dir);
            }
            else
            {
                h++;
                if(!isEmptyFD(f))
                    enqueueD(&f, 0);
            }
        }
    }

    return h;
}

char verifica_AVL_disco()
{
    filaDisco *f;
    int AVL=1, FB, alt_esq, alt_dir, valor;
    regarq dados;
    initFD(&f);
    FILE *Ptrarq = fopen("AVL.dat", "rb");
    if(!Ptrarq)
    {
        printf("Erro ao abrir arquivo! \n");
        AVL = 0;
    }
    else
    {
        enqueueD(&f, 0);
        while(!isEmptyFD(f) && AVL)
        {
            dequeueD(&f, &valor);
            fseek(Ptrarq, valor*sizeof(regarq), 0);
            fread(&dados, sizeof(regarq), 1, Ptrarq);
            if(!feof(Ptrarq))
            {
                alt_dir = alt_esq = 0;
                if(dados.esq != 0)
                    alt_esq = altura_disco(Ptrarq, dados.esq);
                if(dados.dir != 0)
                    alt_dir = altura_disco(Ptrarq, dados.dir);

                FB = alt_dir - alt_esq;
                if(FB < -1 || FB > 1)
                    AVL = 0;
                else
                {
                    if(dados.esq != 0)
                        enqueueD(&f, dados.esq);
                    if(dados.dir != 0)
                        enqueueD(&f, dados.dir);
                }
            }
        }

        //Libera os nos da fila se encontrou um no desbalanceado antes do fim
        while(!isEmptyFD(f))
            dequeueD(&f, &valor);
        fclose(Ptrarq);
    }
    return AVL;
}






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
};

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

int contar_nos(Tree *raiz)
{
    if(raiz)
    {
        return 1+ contar_nos(raiz->esq) + contar_nos(raiz->dir);
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

void balanceamento_perfeito_ABB(Tree **raiz) //sem ser disco
{
    //A ideia do algoritmo de balanceamento eh contar os nos da direita subtraindo com o da esquerda, se sair do range -1 0 1, precisa de balancemento

    //Para o balanceamento, precisamos verificar todos os niveis da arvore, utilizando uma fila

    //Copiamos o valor que precisaremos recolocar na arvore

    //Iremos avancando na arvore normalmente, se tiver filho na esquerda ou na direita

    //Busca a exclusao
    
    //Faz a exclusao e reinsere 


    int FB, qtdeE, qtdeD, aux;
    Tree *no = *raiz, *ex, *pai;
    fila *f;
    initF(&f);
    enqueue(&f, no);

    while(!isEmptyF(f))
    {
        dequeue(&f, &no);
        do
        {
            qtdeD = qtdeE = FB = 0;
            qtdeD = contar_nos(no->dir);
            qtdeE = contar_nos(no->esq);

            FB = qtdeD - qtdeE;

            if(FB < -1 || FB > 1)
            {
                aux = no->info;



                //Faz a busca, exclui e insere
                busca_exclusao(no, aux, &ex, &pai);


                //Avanca pq vou excluir o no atual ou substituir ele
                if(!no->esq)
                    no = no->dir;
                else if(!no->dir)
                    no = no->esq;

                if(FB < 0) //Exclui do lado esquerdo
                    excluir_no_arvore(&*raiz, pai, ex, 'e', aux);
                else
                    excluir_no_arvore(&*raiz, pai, ex, 'd', aux);

                insereABB(&*raiz, aux);
            }

        } while (FB < -1 || FB > 1);
        
        if(no->esq)
            enqueue(&f, no->esq);
        if(no->dir)
            enqueue(&f, no->dir);
    }
} 


/*
f) excluir todos os nodos da árvore ABB.
*/

void excluir_todos_ABB_disco()
{
    FILE *Ptrarq = fopen("dados.dat", "wb");
    fclose(Ptrarq);
}


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
