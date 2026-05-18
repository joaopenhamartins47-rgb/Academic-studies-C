#include <stdio.h>
#include <conio2.h>
#include <ctype.h>
#include <string.h>

char menu(void)
{
    printf("[A] - Inserir ordenado\n");
    printf("[B] - Exclusao de um determinado elemento\n");
    printf("[C] - Exibir \n");
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
                    if(andador->ant != NULL)           // guarda contra andador == L, se repetido
                        andador->ant->prox = novo;
                    else
                        L = novo;                      // novo vira o head
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

//Varredura da lista (crescente)
void varredura_crescente(Tpno *L)
{
    if(L == NULL)
        printf("Nao ha elementos para exibir! \n");
    else
    {
        //Considering that our dynamic list is already sorted in ascending order
        while(L != NULL)
        {
            printf(" %s -> ", L->info);
            L = L->prox;
        }
        printf("\n");
    }
}

//Varredura da lista (decrescente)
void varredura_decrescente(Tpno *L)
{
    if(L == NULL)
        printf("Nao ha elementos para exibir! \n");
    else
    {
        Tpno *andador = L;
        while(andador->prox != NULL) //Para no ultimo
            andador = andador->prox;
        while(andador != NULL)
        {
            printf(" %s -> ", andador->info);
            andador = andador->ant;
        }
        printf("\n");
    }
}

/*
4 - Considere listas implementadas por encadeamento duplo, então pede-se para implementar funções que:

a. Localize/ Pesquise/Encontre (search) elementos;
b. Intercalar (Merge) duas listas ordenadas com apenas um laço de repetição;
c. Dividir uma lista em várias (‘k’ listas);
d. Copiar uma lista;
e. Ordenar (sort) uma lista em ordem crescente/decrescente.
*/

//4 a.



int main(void)
{
    char op;
    Tpno *lista = NULL;
    do
    {
        op = menu();
        switch (op)
        {
        case 'A':
            lista = Inserir_ordenado(lista);
            break;
        case 'B':
            lista = Excluir_elemento(lista);
            break;
        case 'C':
            char op2;
            printf("[1] - Display in ascending order \n");
            printf("[2] - Display in descending order \n");
            op2 = getche();
            if(op2 == '1')
                varredura_crescente(lista);
            else
                varredura_decrescente(lista);
            break;
        case 'D':
            break;
        
        default:
            break;
        }
    } while (op != 27);
    
    
    return 0;
}