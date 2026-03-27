#define MAXFILA 10

struct elemento
{
    int priori;
    char info;
};

struct Tpfila
{
    int fim;
    char fila[MAXFILA];
};

void inicializa(Tpfila &f)
{
    f.fim = -1;
}

void inserir(Tpfila &f, elemento elem)
{
    
}