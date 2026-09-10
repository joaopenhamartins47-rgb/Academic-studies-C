#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct reg_lista
{
    struct listagen *cabeca;
    struct listagen *cauda;
};

union info_lista
{
    char info[8];
    struct reg_lista lista;
};

struct listagen
{
    char terminal;
    union info_lista no;
};typedef struct listagen Listagen;

char nulo(Listagen *L)
{
    return L == NULL;
}

char atomo(Listagen *L)
{
    return !nulo(L) && L->terminal;
}

Listagen *head(Listagen *L)
{
    if(nulo(L) || atomo(L))
    {
        printf("O argumento nao pode ser um atomo\n");
        return NULL;
    }
    else
        return L->no.lista.cabeca;
}

Listagen *tail(Listagen *L)
{
    if(nulo(L) || atomo(L))
    {
        printf("O argumento nao pode ser um atomo e nao pode ser nulo\n");
        return NULL;
    }
    return L->no.lista.cauda;
}

Listagen *criat(char info[])
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    strcpy(novo->no.info, info);
    novo->terminal = 1;
    return novo;
}

Listagen *cons(Listagen *H, Listagen *T)
{
    if(atomo(T))
    {
        printf("O segundo argumento nao pode ser atomo!\n");
        return NULL;
    }
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    novo->terminal = 0;
    novo->no.lista.cabeca = H;
    novo->no.lista.cauda = T;
    return novo;
}


/*
Faça um algoritmo que receba uma Lista Generalizada L por parâmetro e a retorne
ordenando todos os átomos de cada uma de suas sublistas. O algoritmo deve ordenar os
átomos em cada Lista Generalizada (sublista).
*/

//A ideia aqui eh inicialmente identificar todos os cabeca de lista, incluindo os da sublista, pra isso iremos precisar de 2 estruturas do tipo fila, uma pra percorrer a lista e outra pra utilizar na ordenacao

//Primeiro, a ordenacao em linha com selecao direta

void selecao_direta(Listagen *L)
{
    Listagen *pi = L; //Vou andar com pi, mas pode-se andar com L tambem
    Listagen *pj, *pmenor;

    while(!nulo(tail(pi))) //Pois iremos parar no ultimo no
    {
        if(atomo(head(pi)))
        {
            pmenor = pi;
            pj = tail(pi); //Pois o pj comeca um a frente do pi
            //Percorre a linha do pj
            while(!nulo(pj))
            {
                if(atomo(head(pj)))
                {
                    if(strcmp(head(pj)->no.info, head(pmenor)->no.info) < 0)
                        pmenor = pj;
                }
                pj = tail(pj);
            }
            char aux[8];
            //Realiza a permutacao com aux
            strcpy(aux, head(pi)->no.info);
            strcpy(head(pi)->no.info, head(pmenor)->no.info);
            strcpy(head(pmenor)->no.info, aux);
        }
        pi = tail(pi);
    }
}

//Agora iremos salvar na fila os inicios de cada lista e sublista

struct filap
{
    Listagen *info;
    struct filap *prox;
};typedef struct filap fila;

void init(fila **f)
{
    *f = NULL;
}

char vazio(fila *f)
{
    return f == NULL;
}

void enqueue(fila **f, Listagen *info)
{
    fila *novo = (fila*)malloc(sizeof(fila));
    novo->info = info;
    novo->prox = NULL;
    if(!*f)
        *f = novo;
    else
    {
        fila *aux = *f;
        while(aux->prox != NULL)
            aux = aux->prox;
        aux->prox = novo;
    }
}

void dequeue(fila **f, Listagen **removido)
{
    *removido = (*f)->info;

    Listagen *aux = *f;
    *f = (*f)->prox;
    free(aux);
}

void ordena_listas(Listagen *L)
{
    fila *f1, *f2;
    init(&f1);
    init(&f2);
    enqueue(&f1, L);
    enqueue(&f2, L);
    while(!vazio(f1))
    {
        dequeue(&f1, &L);
        while(!nulo(L))
        {
            if(!nulo(head(L)) && !atomo(head(L))) //Se nao for nulo, nem atomo, so pode ser uma lista
            {
                enqueue(&f1, head(L));
                enqueue(&f2, head(L));
            }
            L = tail(L);
        }
    }
    while(!vazio(f2))
    {
        dequeue(&f2, &L);
        selecao_direta(L);
    }
}

/*
2:-) Faça um algoritmo para inserir um elemento (átomo) em cada uma das sublistas de
uma Lista Generalizadas L. A Lista Generalizada possui os átomos em ordem e o
elemento deve ser inserido obedecendo essa ordem.
Exemplos de chamada do algoritmo: insere(&L, “b”, 1); //Não insere, pois já tem o “b”!
insere(&L, “b”, 2);

*/

//Primeiro vou guardar na fila o inicio de cada sublista

//Funcao de procurar se aquele atomo ja existe
char tem_atomo(Listagen *L, char atomo[])
{
    while(L != NULL && strcmp(L->no.lista.cabeca->no.info, atomo) != 0)
        L = tail(L);
    if(L == NULL)
        return 0;
    return 1;
}

/*
Codigo de exemplo insercao direta
void insercao_direta(int v[], int *n, int x)
{
    int i = *n - 1;

    while(i >= 0 && x < v[i])
    {
        v[i + 1] = v[i];
        i--;
    }

    v[i + 1] = x;
    (*n)++;
}
*/
void insercao_direta(Listagen **L, char info[])
{
    Listagen *p = *L;
    Listagen *ant = NULL;
    int achou = 0;

    while(!nulo(p) && !achou)
    {
        if(atomo(head(p)))
        {
            if(strcmp(info, head(p)->no.info) < 0)
                achou = 1;
            else
            {
                ant = p;
                p = tail(p);
            }
        }
        else
        {
            ant = p;
            p = tail(p);
        }
    }

    Listagen *novo = cons(criat(info), p);

    if(ant == NULL)
        *L = novo;
    else
        ant->no.lista.cauda = novo;
}

void insere(Listagen *L, char info[], int pos) //Percorro com o f1 e no f2 coloco todos os inicios da lista daquela profundidade
{
    fila *f1, *f2;
    init(&f1);
    init(&f2);
    enqueue(&f1, L);
    int prof = 1;
    while(!vazio(f1))
    {
        int qtde = 0;
        fila *aux = f1;

        //Verifica quantas listas tem no nivel dos que ja estao na fila
        while(aux != NULL)
        {
            qtde++;
            aux = aux->prox;
        }

        //Processa somente as listas do nivel
        while(qtde > 0)
        {
            dequeue(&f1, &L);
            if(prof == pos)
            {
                enqueue(&f2, L);
            }
            
            else
            {
                while(L != NULL)
                {
                    if(!nulo(head(L)) && !atomo(head(L)))
                        enqueue(&f1, head(L));
                    L = tail(L);
                }
            }
            qtde--;
        }
        prof++;
    }
    while(!vazio(f2))
    {
        
        dequeue(&f2, &L);
        int ta = tem_atomo(L, info);
        if(ta)
        {
            printf("Nao foi possivel adicionar pois o atomo ja existe nesse nivel\n");
        }
        else
            insercao_direta(&L, info);
    }
    
}


// Andar de forma iterativa utilizando pilha

struct pilhap
{
    Listagen *info;
    struct pilhap *prox;
};typedef struct pilhap pilha;

char vazia(pilha *p)
{
    return p == NULL;
}

void push(pilha **p, Listagen *info)
{
    pilha *novo = (pilha*)malloc(sizeof(pilha));
    novo->info = info;
    novo->prox = NULL;
    if(!*p)
        *p = novo;
    else
    {
        novo->prox = *p;
        *p = novo;
    }
}

void pop(pilha **p, Listagen **removido)
{
    *removido = (*p)->info;
    pilha *aux = *p;
    *p = (*p)->prox;
    free(aux);
}


void exibeI(Listagen *L)
{
    //A ideia aqui eh o codigo ter duas partes, uma para andar para baixo, colocando na pilha o head e outra pra andar uma vez de lado, simulando recursividade, mas de forma iterativa
    pilha *p;
    init(&p);
    push(&p, L);
    while(!vazia(p))
    {
        if(!nulo(L))
        {
            pop(&p, &L);
            while(!nulo(L) && !atomo(L))
            {
                //Coloca todos os head desse novo L cabeca de lista
                push(&p, L);
                L = head(L);
            }
            if(atomo(L))
                printf("%s\n", L->no.info);
        }
        pop(&p, &L);
        L = tail(L);
        if(!nulo(L))
            push(&p, L);
    }

}





int main(void)
{
    return 0;
}