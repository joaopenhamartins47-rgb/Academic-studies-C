struct PilhaD
{
    int info;
    struct FilaD *prox;
};typedef struct PilhaD pilhad;


void init(pilhad **cabeca)
{
    *cabeca = NULL;
}

void PUSH(pilhad **cabeca, int x)
{
    pilhad *novo = (pilhad*)malloc(sizeof(pilhad));
    novo->info = x;
    if(!*cabeca)
        novo->prox = NULL;
    else
        novo->prox = *cabeca;

    *cabeca = novo;

}

char isEmpty(pilhad *cabeca)
{
    return cabeca == NULL;
}

void POP(pilhad **cabeca, int *x)
{
    pilhad *aux;
    if(!isEmpty(*cabeca))
    {
        aux = *cabeca;
        *cabeca = (*cabeca)->prox;
        *x = aux->info;
        free(aux);
    }
}

void exibir(pilhad *cabeca)
{
    while(cabeca)
    {
        printf("Info: %d\n", cabeca->info);
        cabeca = cabeca->prox;
    }
}

