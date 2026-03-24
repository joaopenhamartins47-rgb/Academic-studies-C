#define MAXFILA 100

struct tarefa {
    char tipo;     
    int prioridade;         
    int tempo_total;       
    int tempo_restante;    
    int tempo_chegada;     
    int tempo_inicio;      
};

struct fila {
    int fim;                        
    tarefa f[MAXFILA];      
};


struct processador {
    int ocupado;                   
    struct tarefa atual;           
    int tarefas_executadas;        
};

void inicializa(fila &f);
char filavazia(int fim);
char filacheia(int fim);
void inserir(fila &f, tarefa elem);
tarefa remover(fila &f);
tarefa elementoinicio(fila f);
tarefa elementofim(fila f);
void exibir(fila f);

void inicializa(fila &f)
{
    f.fim = -1;
}

char filavazia(int fim)
{
    return fim == -1;
}
char filacheia(int fim)
{
    return fim == MAXFILA-1;
}

void inserir(fila &f, tarefa tar)
{
    int i, achou=0;
    tarefa aux;
    f.f[++f.fim] = tar;
    for(i = f.fim; i>0 && !achou; i--)
    {
        if(f.f[i].prioridade < f.f[i-1].prioridade) //1 - Alta 2 - Media 3 - Baixa
        {
            aux = f.f[i];
            f.f[i] = f.f[i-1];
            f.f[i-1] = aux;
        }
            
        else
            achou = 1;
    }
}

tarefa remover(fila &f)
{
    tarefa aux;
    aux = f.f[0];
    for(int i=0; i < f.fim; i++)
        f.f[i] = f.f[i+1];
    f.fim--;
    return aux;
}

tarefa elementoinicio(fila f)
{
    return f.f[0];
}

tarefa elementofim(fila f)
{
    return f.f[f.fim];
}

void exibir(fila f)
{
    tarefa aux;
    while(!filavazia(f.fim))
    {
        aux = remover(f);
        printf("Info: %d, Prioridade: %d\n", aux.tipo, aux.prioridade);
    }
}