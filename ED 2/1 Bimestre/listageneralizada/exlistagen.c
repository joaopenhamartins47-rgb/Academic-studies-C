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

Listagen *criat(char info[])
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    novo->terminal = 1;
    strcpy(novo->no.info, info);
    return novo;
}

Listagen *cons(Listagen *H, Listagen *T)
{
    if(atomo(T))
    {
        printf("O segundo argumento nao pode ser um atomo!\n");
        return NULL;
    }
    else{
        Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
        novo->terminal = 0;
        novo->no.lista.cabeca = H;
        novo->no.lista.cauda = T;
        return novo;
    }
}

// 1 - Fazer um algoritmo pra destruir uma lista gen

//Temos 2 formas inicialmente de percorrer uma lista gen, uma delas é percorrer recursivamente pelo head e depois pelo tail, a outra é percorrer em linhas, utilizando fila.

void destruir(Listagen **L)
{
    if(!nulo(*L))
    {
        if(atomo(*L))
            free(*L);
        else
        {
            destruir(&(*L)->no.lista.cabeca);
            destruir(&(*L)->no.lista.cauda);
            free(*L);
            *L = NULL;
        }
    }
}

// 2 - Fazer um algoritmo para duplicar uma lista generalizada fornecida por parâmetro.

// A ideia eh criar um cons com a cabeca e cauda da lista atual, percorrendo recursivamente

Listagen *head(Listagen *L)
{
    if(atomo(L)){
        printf("O argumento deve ser uma lista\n");
        return NULL;
    }
        
    return L->no.lista.cabeca;
}

Listagen *tail(Listagen *L)
{
    if(atomo(L)){
        printf("O argumento deve ser uma lista\n");
        return NULL;
    }
        
    return L->no.lista.cauda;
}

Listagen *dup(Listagen *L)
{
    if(nulo(L))
        return NULL;
    if(atomo(L))
        return criat(L->no.info);
    return cons(dup(head(L)), dup(tail(L)));
}

// 3 - Fazer um algoritmo (função boolean) para comparar duas listas generalizadas passadas por parâmetro.

char comp(Listagen *L, Listagen *L2)
{
    if(nulo(L) && nulo(L2))
        return 1;
    if(nulo(L) || nulo(L2))
        return 0;
    if(atomo(L) && atomo(L2))
        return 1;
    if(atomo(L) || atomo (L2))
        return 0;

    return comp(head(L), head(L2)) && comp(tail(L), tail(L2));
}


/*
4 - Numa lista generalizada, cada par de colchetes serve para indicar um nível de aninhamento. Por exemplo, na lista [a,[b,[c],d],e], os elementos a, [b,[c],d] e e pertencem ao primeiro nível de aninhamento, os elementos b, [c] e d pertencem ao segundo nível, e o elemento c pertence ao terceiro. Freqüentemente, o primeiro nível de aninhamento é denominado top-level, enquanto o último (aquele mais interno) é chamado botton-level. Com base nisto, podemos definir dois novos conceitos relacionados a uma lista generalizada L:
*/

// a) codifique a rotina Len(L), que dá o comprimento de uma lista generalizada L. Admita que a lista nula tem comprimento 0 e que a operação não pode ser aplicada a átomos.

void comprimento_lista(Listagen *L, int *cont)
{
    if(!nulo(L))
    {
        (*cont)++;
        comprimento_lista(tail(L), &*cont);
    }
}

// b) codifique a rotina Deph(L), que dá a profundidade de uma lista generalizada L. Admita que átomos têm profundidade 0 e listas vazias têm profundidade 1.

void profundidade_lista(Listagen *L, int p, int *maior)
{
    if(!nulo(L) && !atomo(L))
    {
        if(p > *maior)
            *maior = p;
        profundidade_lista(head(L), p+1, &*maior);
        profundidade_lista(tail(L), p, &*maior);
    }
}

int calc_profundidade(Listagen *L)
{
    int maior = 0;
    profundidade_lista(L, 1, &maior);
    return maior;
}

/*
5:-) Codifique a rotina Append(L, M), que concatena as listas generalizadas L e M. Por exemplo, para L:[a,[b,[c],d],e,[f]] e M:[g,[],[h]], a operação R:=Append(L, M) resultará na lista R:[a,[b,[c],d],e,[f],g,[],[h]].
*/

void concatenar_lista(Listagen **L, Listagen *L2)
{
    if(!nulo(*L))
    {
        if(!tail(*L))
        (*L)->no.lista.cauda = L2;
    
        else
            concatenar_lista(&(*L)->no.lista.cauda, L2);
    } 
}

/*
6:-) Codifique a rotina Replace(O,N,L), que substitui todas as ocorrências do elemento O, em L, por um novo elemento N.
*/

void Replace(char *o, char *n, Listagen **L)
{
    if(!nulo(*L))
    {
        if(atomo(*L))
        {
            if(strcmp((*L)->no.info, o) == 0)
                strcpy((*L)->no.info, n);
        }
        else
        {
            Replace(o, n, &(*L)->no.lista.cabeca);
            Replace(o, n, &(*L)->no.lista.cauda);
        }
    }  
}

//7:-) Codifique a rotina TopLevel(L), que cria e retorna lista contendo apenas os elementos que se encontram no top-level da lista L.

Listagen *TopLevel(Listagen *L)
{
    Listagen *ListaTop = NULL;
    while(!nulo(L))
    {
        if(atomo(head(L)))
        {
            if(!ListaTop)
                ListaTop = Cons(Cons(criat(L->no.info), NULL), NULL);
            else
            {
                Listagen *aux = ListaTop;
                while(tail(aux) != NULL)
                    aux = tail(aux);

                //Para um antes
                aux->no.lista.cauda = Cons(Cons(criat(L->no.info), NULL), NULL);
            }
        }
        L = tail(L);
    }
    return ListaTop;
}

/*
8:-) Codifique a rotina Nth(L,n), que retorna o n-ésimo elemento existente no top-level de L.
*/

char Nth(Listagen *L, int n)
{
    int cont = 0;
    while(!nulo(L) && cont <= n)
    {
        if(atomo(head(L)))
        {
            cont++;
            if(cont == n)
                return head(L)->no.info;
        }
        L = tail(L);
    }
    return 0;
}

/*
9:-) Codifique a rotina Plain(L), que transforma a lista L numa lista de profundidade 1. Por exemplo, sendo a lista L:[a,[b,[c,d]],[],e], Plain(L) transformá-la-ia na lista L:[a,b,c,d,e].
*/

/*
Ideias: L vai andar de lado

Preciso percorrer pelos head, se nao for atomo, ele continua andando ate ser, 
*/

//Da pra fazer recursivo, empilha ate achar o atomo, ai desempilha deletando e quando chegar a primeira chamada coloca o head apontando pro atomo salvo dentro de uma variavel

//Da pra eu usar uma estrutura do tipo fila, enfileirar os atomos percorrendo a lista, depois percorrer dnv para deletar os atomos e estruturas da lista e criar novas caixas de conexao, oq eu devo considerar:

//Deletar apenas quando tiver sublistas, e garantir que os ponteiros nao se percam ao colocar no top level

struct fila
{
    char info[8];
    struct fila *prox;
};typedef struct fila filap;

void init(filap **f)
{
    *f = NULL;
}

void enqueue(filap **f, char info[])
{
    filap *novo = (filap*)malloc(sizeof(filap));

    strcpy(novo->info, info);
    novo->prox = NULL;

    if(!*f)
        *f = novo;
    else
    {
        filap *aux = *f;

        while(aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
}

char isEmpty(filap *f)
{
    return f == NULL;
}

void dequeue(filap **f, char *removido)
{
    if(!isEmpty(*f))
    {
        filap *aux = *f;
        strcpy(removido, (*f)->info);
        *f = (*f)->prox;
        free(aux);
    }
    
}



void Armazenar_atomos(Listagen *L, filap **f)
{
    //Percorrer a lista principal
    while(L != NULL)
    {
        if(atomo(head(L)))
            enqueue(&*f, head(L)->no.info);
        else //sublista
        {
            Armazenar_atomos(head(L), &*f);
        }
        L = tail(L);
    }
}

void destruir_lista(Listagen **L)
{
    if(!nulo(*L))
    {
        if(!atomo(*L))
        {
            destruir_lista(&(*L)->no.lista.cabeca);
            destruir_lista(&(*L)->no.lista.cauda);
            free(*L);
        }
        else
        {
            free(*L);
        }
        *L = NULL;

        
    }
}

void Plain_3(Listagen **L, filap *f)
{
    Armazenar_atomos(*L, &f);
    destruir_lista(&*L);
    while(!isEmpty(f))
    {
        char info[8];
        
        dequeue(&f, info);
        Listagen *novo = criat(info);
        if(!*L)
            *L = cons(cons(novo, NULL), NULL);
        else
        {
            Listagen *aux = *L;
            while(tail(aux))
                aux = tail(aux);
            aux->no.lista.cauda = cons(cons(novo, NULL), NULL);
        }
    }
}

// Outra forma de fazer, com uma funcao só

void Plain(Listagen **L)
{
    if(!nulo(*L))
    {
        if(atomo(head(*L)))
            Plain(&(*L)->no.lista.cauda);
        else
        {
            Listagen *sub = head(*L);
            Plain(&sub);

            Listagen *velho = *L;

            if(sub == NULL)
            {
                *L = tail(*L);
                free(velho);
                Plain(&*L);
            }
            else
            {
                Listagen *ultimo = sub;

                while(tail(ultimo) != NULL)
                    ultimo = tail(ultimo);

                ultimo->no.lista.cauda = tail(*L);

                *L = sub;
                free(velho);

                Plain(&ultimo->no.lista.cauda);
            }
        }
    }
}

int main(void)
{
    return 0;
}