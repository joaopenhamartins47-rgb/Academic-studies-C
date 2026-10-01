#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct reg_lista
{
    struct listagen *cabeca;
    struct listagen *cauda;
};

union info_lista
{
    char info[8];
    struct reg_lista lista;
};

struct listagen
{
    char terminal;
    union info_lista no;
};typedef struct listagen Listagen;


char nulo(Listagen *L)
{
    return L == NULL;
}

char atomo(Listagen *L)
{
    return !nulo(L) && L->terminal;
}

Listagen *head(Listagen *L)
{
    if(nulo(L)||atomo(L))
    {
        printf("O argumento deve ser uma lista nao vazia\n");
        return NULL;
    }
    else
        return L->no.lista.cabeca;
}

Listagen *tail(Listagen *L)
{
    if(nulo(L)||atomo(L))
    {
        printf("O argumento deve ser uma lista nao vazia\n");
        return NULL;
    }
    else
        return L->no.lista.cauda;
}

Listagen *criat(char info[])
{
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    strcpy(novo->no.info, info);
    novo->terminal = 1;
    return novo;
}

Listagen *cons(Listagen *H, Listagen *T)
{
    if(atomo(T))
    {
        printf("O segundo argumento nao pode ser atomo!\n");
        return NULL;
    }
    Listagen *novo = (Listagen*)malloc(sizeof(Listagen));
    novo->terminal = 0;
    novo->no.lista.cabeca = H;
    novo->no.lista.cauda = T;
    return novo;
}


struct pilhap
{
    struct pilhap *cabeca;
    Listagen *info;
};typedef struct pilhap pilha;


char vazia(pilha *p)
{
    return p == NULL;
}
void push(pilha **p, Listagen *info)
{
    //Primeiro, cria a caixinha
    pilha *novo = (pilha*)malloc(sizeof(pilha));
    novo->info = info;
    novo->cabeca = NULL;
    if(!*p)
    {
        *p = novo;
    }
    else
    {
        novo->cabeca = *p;
        *p = novo;
    }
}

void pop(pilha **p, Listagen **removido)
{
    pilha *aux;
    aux = *p;
    *removido = (*p)->info;
    *p = (*p)->cabeca;
    free(aux);
}

void init_p(pilha **p)
{
    *p = NULL;
}

struct filap
{
    struct filap *prox;
    Listagen *info;
};typedef struct filap fila;



void enqueue(fila **f, Listagen *dado)
{
    fila *novo = (fila*)malloc(sizeof(fila));

    novo->info = dado;
    novo->prox = NULL;

    if (*f == NULL)
    {
        *f = novo;
    }
    else
    {
        fila *aux = *f;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
}

void dequeue(fila **f, Listagen **removido)
{
    fila *aux;

    if (*f == NULL)
    {
        *removido = NULL;
    }
    else
    {
        aux = *f;

        *removido = (*f)->info;

        *f = aux->prox;

        free(aux);
    }
}


char isEmpty(fila *f)
{
    return f == NULL;
}

void init(fila **f)
{
    *f = NULL;
}


//Exercicio para inserir um determinado elemento ordenado na lista em que eh informado a profundidade da mesma

/*Ideias:
Para esse exercicio eu vou utilizar uma fila por conta do controle de profundidade e toda vez que achar uma sublista, aumenta a prof e verifica se tem aquele atomo naquela linha
antes de tudo vou precisar de uma funcao auxiliar pra verificar se tem aquele atomo naquela linha, que sera chamada dentro da funcao principal, assim como a funcao de inserir ordenado
*/



char verifica_linha(Listagen *L, char at[])
{
    int achou = 0;
    while(L && !achou)
    {
        if(!nulo(head(L)) && atomo(head(L)))
        {
            if(strcmp(L->no.lista.cabeca->no.info, at) == 0)
                achou = 1;
        }
        L = tail(L);
    }
    if(achou)
        return 1;
    return 0;
}


void inserir_ordenado_linha(Listagen **L, char at[], Listagen *info) //Aqui eu posso estar mudando pra onde o ponteiro do lista pai esta apontando, por isso **
{
    Listagen *aux = (*L)->no.lista.cabeca;
    Listagen *ant = NULL;
    int achou = 0;
    if(!nulo(head(aux)) && atomo(head(aux)) && strcmp(aux->no.info, at) > 0) //Primeiro caso de insercao
    {
        info->no.lista.cauda = aux;
        (*L)->no.lista.cabeca = info;
    }
    else //Ai procura pra achar onde inserir
    {
        while(aux && !achou)
        {
            if(!nulo(head(aux)) && atomo(head(aux)))
            {
                if(strcmp(aux->no.info, at) > 0)
                {
                    achou = 1;
                }
            }
            if(!achou)
            {
                ant = aux;
                aux = tail(aux);
            }
        }
        ant->no.lista.cauda = info;
        info->no.lista.cauda = aux;
        info->no.lista.cabeca = criat(at);
    }
}


void insere(Listagen **L, char info[], int prof)
{
    fila *f, *f2, *qt;
    int qtde=0, achou;
    init(&f);
    init(&f2);
    Listagen *aux = *L;
    int prof_atual=1;
    enqueue(&f, aux);
    enqueue(&f2, aux);
    while(prof_atual < prof)
    {
        qt = f;
        while(qt)
        {
            qtde++;
            qt = qt->prox;
        }
        while(qtde > 0)
        {
            dequeue(&f2, &aux);
            dequeue(&f, &aux);
            while(aux)
            {
                if(!nulo(head(aux)) && !atomo(head(aux)))
                {
                    enqueue(&f, head(aux));
                    enqueue(&f2, aux);
                }
                aux = tail(aux);
            }
            qtde--;
        }
        prof_atual++;
    }
    
    while(!isEmpty(f2))
    {
        dequeue(&f2, &aux);
        achou = verifica_linha(head(aux), info);
        if(!achou)
        {
            Listagen *novo = cons(NULL, NULL);
            inserir_ordenado_linha(&aux, info, novo);
        }
    }
}


//Exercicio: Excluir todos os atomos que contenham a mensagem passada por parametro, alinhando os ponteiros da lista pai e sublistas quando necessario

/*
Ideias: Eu so vou precisar alterar o ponteiro da lista pai quando o atomo da cabeca da primeira lista dele for o elemento que eu quero excluir, senao a alteracao eh feita na propria sublista

Vou utilizar a abordagem de percorrer com pilha guardando o e o tail sempre que for sublista e percorrendo com aux = head(L)
*/


//Cadeia de cabecas (cada sublista com 1 elemento) que termina no atomo procurado
char libera_exclusao(Listagen *L, char at[])
{
    Listagen *cabecas = L;
    while(!nulo(head(cabecas)) && !atomo(head(cabecas)) && nulo(tail(head(cabecas))))
        cabecas = head(cabecas);
    if(!nulo(head(cabecas)) && atomo(head(cabecas)) && strcmp(head(cabecas)->no.info, at) == 0)
        return 1;
    return 0;
}

//Ajusta o ponteiro certo: ant se existir, senao o pai, senao o proprio L
void religa(Listagen **L, Listagen *pai, Listagen *ant, Listagen *prox)
{
    if(ant)
        ant->no.lista.cauda = prox;
    else if(pai)
        pai->no.lista.cabeca = prox;
    else
        *L = prox;
}

void exclui_lista_atomo(Listagen *L)
{
    Listagen *aux = L;
    pilha *p;
    init_p(&p);
    while(aux && !atomo(aux)) //Desce pelas cabecas ate o atomo
    {
        push(&p, aux);
        aux = head(aux);
    }
    if(aux)
        push(&p, aux); //Empilha o no atomo tambem
    while(!vazia(p))
    {
        pop(&p, &aux);
        free(aux);
    }
}

void excluir_atomos(Listagen **L, char at[])
{
    pilha *p, *p2;
    Listagen *aux, *ant, *pai, *prox;
    init_p(&p);
    init_p(&p2);
    push(&p, *L);
    push(&p2, NULL); //Lista do primeiro nivel nao tem pai
    while(!vazia(p))
    {
        pop(&p, &aux);
        pop(&p2, &pai);
        ant = NULL;
        while(aux)
        {
            if(libera_exclusao(aux, at))
            {
                prox = tail(aux);
                religa(L, pai, ant, prox);
                exclui_lista_atomo(aux);
                aux = prox; //ant nao muda
            }
            else
            {
                if(!nulo(head(aux)) && !atomo(head(aux)))
                {
                    push(&p, head(aux)); //Sublista pra processar depois
                    push(&p2, aux);      //Dono dela eh o pai
                }
                ant = aux;
                aux = tail(aux);
            }
        }
    }
}


//Exercicio: Exclusao de uma matriz esparsa dado um range em string (ex: D2J5) Listas encadeadas para representar linhas e colunas, fazer toda a exclusao realizando as operacoes certas de ponteiros e listas encadeadas

struct MatrizEsparsa
{
    int lin;
    char col;
    struct MatrizEsparsa *pc, *pl;
};typedef struct MatrizEsparsa Matesp;

struct Descritor
{
    struct Linha *plinha;
    struct Coluna *pcoluna;
};typedef struct Descritor desc;

struct Coluna
{
    char info;
    struct MatrizEsparsa *primC;
    struct Coluna *prox;
};typedef struct Coluna coluna;

struct Linha
{
    int info;
    struct MatrizEsparsa *primA;
    struct Linha *prox;
};typedef struct Linha linha;

void excluir_range(desc **planilha, char range[])
{
    char ini, fim;
    int lin_ini, lin_fim;
    int entrou;

    ini = range[0];
    fim = range[2];

    lin_ini = atoi(&range[1]); // OU lin_ini = range[1] - '0';
    lin_fim = atoi(&range[3]);


    

    linha *auxl = (*planilha)->plinha, *antl = NULL;
    coluna *auxc = (*planilha)->pcoluna, *antc = NULL;

    linha *remover_l;
    coluna *remover_col;



    while(auxl && auxl->info < lin_ini)
    {
        antl = auxl;
        auxl = auxl->prox;
    }

    while(auxc && auxc->info < ini)
    {
        antc = auxc;
        auxc = auxc->prox;
    }



    while(auxc && auxc->info <= fim)
    {
        Matesp *caixamat = auxc->primC;
        Matesp *ant_caixa = NULL;
        Matesp *remover;


        entrou = 0;


        // Vou ate a primeira caixa da coluna que esteja dentro das linhas que quero excluir.

        while(caixamat && caixamat->lin < lin_ini)
        {
            ant_caixa = caixamat;
            caixamat = caixamat->pc;
            entrou = 1;
        }


        while(caixamat && caixamat->lin <= lin_fim)
        {
            remover = caixamat;

            caixamat = caixamat->pc;


            if(!entrou)
            {
                auxc->primC = caixamat;
            }
            else
            {
                ant_caixa->pc = caixamat;
            }
        }



        if(!auxc->primC)
        {
            remover_col = auxc;
            auxc = auxc->prox;



            if(!antc)
            {
                (*planilha)->pcoluna = auxc;
            }
            else
            {
                antc->prox = auxc;
            }

            free(remover_col);
        }
        else
        {
            antc = auxc;
            auxc = auxc->prox;
        }
    }

    while(auxl && auxl->info <= lin_fim)
    {
        entrou = 0;

        Matesp *caixamat = auxl->primA;
        Matesp *ant_caixa = NULL;
        Matesp *remover;

        while(caixamat && caixamat->col < ini)
        {
            ant_caixa = caixamat;
            caixamat = caixamat->pl;
            entrou = 1;
        }


        while(caixamat && caixamat->col <= fim)
        {
            remover = caixamat;

            caixamat = caixamat->pl;


            if(!entrou)
            {
                auxl->primA = caixamat;
            }
            else
            {
                ant_caixa->pl = caixamat;
            }
            free(remover);
        }

        if(!auxl->primA) //Remove a linha
        {
            remover_l = auxl;
            auxl = auxl->prox;

            if(!antl)
            {
                (*planilha)->plinha = auxl;
            }
            else
            {
                antl->prox = auxl;
            }

            free(remover_l);
        }
        else
        {
            antl = auxl;
            auxl = auxl->prox;
        }
    }
}


//Fixacao, 4 jeitos de se percorrer uma listagen, podemos usar: 1 - recursividade, 2 - Pilha, 3 - Fila, 4 - Misto Fila com variavel ou pilha com variavel

//Recursivo conta quantas vezes o elemento apareceu
int contar_lista(Listagen *L, int *cont, char info[])
{
    if(!nulo(L))
    {
        if(atomo(L))
        {
            if(strcmp(L->no.info, info) == 0)
                (*cont)++;
        }
        else
        {
            contar_lista(head(L), cont, info);
            contar_lista(tail(L), cont, info);
        }
    }
}


// 2. Pilha pura (empilha o tail, desce no head, pop quando acaba): refaça o 1a (contar ocorrências), sem recursão.

int conta_lista_pilha(Listagen *L, char info[])
{
    pilha *p;
    int cont=0;
    init_p(&p);
    push(&p, L);
    while(!vazia(p))
    {
        pop(&p, &L);
        if(!nulo(head(L)) && !atomo(head(L)))
        {
            if(!nulo(tail(L)))
                push(&p, tail(L));
            push(&p, head(L));
        }
        else if(!nulo(head(L)) && atomo(head(L)))
        {
            if(strcmp(L->no.lista.cabeca->no.info, info) == 0)
                cont++;
            if(!nulo(tail(L)))
                push(&p, tail(L));
        }
    }
}

// 3. Pilha mista retornar a lista que aponta para o atomo junto com o nivel de profundidade dele
struct Lista
{
    Listagen *info;
    int prof;
};typedef struct Lista lista;

Listagen* verificar_prof(Listagen *L, char at[])
{
    int achou = 0;
    int prof=1, primeiro=0;
    pilha *p;
    init_p(&p);
    push(&p, L);
    lista *novo;
    while(!vazia(p))
    {
        if(!primeiro)
        {
            primeiro = 1;
            pop(&p, &L);
        }
        else
        {
            pop(&p, &L);
            prof--;
        }

        while(L && !achou)
        {
            if(!nulo(head(L)) && atomo(head(L)))
            {
                if(strcmp(L->no.lista.cabeca->no.info, at) == 0)
                {
                    novo = (lista*)malloc(sizeof(lista));
                    novo->info = L;
                    novo->prof = prof;
                    achou = 1;
                }
                L = tail(L);
            }
            else if(!nulo(head(L)) && !atomo(head(L)))
            {
                push(&p, tail(L));
                L = head(L);
                prof++;
            }
        }
    }
    if(achou)
        return novo;
    return NULL;
}


int main(void)
{


    return 0;
}