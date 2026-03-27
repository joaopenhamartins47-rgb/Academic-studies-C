#define MAXPILHA 10

struct Tppilha
{
    int topo;
    char pilha[MAXPILHA];
};

void inicializa(Tppilha &p)
{
    p.topo = -1;
}

void PUSH(Tppilha &p, char elem)
{
    p.pilha[++p.topo] = elem;
}

char POP(Tppilha &p)
{
    char remove = p.pilha[p.topo];
    for(int i = 0; i<p.topo;i++)
    {
        p.pilha[i] = p.pilha[i+1];
    }
    p.topo--;
    return remove;
}

char pilhavazia(int topo)
{
    return topo == -1;
}
char pilhacheia(int topo)
{
    return topo == MAXPILHA-1;
}
char elementotopo(Tppilha p)
{
    return p.pilha[p.topo];
}
char elementoinicio(Tppilha p)
{
    return p.pilha[0];
}
void exibe(Tppilha p)
{
    while(!pilhavazia(p.topo))
        printf("%c ", POP(p));
}