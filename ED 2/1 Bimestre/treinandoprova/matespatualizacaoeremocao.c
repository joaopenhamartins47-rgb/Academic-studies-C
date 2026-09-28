#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Implemente:

void atualizar_matriz(MatEsp *vetlin[NL], MatEsp *vetcol[NC]);

A função deve percorrer todas as células existentes da matriz e realizar as seguintes operações:

Se o valor da célula for par, adicionar 10 ao valor.
Se o valor da célula for ímpar, subtrair 5 do valor.
Após a atualização, caso o valor seja menor ou igual a 5, a célula deverá ser excluída da matriz.
A exclusão deve manter corretamente os encadeamentos das linhas e das colunas, atualizando:
pl do elemento anterior e seguinte;
pc do elemento anterior e seguinte;
vetlin, quando a célula removida for a primeira de uma linha;
vetcol, quando a célula removida for a primeira de uma coluna.
A célula removida deve ser liberada com free.
*/

#define NC 5
#define NL 6

struct matrizEsp
{
    int lin, col, valor;
    struct matrizEsp *pc, *pl;
};typedef struct matrizEsp MatEsp;

void atualizar_matriz(MatEsp *vetlin[NL], MatEsp *vetcol[NC])
{
    int i, j=0;
    MatEsp *aux_l, *aux_c, *ant, *atual;
    MatEsp *ex_l;
    int excluiu;
    for(i=0; i<NL; i++)
    {
        aux_l = vetlin[i];

        for(j=0; j<NC && aux_l != NULL;j++)
        {
            int excluiu=0;
            if(aux_l->col == j)
            {
                if(aux_l->valor % 2 == 0)
                {
                    aux_l->valor += 10;
                }
                else
                    aux_l->valor -= 5;
                
                if(aux_l->valor <= 5)
                {
                    //Exclusao da linha primeiro
                    ex_l = aux_l;
                    if(aux_l == vetlin[i]) //Primeiro caso de remocao
                    {
                        vetlin[i] = aux_l->pl;
                        aux_l = aux_l->pl;
                    }
                    else
                    {
                        //Procura o anterior, atual e liga os nos
                        ant = NULL;
                        atual = vetlin[i];
                        while(atual && atual->col != aux_l->col)
                        {
                            ant = atual;
                            atual = atual->pl;
                        }
                        ant->pl = atual->pl;
                    }
                    //Exclusao da coluna agora
                    aux_c = vetcol[j];
                    if(ex_l == aux_c)
                    {
                        vetcol[j] = aux_c->pc;
                        aux_c = aux_c->pc;
                    }
                    else
                    {
                        //Procura o anterior, atual e liga os nos
                        ant = NULL;
                        atual = vetcol[j];
                        while(atual && atual->lin != ex_l->lin)
                        {
                            ant = atual;
                            atual = atual->pc;
                        }
                        ant->pc = atual->pc;
                    }
                    aux_l = ex_l->pl;

                    free(ex_l);
                    excluiu = 1;
                }
                if(!excluiu)
                    aux_l = aux_l->pl;
            }

        }
    }
}



int main(void)
{
    return 0;
}