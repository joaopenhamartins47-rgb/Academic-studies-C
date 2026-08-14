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
    if(!isEmpty(desc->inicio))
    {
        tpno *novo = (tpno*)malloc(sizeof(tpno));
        novo->info = x;
        novo->prox = desc->inicio;
        novo->ant = NULL;
        desc->inicio->ant = novo;
        desc->inicio = novo;
    }
    else
    {
        tpno *novo = (tpno*)malloc(sizeof(tpno));
        novo->info = x;
        novo->ant = novo->prox = NULL;
        desc->inicio = desc->fim = novo;
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

