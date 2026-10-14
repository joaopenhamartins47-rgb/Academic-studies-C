struct Arvore
{
    int info;
    struct Arvore *esq, *dir;
};typedef struct Arvore arvore;

struct Pilha
{
    arvore *info;
    struct Pilha *prox;
};
typedef struct Pilha pilha;

struct Fila
{
    arvore *info;
    struct Fila *prox;
};typedef struct Fila fila;

void initF(fila **f)
{
    *f = NULL;
}

void enqueue(fila **f, arvore *info)
{
    fila *novo, *aux;

    novo = (fila*)malloc(sizeof(fila));

    novo->info = info;
    novo->prox = NULL;

    if (*f == NULL)
        *f = novo;
    else
    {
        aux = *f;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
}

void dequeue(fila **f, arvore **info)
{
    fila *aux;

    aux = *f;
    *info = aux->info;

    *f = aux->prox;

    free(aux);

}

int isEmptyF(fila *f)
{
    return f == NULL;
}

void init(pilha **p)
{
    *p = NULL; 
}

void push(pilha **topo, arvore *info)
{
    pilha *novo = (pilha*) malloc(sizeof(pilha));

    if(novo != NULL)
    {
        novo->info = info;
        novo->prox = *topo;
        *topo = novo;
    }
}

void pop(pilha **topo, arvore **removido)
{
    pilha *aux;

    if(*topo == NULL)
        return 0;

    aux = *topo;
    *removido = aux;
    *topo = aux->prox;
    free(aux);
}

char isEmpty(pilha *topo)
{
    return topo == NULL;
}

