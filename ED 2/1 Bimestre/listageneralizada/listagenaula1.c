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

ListaGen *criat(char info[])
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

/*
Usando as operações Cons() e Criat(), escreva expressões para construir as
seguintes listas:
a) [a, b, c]
b) [a, [b, [c]]]
c) [[[a], b], c]
d) [[a, b, [c]], d]
e) [[[[]]]]
*/
int main(void)
{
    //A
    ListaGen *la = criat("a");
    ListaGen *lb = criat("b");
    ListaGen *lc = criat("c");

    ListaGen *exA = Cons(la, Cons(lb, Cons(lc, NULL)));

    //B
    ListaGen *exB = Cons(criat("a"), Cons(Cons(criat("b"), Cons(Cons(criat("c"), NULL), NULL)), NULL));
    
    //C
    ListaGen *exC = Cons(Cons(Cons(criat("a"), NULL), Cons(criat("b"), NULL)), Cons(criat("c"), NULL));

    //D
    ListaGen *exD = Cons(Cons(criat("a"), Cons(criat("b"), Cons(Cons(criat("c"), NULL), NULL))), Cons(criat("d"), NULL));

    //E
    ListaGen *exE = Cons(Cons(Cons(NULL, NULL), NULL), NULL);
}

