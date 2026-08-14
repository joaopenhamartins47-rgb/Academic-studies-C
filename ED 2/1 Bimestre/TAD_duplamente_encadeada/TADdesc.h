struct Tpno
{
    int info;
    struct Tpno *ant, *prox;
};typedef struct Tpno tpno;


struct Tpdescritor
{
    tpno *inicio, *fim;
};typedef struct Tpdescritor descritor;

void init (descritor **desc) //inicializar a lista e o descritor
{
    *desc = (descritor*)malloc(sizeof(descritor));
    (*desc)->inicio = NULL;
    (*desc)->fim = NULL;
} 

char isEmpty(tpno *LD)
{
    return LD == NULL;
}


void InserirInicio(descritor *desc, int x)
{
    tpno *novo = (tpno*)malloc(sizeof(tpno));
    novo->info = x;
    novo->ant = novo->prox = NULL;

    if(!isEmpty(desc->inicio))
    {
        novo->prox = desc->inicio;
        desc->inicio->ant = novo;
        desc->inicio = novo;
    }
    else
    {
        desc->inicio = desc->fim = novo;
    }
}

void InserirFinal(descritor *desc, int x)
{
    if(!isEmpty(desc->inicio))
    {
        tpno *novo = (tpno*)malloc(sizeof(tpno));
        novo->info = x;
        novo->prox = NULL;
        novo->ant = desc->fim;
        desc->fim->prox = novo;
        desc->fim = novo;
    }
    else
    {
        tpno *novo = (tpno*)malloc(sizeof(tpno));
        novo->info = x;
        novo->ant = novo->prox = NULL;
        desc->inicio = desc->fim = novo;
    }
}


tpno *Busca(tpno *LD, int x)
{
    while(LD != NULL && LD->info != x)
        LD = LD->prox;

    return LD; 
}

int Exclui(descritor *desc, int x)
{
    tpno *aux = Busca(desc->inicio, x);
    if(aux == NULL)
    {
        printf("Elemento nao encontrado! \n");
        return -1;
    }
    else
    {
        int info = aux->info;
        //4 casos de exclusao
        if (desc->inicio == aux && desc->fim == aux)
            desc->inicio = desc->fim = NULL;

        else if(desc->inicio == aux)
        {
            aux->prox->ant = NULL;
            desc->inicio = aux->prox;
        }
        else if(desc->fim == aux)
        {
            aux->ant->prox = NULL;
            desc->fim = aux->ant;
        }
        else
        {
            aux->ant->prox = aux->prox;
            aux->prox->ant = aux->ant;
        }

        free(aux);
        return info;
    }
    
}

void exibir(descritor *desc)
{
    tpno *aux = desc->inicio;
    while(aux != NULL)
    {
        printf("%d\n",aux->info);
        aux = aux->prox;
    }
}

