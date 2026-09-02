#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct reg_lista
{
    struct listagen *cabeça;
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
};typedef struct listagen ListaGen;


char nulo(ListaGen *L)
{
    return L == NULL;
}

char atomo(ListaGen *L)
{
    return !nulo(L) && L->terminal;
}

ListaGen *head(ListaGen *L)
{
    if(nulo(L)||atomo(L))
    {
        printf("O argumento deve ser uma lista nao vazia\n");
        return NULL;
    }
    else
        return L->no.lista.cabeça;
}

ListaGen *tail(ListaGen *L)
{
    if(nulo(L)||atomo(L))
    {
        printf("O argumento deve ser uma lista nao vazia\n");
        return NULL;
    }
    else
        return L->no.lista.cauda;
}

// A ideia aqui é percorrer de forma recursiva os head e de forma iterativa as caudas

void exibemisto(ListaGen *L)
{
    if(!nulo(L))
    {
        if(atomo(L))
            printf("%s\n", L->no.info);
        else
        {
            printf("[");
            while(!nulo(L))
            {
                exibemisto(head(L)); //Percorre os head
                L = tail(L); //Avança pela cauda
                if(!nulo(L))
                    printf(",");

            }
            printf("]");
        }
    }
}



int main(void)
{


    return 0;
}