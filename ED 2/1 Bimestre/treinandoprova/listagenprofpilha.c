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

void init_p(pilha **p)
{
    *p = NULL;
}

struct filap
{
    struct filap *prox;
    char at[12];
    int nivel;
};

typedef struct filap fila;



void enqueue(fila **f, char info[])
{
    fila *novo = (fila*)malloc(sizeof(fila));

    strcpy(novo->at, info);
    novo->nivel = -1;      
    novo->prox = NULL;

    if (*f == NULL)
    {
        *f = novo;
    }
    else
    {
        fila *aux = *f;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
}

void dequeue(fila **f, char *removido, int *nivel)
{
    fila *aux;

    if (*f == NULL)
    {
        removido[0] = '\0';
        *nivel = -1;
    }
    else
    {
        aux = *f;

        strcpy(removido, aux->at);
        *nivel = aux->nivel;

        *f = aux->prox;

        free(aux);
    }
}

void inserir_fim(Listagen *L, Listagen *elemento)
{
    Listagen *aux;

    if (L->no.lista.cabeca == NULL)
    {
        L->no.lista.cabeca = elemento;
    }
    else
    {
        aux = L;

        while (aux->no.lista.cauda != NULL)
            aux = aux->no.lista.cauda;

        aux->no.lista.cauda = cons(elemento, NULL);
    }
}

void definir_nivel_fila(fila *f, int nivel)
{
    while (f != NULL)
    {
        f->nivel = nivel;
        f = f->prox;
    }
}

char isEmpty(fila *f)
{
    return f == NULL;
}

void init(fila **f)
{
    *f = NULL;
}


//Construir uma lista gen do zero de acordo com uma entrada string que fornece os nomes e a profundidade 

Listagen *construir_listagen_prof(char entrada[])
{
    Listagen *raiz;
    Listagen *atual;
    Listagen *nova;

    pilha *p;
    fila *f;

    int i = 0;
    int j;
    int nivel_atual = 1;
    int nivel_desejado;
    int nivel_atom;

    char palavra[12];

    init_p(&p);
    init(&f);

    raiz = cons(NULL, NULL);

    atual = raiz;

    push(&p, raiz);

    while (entrada[i] != '\0')
    {
        if (entrada[i] == ' ' || entrada[i] == ',' || entrada[i] == '(')
        {
            i++;
        }

        

        else if (entrada[i] >= 'a' && entrada[i] <= 'z')
        {
            j = 0;

            while (entrada[i] >= 'a' && entrada[i] <= 'z')
            {
                palavra[j++] = entrada[i++];
            }

            palavra[j] = '\0';

            
            enqueue(&f, palavra);
        }

        

        else if (entrada[i] == '#')
        {
            i++;
            nivel_desejado = entrada[i] - '0';
            i++;
            
            definir_nivel_fila(&f, nivel_desejado);

            

            while (nivel_atual > nivel_desejado)
            {
                pop(&p, &atual);
                nivel_atual--;
            }

            while (nivel_atual < nivel_desejado)
            {
                
                nova = cons(NULL, NULL);

                
                inserir_fim(atual, nova);

                
                atual = nova;

                
                push(&p, atual);

                nivel_atual++;
            }

            while (!isEmpty(f))
            {
                dequeue(&f, palavra, &nivel_atom);

                
                inserir_fim(atual, criat(palavra));
            }
        }

        
        else if (entrada[i] == ')') //ai volta pra raiz
        {
            while (nivel_atual > 1)
            {
                pop(&p, &atual);
                nivel_atual--;
            }

            i++;
        }

        else
        {
            i++;
        }
    }

    return raiz;
}






int main(void)
{
    return 0;
}