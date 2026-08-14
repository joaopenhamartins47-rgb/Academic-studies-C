struct FilaP
{
    int x, p;
    struct FilaP *prox;
};typedef struct FilaP filap;


void init(filap **inicio)
{
    *inicio = NULL;
}

char isEmpty(filap *inicio)
{
    return inicio == NULL;
}

void Enqueue(filap **inicio, int x, int p)
{
    //Criacao de uma caixinha nova
    filap *nova = (filap*)malloc(sizeof(filap));
    //atribui os valores
    nova->x = x;
    nova->p = p;
    

    if(*inicio == NULL) //Primeiro elemento
    {
        nova->prox = NULL;
        *inicio = nova;
    }
    else if (nova->p < (*inicio)->p) //Adicionar no inicio
    {
        nova->prox = *inicio;
        *inicio = nova;
    }
    else
    {
        filap *aux = (*inicio)->prox;
        filap *ant = *inicio;
        while(aux != NULL && aux->p < p) //Adicionar entre 2
        {
            ant = aux;
            aux = aux->prox;
        }

        ant->prox = nova;
        nova->prox = aux;
    } 
}

void Dequeue(filap **inicio, int *x, int *p)
{
    filap *aux = *inicio;
    if(aux == NULL)
        printf("Nenhum elemento na lista! \n");
    else
    {
        (*inicio) = (*inicio)->prox;
        *x = aux->x;
        *p = aux->p;
        free(aux);
        printf("Elemento deletado com sucesso!\n");
    }
}

void exibe(filap *inicio)
{
    filap *aux = inicio;
    while(aux != NULL)
    {
        printf("Elemento: %d, Prioridade: %d\n", aux->x, aux->p);
        aux = aux->prox;
    }
}