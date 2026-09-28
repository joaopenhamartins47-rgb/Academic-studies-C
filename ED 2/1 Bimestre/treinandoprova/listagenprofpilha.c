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
};

typedef struct filap fila;



void enqueue(fila **f, char info[])
{
    fila *novo = (fila*)malloc(sizeof(fila));

    strcpy(novo->at, info);
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

void dequeue(fila **f, char *removido)
{
    fila *aux;

    if (*f == NULL)
    {
        removido[0] = '\0';
    }
    else
    {
        aux = *f;

        strcpy(removido, aux->at);

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


char isEmpty(fila *f)
{
    return f == NULL;
}

void init(fila **f)
{
    *f = NULL;
}

Listagen *nova_celula_fim(Listagen *L)
{
    Listagen *aux;
    Listagen *nova;

    nova = cons(NULL, NULL);

    aux = L;

    while (aux->no.lista.cauda != NULL)
        aux = aux->no.lista.cauda;

    aux->no.lista.cauda = nova;

    return nova;
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

    char palavra[12];

    init_p(&p);
    init(&f);

    raiz = cons(NULL, NULL);

    atual = raiz;

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

            nivel_desejado = 0;

            while (entrada[i] >= '0' && entrada[i] <= '9')
            {
                nivel_desejado = nivel_desejado * 10 + (entrada[i] - '0');
                i++;
            }

            while (nivel_atual > nivel_desejado)
            {
                pop(&p, &atual);
                nivel_atual--;
            }

            while (nivel_atual < nivel_desejado)
            {
                nova = cons(NULL, NULL);

              
                inserir_fim(atual, nova);

                
                push(&p, atual);

               
                atual = nova;

                nivel_atual++;
            }

            /* Coloca os átomos pendentes neste nível */
            while (!isEmpty(f))
            {
                dequeue(&f, palavra);

                inserir_fim(atual, criat(palavra));
            }
        }

        /* Terminou um grupo: volta para a raiz */
        else if (entrada[i] == ')')
        {
            
            while (nivel_atual > 1)
            {
                pop(&p, &atual);
                nivel_atual--;
            }

            i++;

            /* Ignora vírgula e espaços */
            while (entrada[i] == ' ' || entrada[i] == ',')
                i++;

           
            if (entrada[i] != '\0')
            {
                atual = nova_celula_fim(raiz);
            }
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