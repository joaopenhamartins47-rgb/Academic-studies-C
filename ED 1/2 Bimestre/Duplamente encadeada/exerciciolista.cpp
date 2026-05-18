#include <stdio.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>

char menu(void)
{
    printf("[A] - Inserir ordenado\n");
    printf("[B] - Exclusao de um determinado elemento\n");
    return toupper(getche());
}

//Estrutura de dados
struct Tpno
{
    char info[10];
    Tpno *ant, *prox;
};

//Criar caixinha
Tpno *criar_caixinha(char dado[])
{
    Tpno *novo;
    novo = new Tpno;
    strcpy(novo->info, dado);
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

Tpno *Inserir_ordenado(Tpno *L)
{
    char elemento[10];
    Tpno *novo;
    fflush(stdin);
    gets(elemento);
    while(strcmp(elemento, "") != 0)
    {
        novo = criar_caixinha(elemento);
        
        if(L == NULL) //Insere o primeiro elemento (1)
            L = novo;
        else
        {
            if(strcmp(elemento, L->info) < 0) //Insere no inicio (2)
            {
                novo->prox = L;
                L->ant = novo;
                L = novo;
            }
            else
            {
                Tpno *andador = L;
                //anda procurando o lugar ideal
                while(andador->prox != NULL && strcmp(elemento, andador->info) > 0)
                    andador = andador->prox;

                if(andador->prox == NULL && strcmp(elemento, andador->info) > 0) //Insere no final (3)
                {
                    novo->ant = andador;
                    andador->prox = novo;
                }
                else //Insere no meio (4)
                {
                    novo->prox = andador;
                    novo->ant = andador->ant;
                    andador->ant->prox = novo;
                    andador->ant = novo;
                }
            }
        }
        fflush(stdin);
        gets(elemento);
    }
    return L;
}

Tpno *Excluir_elemento(Tpno *L)
{
    char elemento[10];
    fflush(stdin);
    gets(elemento);
    while(strcmp(elemento, "\0") != 0)
    {
        Tpno *andador = L;
        if(L == NULL)
        {
            printf("Lista vazia!");
            strcpy(elemento, "\0");
        }
        else
        {
            while(andador != NULL && strcmp(elemento, andador->info) != 0)
                andador = andador->prox;
            if(andador != NULL) //Significa que achou
            {
                if(andador == L) //Remove no comeco (1)
                {
                    L = andador->prox;
                    if(L != NULL)
                        L->ant = NULL;
                    andador->prox = NULL;
                    andador->ant = NULL;
                    delete andador;
                }
                else if(andador->prox == NULL) //Remove no final (2)
                {
                    andador->ant->prox = NULL;
                    andador->ant = NULL;
                    delete andador;
                }
                else
                {
                    andador->ant->prox = andador->prox;
                    andador->prox->ant = andador->ant;
                    andador->prox = NULL;
                    andador->ant = NULL;
                    delete andador;
                }
            }
            else
                printf("Elemento nao encontrado! \n");
            fflush(stdin);
            gets(elemento);
        }
            
    }
    return L;
}



int main(void)
{
    char op;
    op = menu();
    Tpno *lista = NULL;
    do
    {
        switch (op)
        {
        case 'A':
            lista = Inserir_ordenado(lista);
            break;
        case 'B':
            lista = Excluir_elemento(lista);
            break;
        
        default:
            break;
        }
    } while (op != 27);
    
    
    return 0;
}