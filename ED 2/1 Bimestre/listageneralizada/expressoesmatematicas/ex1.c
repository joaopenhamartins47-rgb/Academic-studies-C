#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
1:) Faça um algoritmo para resolver uma expressão matemática utilizando uma lista generalizada
(diferente do modelo de aula!). A partir de uma string (char [ ]) passada por parâmetro, o
algoritmo deverá:
a) Construir uma lista generalizada segundo as prioridades.
b) Após a lista ter sido construída, o algoritmo deverá resolver a expressão “podando” os nodos da
lista generalizada até sobrar um único nodo com o resultado, cujo valor deverá ser retornado. À
medida que cada operação vai sendo resolvida, os nodos da lista generalizada devem ser
removidos e deverá sobrar apenas um nodo com o resultado. O nodo da lista deverá ser construído
com o uso de union, uma vez que poderá ter um valor (float), um operador (char) ou uma função
(pow, sqrt, sin e cos).
Obs: Você pode usar Pilha e Fila conforme foi aprendido em aula sem a necessidade de
implementação, apenas use as funções de forma correta, com seus devidos nomes e parâmetros!
*/

//Construir a listagen de acordo com as prioridades

union valores
{
    float valorF;
    char operador;
    char funcao[8];
};

struct ListaGen
{
    struct ListaGen *cabeca;
    struct ListaGen *cauda;
    union valores no;
    char terminal;
};typedef struct ListaGen Listagen;

struct pilhap
{
    Listagen *info;
    struct pilhap *cabeca;
};typedef struct pilhap pilha;


void init_pilha(pilha **p)
{
    *p = NULL;
}

char isEmpty(pilha *p)
{
    return p == NULL;
}

void push(pilha **p, Listagen *x)
{
    pilha *novo;

    novo = (pilha *) malloc(sizeof(pilha));

    novo->info = x;
    novo->cabeca = *p;

    *p = novo;
}

void pop(pilha **p, Listagen **x)
{
    pilha *aux;

    if(*p != NULL)
    {
        aux = *p;

        *x = aux->info;

        *p = aux->cabeca;
        free(aux);
    }
}

Listagen* criaNoF(float valor)
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    novo->no.valorF = valor;
    novo->cabeca = NULL;
    novo->cauda = NULL;
    novo->terminal = 'V';
    return novo;
}

Listagen* criaNoO(char op)
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    novo->no.operador = op;
    novo->cabeca = NULL;
    novo->cauda = NULL;
    novo->terminal = 'O';
    return novo;
}

Listagen* criaNoFuncao(char funcao[])
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    strcpy(novo->no.funcao, funcao);
    novo->cabeca = NULL;
    novo->cauda = NULL;
    novo->terminal = 'F';
    return novo;
}

struct Caixa
{
    char termo[20];
    struct caixa *prox;
};typedef struct Caixa caixa;


caixa *separa(char exp[])
{
    caixa *inicio = NULL, *fim = NULL, *novo;
    char termo[20];
    int i, j;

    i = 0;

    while(exp[i] != '\0')
    {
        j = 0;

        if(exp[i] == ' ')
        {
            i++;
        }
        else if((exp[i] >= '0' && exp[i] <= '9') || exp[i] == '.')
        {
            while((exp[i] >= '0' && exp[i] <= '9') || exp[i] == '.')
            {
                termo[j] = exp[i];
                j++;
                i++;
            }

            termo[j] = '\0';

            novo = (caixa *)malloc(sizeof(caixa));
            strcpy(novo->termo, termo);
            novo->prox = NULL;

            if(inicio == NULL)
            {
                inicio = novo;
                fim = novo;
            }
            else
            {
                fim->prox = novo;
                fim = novo;
            }
        }
        else if((exp[i] >= 'a' && exp[i] <= 'z') ||
                (exp[i] >= 'A' && exp[i] <= 'Z'))
        {
            while((exp[i] >= 'a' && exp[i] <= 'z') ||
                  (exp[i] >= 'A' && exp[i] <= 'Z'))
            {
                termo[j] = exp[i];
                j++;
                i++;
            }

            termo[j] = '\0';

            novo = (caixa *)malloc(sizeof(caixa));
            strcpy(novo->termo, termo);
            novo->prox = NULL;

            if(inicio == NULL)
            {
                inicio = novo;
                fim = novo;
            }
            else
            {
                fim->prox = novo;
                fim = novo;
            }
        }
        else
        {
            termo[0] = exp[i];
            termo[1] = '\0';

            novo = (caixa *)malloc(sizeof(caixa));
            strcpy(novo->termo, termo);
            novo->prox = NULL;

            if(inicio == NULL)
            {
                inicio = novo;
                fim = novo;
            }
            else
            {
                fim->prox = novo;
                fim = novo;
            }

            i++;
        }
    }

    return inicio;
}


char tipo(caixa *lista)
{
    int i;

    i = 0;

    if(lista->termo[0] >= '0' && lista->termo[0] <= '9')
        return 'V';

    if(lista->termo[0] == '+' || lista->termo[0] == '-' ||
       lista->termo[0] == '*' || lista->termo[0] == '/')
        return 'O';

    return 'F';
}

float resolve_funcao(Listagen *func)
{
    Listagen *arg, *virgula, *arg2;
    float a, b, resultado;

    arg = func->cauda->cabeca;

    if(strcmp(func->no.funcao, "pow") == 0)
    {
        virgula = arg;

        while(virgula != NULL && virgula->no.operador != ',')
            virgula = virgula->cauda;

        arg2 = virgula->cauda;

        a = resolve_linha(arg);
        b = resolve_linha(arg2);

        resultado = pow(a, b);
    }
    else if(strcmp(func->no.funcao, "sqrt") == 0)
    {
        a = resolve_linha(arg);
        resultado = sqrt(a);
    }
    else if(strcmp(func->no.funcao, "sin") == 0)
    {
        a = resolve_linha(arg);
        resultado = sin(a);
    }
    else if(strcmp(func->no.funcao, "cos") == 0)
    {
        a = resolve_linha(arg);
        resultado = cos(a);
    }

    return resultado;
}

void construir_listagen(char exp[])
{
    Listagen *L = NULL, *atual;
    pilha *p1, *p2;
    caixa *lista = separa(exp);
    init(&p1); init(&p2);
    int i;
    char t;
    float num=0;
    while(lista != NULL)
    {
        if(!L)
        {
            t = tipo(lista);
            if(t == 'V')
            {
                float valor = atof(lista->termo);
                L = atual = criaNoF(valor);
            }
            else if(t == 'O')
            {
                char valor = lista->termo[0];
                L = atual = criaNoO(valor);
            }
            else
            {
                L = atual = criaNoFuncao(lista->termo);
            }
            push(&p2, L);
            lista = lista->prox;

        }
        else
        {
            if(strcmp(lista->termo, "(") == 0)
            {
                //Ai cria uma nova caixa com valor 0, faz o atual apontar pra ele e cria uma caixa embaixo com o proximo termo
                atual->cauda = criaNoF(0);
                atual = tail(atual);
                push(&p1, atual);
                push(&p2, atual);
                lista = lista->prox;
                t = tipo(lista);
                if(t == 'V')
                {
                    float valor = atof(lista->termo);
                    atual->cabeca = criaNoF(valor);
                }
                else if(t == 'O')
                {
                    char valor = lista->termo[0];
                    atual->cabeca = criaNoO(valor);
                }
                else
                {
                    atual->cabeca = criaNoFuncao(lista->termo);
                }
                atual = head(atual);
                lista = lista->prox;
            }
            else
            {
                if(strcmp(lista->termo, ")") == 0)
                {
                    pop(&p1, &atual);
                }
                else
                {
                    t = tipo(lista);
                    if(t == 'V')
                    {
                        float valor = atof(lista->termo);
                        atual->cauda = criaNoF(valor);
                    }
                    else if(t == 'O')
                    {
                        char valor = lista->termo[0];
                        atual->cauda = criaNoO(valor);
                    }
                    else
                    {
                        atual->cauda = criaNoFuncao(lista->termo);
                    }
                    atual = tail(atual);
                }
                lista = lista->prox;
            }

        }
    }
    while(!isEmpty(p2))
    {
        pop(&p2, &atual);

        if(atual->terminal == 'F')
        {
            atual->no.valorF = resolve_funcao(atual);
            atual->terminal = 'V';
        }
        else
        {
            atual->no.valorF = resolve_linha(atual);
            atual->terminal = 'V';
        }
    }
}

float resolve_linha(Listagen *L)
{
    Listagen *ant, *op, *dir;
    float resultado;

    ant = NULL;
    op = L;

    while(op != NULL)
    {
        if(op->terminal == 'O' &&
           (op->no.operador == '*' || op->no.operador == '/'))
        {
            dir = op->cauda;

            if(op->no.operador == '*')
                resultado = ant->no.valorF * dir->no.valorF;
            else
                resultado = ant->no.valorF / dir->no.valorF;

            ant->no.valorF = resultado;
            ant->terminal = 'V';
            ant->cauda = dir->cauda;

            free(op);
            free(dir);

            op = ant->cauda;
        }
        else
        {
            ant = op;
            op = op->cauda;
        }
    }

    /* resolve depois + e - */
    ant = NULL;
    op = L;

    while(op != NULL)
    {
        if(op->terminal == 'O' &&
           (op->no.operador == '+' || op->no.operador == '-'))
        {
            dir = op->cauda;

            if(op->no.operador == '+')
                resultado = ant->no.valorF + dir->no.valorF;
            else
                resultado = ant->no.valorF - dir->no.valorF;

            ant->no.valorF = resultado;
            ant->terminal = 'V';
            ant->cauda = dir->cauda;

            free(op);
            free(dir);

            op = ant->cauda;
        }
        else
        {
            ant = op;
            op = op->cauda;
        }
    }

    return L->no.valorF;
}

int main(void)
{
    return 0;
}