#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define TF 6
#define K 2

struct kdtree
{
	int ponto[K];
	struct kdtree *esq,*dir;
};
typedef struct kdtree KdTree;

KdTree *CriaNo(int ponto[K])
{
	int i;
	KdTree *no=(KdTree*)malloc(sizeof(KdTree));
	for(i=0; i<K; i++)
		no->ponto[i] = ponto[i];	
	no->esq = no->dir = NULL;
	return no;
}

void insereR(KdTree **raiz, int ponto[K], int n)
{
	int d;
	if (*raiz==NULL)
		*raiz=Cria_no(ponto);
	else
	{
		d=n%K;
		if (ponto[d] < (*raiz)->ponto[d])
			insereR(&(*raiz)->esq, ponto, n+1);
		else
			insereR(&(*raiz)->dir, ponto, n+1);
	}
}


void ordenaPontos(int pontos[TF][K],int ini,int fim,int d)
{
	int i,j,aux;
    char flag = 1;
	while(fim>ini && flag)
	{
		flag = 0;
		for(i=ini; i<fim; i++)
			if(pontos[i][d] > pontos[i+1][d])
			{
				for(j=0; j<K; j++)
				{
					aux = pontos[i][j];
					pontos[i][j] = pontos[i+1][j];
					pontos[i+1][j] = aux;
				}
				flag = 1;
			}
		fim--;
	}
}

void insereBalanceado(KdTree **raiz,int pontos[TF][K],int ini,int fim,int n)
{
	int d,meio;
	if(ini<=fim)
	{
		d=n%K;
		meio=(ini+fim)/2;
		ordenaPontos(pontos,ini,fim,d);
		*raiz=CriaNo(pontos[meio]);	
		insereBalanceado(&(*raiz)->esq,pontos,ini,meio-1,n+1);
		insereBalanceado(&(*raiz)->dir,pontos,meio+1,fim,n+1);
	}
}

float distancia(int pontoA[K],int pontoB[K])
{
	float soma=0;
	int i;
	for(i=0; i<K; i++)
		soma = soma + pow(pontoA[i] - pontoB[i],2);	
	return sqrt(soma);
}

void buscaPonto(KdTree *raiz,int pbusca[K],int raio)
{
	if(raiz!=NULL)
	{
		if(distancia(raiz->ponto,pbusca)<=raio)	
			printf("(%d,%d)\n",raiz->ponto[0],raiz->ponto[1]);
		buscaPonto(raiz->esq,pbusca,raio);	
		buscaPonto(raiz->dir,pbusca,raio);	
	}
}



//Exercicios para treinar kdtree e fixar sua regra de execucao

/*
A função deve retornar 1 se o ponto existir e 0 caso contrário.
- Considere o ponto encontrado somente quando todas as coordenadas forem iguais.
- Escolha o próximo filho pela dimensão do nível atual.
- Faça sem recursão.
*/
int buscaExata(KdTree *raiz, int ponto[K])
{
	int d, n = 0, i, achou=0, cont=0;
	while(raiz && !achou)
	{
		d = n%K;
		if(ponto[d] != raiz->ponto[d])
		{
			if(ponto[d] < raiz->ponto[d])
				raiz = raiz->esq;
			else if(ponto[d] > raiz->ponto[d])
				raiz = raiz->dir;
		}
		else
		{
			cont = 0;
			for(i = 0; i<K; i++)
			{
				if(ponto[i] == raiz->ponto[i])
					cont++;
			}
			if(cont == K)
				achou = 1;
			else
				raiz = raiz->dir;
			
		}
		n+=1;
		
	}
	return achou;
}



int main()
{
	int pontos[TF][K]={{30,40},{5,25},{10,12},{70,70},{50,30},{35,45}};
	KdTree *raiz=NULL;
	int i;
	int pbusca[K] = {32,42};
	
	insereBalanceado(&raiz,pontos,0,TF-1,0);
	
	buscaPonto(raiz,pbusca,22);
	
}


