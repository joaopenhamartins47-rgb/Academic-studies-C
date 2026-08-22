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
    sd *ultimo = *inicio2;

    if (ultimo)
        while (ultimo->prox != NULL)
            ultimo = ultimo->prox;
    

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


void concatenar(sd *inicio, sd *inicio2, sd **inicio3)
{
    copy(inicio, inicio3);
    copy(inicio2, inicio3);
}

//Remove da string str1, a quantidade de caracteres especificado por nro a partir da posição start;

void remover(sd **inicio, int nro, int start)
{
    sd *ant, *aux;

    if(start == 0)
    {
        while(*inicio != NULL && nro > 0)
        {
            aux = *inicio;
            *inicio = (*inicio)->prox;
            free(aux);
            nro--;
        }
    }
    else
    {
        ant = *inicio;
        while(ant != NULL && start > 1) //Maior que 1 pq queremos parar uma casa antes dos elementos que serao deletados
        {
            ant = ant->prox;
            start--;
        }
        if(ant)
        {
            while(ant->prox != NULL && nro > 0)
            {
                aux = ant->prox;
                ant->prox = ant->prox->prox;
                free(aux);
                nro--;
            }
        }
    }
}