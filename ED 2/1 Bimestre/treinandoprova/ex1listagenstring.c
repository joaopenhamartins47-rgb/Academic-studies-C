#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Faça um algoritmo para construir uma lista generalizada L a partir de uma string passada por parâmetro. Você deve percorrer a string para construir a lista generalizada de maneira recursiva.
Exemplo de string passada por parâmetro:
[[um, dois], três]
Utilize uma pilha com as seguintes operações:
Init(P), Top(P), Push(P,x), Pop(P,x) e IsEmpty(P)
onde P é do tipo ListaGen*
*/

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
    if(nulo(L)||atomo(L))
    {
        printf("O argumento deve ser uma lista nao vazia\n");
        return NULL;
    }
    else
        return L->no.lista.cabeca;
}

Listagen *tail(Listagen *L)
{
    if(nulo(L)||atomo(L))
    {
        printf("O argumento deve ser uma lista nao vazia\n");
        return NULL;
    }
    else
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


struct pilhap
{
    struct pilhap *cabeca;
    Listagen *info;
};typedef struct pilhap pilha;


char vazia(pilha *p)
{
    return p == NULL;
}
void push(pilha **p, Listagen *info)
{
    //Primeiro, cria a caixinha
    pilha *novo = (pilha*)malloc(sizeof(pilha));
    novo->info = info;
    novo->cabeca = NULL;
    if(!*p)
    {
        *p = novo;
    }
    else
    {
        novo->cabeca = *p;
        *p = novo;
    }
}

void pop(pilha **p, Listagen **removido)
{
    pilha *aux;
    aux = *p;
    *removido = (*p)->info;
    *p = (*p)->cabeca;
    free(aux);
}

void init(pilha **p)
{
    *p = NULL;
}

//"[[um,dois],três]"

void string_to_listagen(Listagen **L, char expressao[])
{
    int i, j, entrou=0;
    char palavra[20];
    Listagen *aux = *L;
    pilha *p;
    init(&p);
    for(i = 0; expressao[i] != '\0'; i++)
    {
        j=0;
        while(expressao[i] >= 'a' && expressao[i] <= 'z' && expressao[i] != '\0')
        {
            palavra[j++] = expressao[i++];
            entrou = 1;
        }
        if(entrou)
        {
            palavra[j] = '\0';
            if(!vazia(p))
                pop(&p, &aux);
            aux->no.lista.cabeca = criat(palavra);
            entrou = 0;
        }

        if(expressao[i] == '[')
        {
            if(*L == NULL)
            {   
                *L = cons(NULL, NULL);
                aux = *L;
                push(&p, aux);
            }
            else
            {
                aux->no.lista.cabeca = cons(NULL, NULL);
                push(&p, head(aux));
            }
        }
        else if(expressao[i] == ']')
        {
            aux->no.lista.cauda = NULL;
            if(!vazia(p))
                pop(&p, &aux);
        }
        else if(expressao[i] == ',')
        {
            aux->no.lista.cauda = cons(NULL, NULL);
            aux = aux->no.lista.cauda;
            push(&p,aux);
        }
    }
}

int main(void)
{

}