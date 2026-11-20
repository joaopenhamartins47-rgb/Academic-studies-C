#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Estrutura de dados para hash e arquivo

//hash
struct caixa
{
    int chave, pos;
    struct caixa *prox;
}; typedef struct caixa Caixa;


//Arquivo
struct Tpreg
{
    int codigo;
    char nome[100];
    char status;
};typedef struct Tpreg tpreg;

//Para inserir no arquivo usando hashing, precisarei de 4 funcoes auxiliares:

//1 - A hash pra definir em qual posicao ela devera ser inserida

//2 - Insere ordenado, que insere o dado ordenado na posicao do hash

//3 - Inicializar o vetor de ponteiros

//4 - Busca indexada no hash

#define N 4

void init_vet(Caixa *vet[N])
{
    int i;
    for(i=0;i<N;i++)
        vet[i] = NULL;
}

int hash(int cod)
{
    return cod%N;
}

Caixa *criaCaixa(int cod, int registro)
{
    Caixa *novo = (Caixa*)malloc(sizeof(Caixa));
    novo->chave = cod;
    novo->pos = registro;
    novo->prox = NULL;

    return novo;
}

void insere_ordenado(Caixa **inicio, int cod, int registro)
{
    Caixa *aux = *inicio;
    Caixa *ant = NULL;
    Caixa *novo = criaCaixa(cod, registro);
    if(!aux || cod < aux->chave)
    {
        novo->prox = *inicio;
        *inicio = novo;
    }
    else
    {
        ant = aux;
        aux = aux->prox;
        while(aux && aux->chave < cod)
        {
            ant = aux;
            aux = aux->prox;
        }

        ant->prox = novo;
        novo->prox = aux;
    }
}

Caixa* busca_indexada(Caixa *inicio, int cod)
{
    while(inicio && inicio->chave != cod)
        inicio = inicio->prox;

    return inicio;
}

//Funcao para inserir a caixa utilizando hashing no arquivo

void insere_hash(tpreg reg, Caixa *T[N])
{
    int end;
    FILE *Ptrarq = fopen("arqHash.dat", "ab");

    end = hash(reg.codigo);
    if(busca_indexada(T[end], reg.codigo))
        printf("Chave ja existe!\n");
    else
    {
        fwrite(&reg, sizeof(tpreg), 1, Ptrarq);
        insere_ordenado(&T[end], reg.codigo, ftell(Ptrarq)/sizeof(tpreg)-1); // -1 pq ele ta um a frente, por causa do fwrite
    }
    fclose(Ptrarq);
}

//-------------------------------------------------------------------------------------------------------
//Insere hash utilizando o elo, que eh o registro pai que deve apontar para a area de extensao (overflow)

//Vou precisar de uma funcao que inicializa todos os registros no arq de tamanho n com codigo zero

struct Tphash
{
    int codigo, status, elo;
    char nome[50];
};typedef struct Tphash tphash;

void init_arq()
{
    FILE *Ptrarq = fopen("arqHash.dat", "wb");

    tphash reg;
    reg.codigo = 0;
    strcpy(reg.nome, "");
    reg.status = 0;
    reg.elo = 0;
    int i;
    for(i = 0; i<N; i++)
    {
        fwrite(&reg, sizeof(tphash), 1, Ptrarq);
    }
    fclose(Ptrarq);
}

//Tambem vou precisar de uma funcao busca_hash, que precura na posicao do arq se tem aquele codigo, atraves dos elos enquanto for diferente de 0

void busca_hash(FILE *Ptrarq, int end, int cod, int *achou)
{
    int terminou = 0;
    *achou = 0;
    tphash reg;
    fseek(Ptrarq, end*sizeof(tphash), 0);
    fread(&reg, sizeof(tphash), 1, Ptrarq);
    while(!feof(Ptrarq) && !terminou)
    {
        if(reg.codigo != cod)
        {
            if(reg.elo == 0)
                terminou = 1;
            else
            {
                fseek(Ptrarq, reg.elo*sizeof(tphash), 0);
                fread(&reg, sizeof(tphash), 1, Ptrarq);
            }
        }
        else
        {
            terminou = 1;
            *achou = 1;
        }
    }
}


//Nessa funcao as informacoes do registro ja vou ter por parametro, so vou precisar fazer essas verificacoes e atualizar o registro do pai











int main(void)
{
    return 0;
}