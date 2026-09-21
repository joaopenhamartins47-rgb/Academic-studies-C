#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Coluna
{
    int cod;
    struct Coluna *primC, *prox;
};typedef struct Coluna coluna;

struct Linha
{
    int ano;
    struct Linha *primA, *prox;
};typedef struct Linha linha;

struct Arq_binario
{
    int cod, ano;
    char nome[20], data[20];
};typedef struct arq_bin;

//Vou fazer tudo em uma funcao so pra simular a prova
void gerar_matrizesparsa(void)
{
    
}




int main(void)
{
    return 0;
}
