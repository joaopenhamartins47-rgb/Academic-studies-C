
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Coluna
{
    int cod;
    struct Coluna *prox;
    struct Matriz_esparsa *primC;
};typedef struct Coluna coluna;

struct Linha
{
    int ano;
    struct Matriz_esparsa *primA;
    struct Linha *prox;
};typedef struct Linha linha;

struct Arq_binario
{
    int cod, ano;
    char nome[30], data[10];
};typedef struct Arq_binario arq_bin;

struct Matriz_esparsa
{
    int lin, col, qtde;
    struct Matriz_esparsa *pc, *pl;
};typedef struct Matriz_esparsa MatEsp;

//Vou fazer tudo em uma funcao so pra simular a prova
void gerar_matrizesparsa(coluna **pCliente, linha **pAnos)
{
    coluna *novo, *aux, *ant;
    linha *nova_lin, *aux_l, *ant_l;

    *pCliente = NULL;
    *pAnos = NULL;
    MatEsp *caixa;
    arq_bin dados;
    FILE *Ptrarq = fopen("aluguel.dat", "rb");
    if(Ptrarq == NULL)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        while(!feof(Ptrarq))
        {
            fread(&dados, sizeof(arq_bin), 1, Ptrarq);

            if(!*pCliente && !*pAnos)// Se for o primeiro elemento
            {
                //Cria a linha e a coluna
                novo = (coluna*)malloc(sizeof(coluna));
                nova_lin = (linha*)malloc(sizeof(linha));
                novo->cod = dados.cod;
                novo->primC = novo->prox = NULL;
                nova_lin->ano = dados.ano;
                nova_lin->primA = nova_lin->prox = NULL;
                *pCliente = novo;
                *pAnos = nova_lin;

                //Cria a caixa da matriz esparsa
                caixa = (MatEsp*)malloc(sizeof(MatEsp));
                caixa->pc = caixa->pl = NULL;
                caixa->col = novo->cod;
                caixa->lin = nova_lin->ano;
                caixa->qtde = 1;

                (*pCliente)->primC = caixa;
                (*pAnos)->primA = caixa;
            }
            else
            {
                //Se ja tiver, procura na coluna se ja tem com aquele dado
                aux = *pCliente;
                ant = NULL;
                while(aux != NULL && dados.cod != aux->cod)
                {
                    ant = aux;
                    aux = aux->prox;
                }
                

                //Depois procura a linha
                aux_l = *pAnos;
                ant_l = NULL;
                while(aux_l && dados.ano != aux_l->ano)
                {
                    ant_l = aux_l;
                    aux_l = aux_l->prox;
                }

                //Se ja tiver algum dos dois, so aumenta a quantidade
                if(aux && aux_l)
                {
                    MatEsp *percorrer = aux->primC;
                    while(percorrer && percorrer->lin != dados.ano)
                        percorrer = percorrer->pc;
                    if(percorrer)
                        percorrer->qtde = percorrer->qtde+1;  
                }
                else if(!aux && !aux_l)
                {
                    //Insere ordenado
                    coluna *novo = (coluna*)malloc(sizeof(coluna));
                    novo->cod = dados.cod;
                    aux = *pCliente;
                    ant = NULL;
                    while(aux && dados.cod > aux->cod)
                    {
                        ant = aux;
                        aux = aux->prox;
                    }
                    if(ant == NULL) //Primeiro caso de insercao
                    {
                        novo->prox = *pCliente;
                        *pCliente = novo;
                    }
                    else
                    {
                        ant->prox = novo;
                        novo->prox = aux;
                    }
                    //Insere a linha ordenada
                    nova_lin = (linha*)malloc(sizeof(linha));
                    nova_lin->ano = dados.ano;
                    aux_l = *pAnos;
                    ant_l = NULL;
                    while(aux_l && dados.ano > aux_l->ano)
                    {
                        ant_l = aux_l;
                        aux_l = aux_l->prox;
                    }
                    if(ant_l == NULL) //Primeiro caso de insercao
                    {
                        nova_lin->prox = *pAnos;
                        *pAnos = nova_lin;
                    }
                    else
                    {
                        ant_l->prox = nova_lin;
                        nova_lin->prox = aux_l;
                    }
                    caixa = (MatEsp*)malloc(sizeof(MatEsp));
                    caixa->pc = caixa->pl = NULL;
                    caixa->col = novo->cod;
                    caixa->lin = nova_lin->ano;
                    caixa->qtde = caixa->qtde+1;
                    nova_lin->primA = caixa;
                    novo->primC = caixa;
                }
                else if(!aux_l)
                {
                    //Insere ordenado na linha e faz as conexoes na coluna
                    nova_lin = (linha*)malloc(sizeof(linha));
                    nova_lin->ano = dados.ano;
                    aux_l = *pAnos;
                    ant_l = NULL;
                    while(aux_l && dados.ano > aux_l->ano)
                    {
                        ant_l = aux_l;
                        aux_l = aux_l->prox;
                    }
                    if(ant_l == NULL) //Primeiro caso de insercao
                    {
                        nova_lin->prox = *pAnos;
                        *pAnos = nova_lin;
                    }
                    else
                    {
                        ant_l->prox = nova_lin;
                        nova_lin->prox = aux_l;
                    }
                    caixa = (MatEsp*)malloc(sizeof(MatEsp));
                    caixa->pc = caixa->pl = NULL;
                    caixa->col = aux->cod;
                    caixa->lin = nova_lin->ano;
                    caixa->qtde = caixa->qtde+1;

                    nova_lin->primA = caixa;

                    MatEsp *aux_es = aux->primC;
                    MatEsp *ant_es = NULL;
                    while(aux_es && dados.ano > aux_es->lin)
                    {
                        ant_es = aux_es;
                        aux_es = aux_es->pc;
                    }
                    if(ant_es == NULL)
                    {
                        caixa->pc = aux->primC;
                        aux->primC = caixa;
                    }
                    else
                    {
                        ant_es->pc = caixa;
                        caixa->pc = aux_es;
                    }
                }
                else if(!aux)
                {
                    //Insere a coluna ordenado e faz a procura na linha
                    coluna *novo = (coluna*)malloc(sizeof(coluna));
                    novo->cod = dados.cod;
                    aux = *pCliente;
                    ant = NULL;
                    while(aux && dados.cod > aux->cod)
                    {
                        ant = aux;
                        aux = aux->prox;
                    }
                    if(ant == NULL) //Primeiro caso de insercao
                    {
                        novo->prox = *pCliente;
                        *pCliente = novo;
                    }
                    else
                    {
                        ant->prox = novo;
                        novo->prox = aux;
                    }
                    caixa = (MatEsp*)malloc(sizeof(MatEsp));
                    caixa->pc = caixa->pl = NULL;
                    caixa->col = novo->cod;
                    caixa->lin = aux_l->ano;
                    caixa->qtde++;

                    novo->primC = caixa;
                    //Faz a procura pra atualizar os ponteiros na linha
                    MatEsp *aux_es = aux_l->primA;
                    MatEsp *ant_es = NULL;
                    while(aux_es && dados.cod > aux_es->col)
                    {
                        ant_es = aux_es;
                        aux_es = aux_es->pl;
                    }
                    if(ant_es == NULL)
                    {
                        caixa->pl = aux_l->primA;
                        aux_l->primA = caixa;
                    }
                    else
                    {
                        ant_es->pl = caixa;
                        caixa->pl = aux_es;
                    }
                }
            }
        }
        fclose(Ptrarq);
    }
}




int main(void)
{
    return 0;
}
