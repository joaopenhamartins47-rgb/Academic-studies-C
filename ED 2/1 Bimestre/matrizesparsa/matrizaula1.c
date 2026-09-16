#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NL 5
#define NC 6

struct matrizEsp
{
    int lin, col, valor;
    struct matrizEsp *pc, *pl;
};typedef struct matrizEsp MatEsp;

void verifica_ocupado(MatEsp *inicio, int col, MatEsp **aux)
{
    while(inicio != NULL && col > inicio->col)
        inicio = inicio->pl;

    if(inicio && col == inicio->col)
        *aux = inicio;
    else
        *aux = NULL;
}


void insere_mat(MatEsp* vetlin[], MatEsp* vetcol[], int lin, int col, int valor)
{
    MatEsp *nova, *ant, *aux;

    if(lin >= 0 && lin < NL && col >= 0 && col < NC) //Verificacao pra ver se a linha e a coluna informada sao validas
    {
        verifica_ocupado(vetlin[lin], col, &aux);
        if(aux)
            aux->valor = valor;
        else
        {
            //Se nao tiver uma matriz naquela posicao ainda, cria e insere
            nova = (MatEsp*)malloc(sizeof(MatEsp));
            nova->lin = lin;
            nova->col = col;
            nova->valor = valor;

            //Ligacao horizontal primeiro 3 casos
            if(!vetlin[lin])
            {
                vetlin[lin] = nova;
                nova->pl = NULL;
            }
            else
            {
                if(col < vetlin[lin]->col)
                {
                    nova->pl = vetlin[lin];
                    vetlin[lin] = nova;
                }
                else
                {
                    ant = vetlin[lin];
                    aux = vetlin[lin]->pl;
                    while(aux && col > aux->col)
                    {
                        ant = aux;
                        aux = aux->pl;
                    }
                    ant->pl = nova;
                    nova->pl = aux;
                }
            }
            //Insercao vertical
            if(!vetcol[col])
            {
                vetlin[col] = nova;
                nova->pc = NULL;
            }
            else
            {
                if(lin < vetcol[col]->lin)
                {
                    nova->pc = vetcol[col];
                    vetcol[col] = nova;
                }
                else
                {
                    ant = vetcol[col];
                    aux = vetcol[col]->pc;
                    while(aux && lin > aux->lin)
                    {
                        ant = aux;
                        aux = aux->pc;
                    }
                    ant->pc = nova;
                    nova->pc = aux;
                }
            }

        }
    }
}

void exibe_mat(MatEsp *vetlin[])
{
    int i, j;
    MatEsp *aux;

    for(i = 0; i < NL; i++)
    {
        j = 0;
        aux = vetlin[i];

        while(j < NC)
        {
            if(aux && j == aux->col)
            {
                printf("%d ", aux->valor);
                aux = aux->pl;
            }
            else
            {
                printf("0 ");
            }

            j++;
        }

        printf("\n");
    }
}



int main(void)
{
    return 0;
}