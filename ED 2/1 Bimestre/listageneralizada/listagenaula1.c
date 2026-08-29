#include <stdio.h>

//Estrutura da lista gen

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


//Criacao de uma lista gen com informacoes

ListaGen *criar_lista_gen(char info[])
{
    ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
    
    //Atribuicao
    L->terminal = 1;
    strcpy(L->no.info, info);
    return L;
}

char nulo(ListaGen *L)
{
    return L == NULL;
}

char atomo(ListaGen *L)
{
    return !nulo(L) && L->terminal;
}

ListaGen *Cons(ListaGen *H, ListaGen *T)
{
    if(atomo(T))
    {
        printf("Segundo argumento nao pode ser atomo!");
        return NULL;
    }
    else
    {
        ListaGen *L = (ListaGen*)malloc(sizeof(ListaGen));
        L->terminal = 0;
        L->no.lista.cabeça = H;
        L->no.lista.cauda = T;
        return L;
    }
}

ListaGen *Head(ListaGen *L)
{
    if(atomo(L) || nulo(L))
    {
        printf("Argumento deve ser uma lista nao vazia!");
        return NULL;
    }
    else
    {
        return L->no.lista.cabeça;
    }
}

ListaGen *Tail(ListaGen *L)
{
    if(atomo(L) || nulo(L))
    {
        printf("Argumento deve ser uma lista nao vazia");
        return NULL;
    }
    else
        return L->no.lista.cauda;
}

