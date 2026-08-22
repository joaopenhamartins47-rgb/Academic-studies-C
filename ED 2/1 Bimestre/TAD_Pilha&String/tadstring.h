struct StringD
{
    char letra;
    struct StringD *prox;
};typedef struct StringD sd;


void init_sd(sd **inicio)
{
    *inicio = NULL;
}

void reinicia_s(sd **inicio)
{
    sd *aux; 
    while(*inicio)
    {
        aux = *inicio;
        *inicio = (*inicio)->prox;
        free(aux);
    }
}

void exibe_s(sd *inicio)
{
    while(inicio)
    {
        printf("%c - ", inicio->letra);
        inicio = inicio->prox;
    }
    printf("\n");
}

void exibe_recursivo(sd *inicio)
{
    if(inicio)
    {
        exibe_recursivo(inicio->prox);
        printf(" %c ", inicio->letra);
    }
}

void insere(sd **inicio, char c)
{
    sd *novo = (sd*)malloc(sizeof(sd));
    novo->letra = c;
    novo->prox = NULL;

    if(!*inicio)
        *inicio = novo;
    
    else
    {
        sd *aux = *inicio;
        while(aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
}

void copy(sd *inicio, sd **inicio2)
{
    sd *ultimo = NULL;

    while(inicio)
    {
        sd *novo = (sd*)malloc(sizeof(sd));
        novo->letra = inicio->letra;
        novo->prox = NULL;
        if(!*inicio2)
            *inicio2 = novo;
        else
            ultimo->prox = novo;

        ultimo = novo;
        inicio = inicio->prox;
    }
}
