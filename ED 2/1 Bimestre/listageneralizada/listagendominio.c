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







int main(void)
{
    return 0;
}