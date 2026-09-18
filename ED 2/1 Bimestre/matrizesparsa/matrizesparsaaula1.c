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

//a) inicializar uma matriz esparsa;
void init_matriz(MatEsp * vetlin[], MatEsp *vetcol[])
{
    int i, j;
    for(i=0;i<NL;i++)
        vetlin[i] = NULL;

    for(j=0;j<NC;j++)
        vetcol[j] = NULL;
}

//inserir um determinado elemento na posição i, j;
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
                vetcol[col] = nova;
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


//excluir um elemento da posição i, j;
void excluir_elemento(MatEsp *vetlin[], MatEsp *vetcol[], int lin, int col)
{
    //Exclui na posicao horizontal e depois da vertical
    MatEsp *exclui, *aux, *ant;
    int achou=0;
    if(vetlin[lin] && vetcol[col])
    {
        if(vetlin[lin]->col == col)
        {
            exclui = vetlin[lin];
            vetlin[lin] = vetlin[lin]->pl;
            achou = 1;
        }
        else
        {
            //Faz a procura
            ant = vetlin[lin], aux = vetlin[lin]->pl;
            while(aux && aux->col < col)
            {
                ant = aux;
                aux = aux->pl;
            }
            if(aux && col == aux->col)
            {
                ant->pl = aux->pl;
                exclui = aux;
                achou = 1;
            }
        }
    }
    
    
    if(achou)
    {
        if(vetcol[col] && vetcol[col]->lin == lin)
        {
            vetcol[col] = vetcol[col]->pc;
        }
        else
        {
            //Faz a procura
            ant = vetcol[col], aux = vetcol[col]->pc;
            while(aux && aux->lin < lin)
            {
                ant = aux;
                aux = aux->pc;
            }
            if(aux && lin == aux->lin)
            {
                ant->pc = aux->pc;
            }
        }
        free(exclui);
    }
    else
        printf("Elemento nao encontrado!\n");
    
}

//exibir uma matriz esparsa
void exibir_matriz(MatEsp *vetlin[])
{
    int i, j;
    MatEsp *aux;
    for(i=0; i<NL; i++)
    {
        j=0;
        aux = vetlin[i];
        while(j<NC)
        {
            if(aux && aux->col == j)
            {
                printf("%d ", aux->valor);
                aux = aux->pl;
            }
            else
                printf("0 ");
            j++;
        }
        printf("\n");
    }
}

//somar duas matrizes esparsas e gerar uma terceira;
void somar_matrizes(MatEsp *vetlin[], MatEsp *vetcol[], MatEsp *vetlin2[], MatEsp *vetcol2[], MatEsp *vetlin3[], MatEsp *vetcol3[])
{
    //Pra somar 2 matrizes elas precisam ser de tamanhos iguais
    MatEsp *aux, *aux2;
    init_matriz(vetlin3, vetcol3);
    int j, i, resultado;
    //Como to usando constantes, nao precisa verificar se sao iguais
    for(i=0; i<NL;i++)
    {
        j=0;
        aux = vetlin[i];
        aux2 = vetlin2[i];
        while((aux || aux2) && j<NC)
        {
            if((aux && aux2) && j == aux->col && j == aux2->col)
            {
                resultado = aux->valor + aux2->valor;
                if(resultado != 0)
                    insere_mat(vetlin3, vetcol3, i, aux->col, resultado);
                aux = aux->pl;
                aux2 = aux2->pl;
            }
            else if(aux && j == aux->col)
            {
                resultado = aux->valor;
                insere_mat(vetlin3, vetcol3, i, aux->col, resultado);
                aux = aux->pl;
            }
            else if(aux2 && j == aux2->col)
            {
                resultado = aux2->valor;
                insere_mat(vetlin3, vetcol3, i, aux2->col, resultado);
                aux2 = aux2->pl;
            }
            j++;
        }
    }
    
}



//fazer a multiplicação de duas matrizes esparsas;

//excluir uma matriz esparsa.
void excluir_matriz(MatEsp *vetlin[], MatEsp *vetcol[])
{
    int i, j;
    MatEsp *aux, *del;
    for(i=0;i<NL;i++)
    {
        j=0;
        aux = vetlin[i];
        while(j<NC)
        {
            if(aux && aux->col == j)
            {
                del = aux;
                if(vetcol[j] && vetcol[j]->lin == aux->lin)
                {
                    vetcol[j] = vetcol[j]->pc;
                }
                aux = aux->pl;
                free(del);
            }
            j++;
        }
        vetlin[i] = NULL;
    }
}



int main(void)
{
    return 0;
}