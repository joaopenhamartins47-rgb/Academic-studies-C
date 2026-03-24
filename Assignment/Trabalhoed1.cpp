#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <conio.h>


#include "filatrab.h"

/*simule e exiba a execução de tarefas solicitadas a um “processador”. As tarefas que este pode executar são:

    Impressão à 3 ut;
    Gravação em dispositivo interno à 5 ut;
    Leitura à 4 ut;
    Gravação em dispositivo externo à 8 ut.

    Observacoes:

    Construir um arquivo texto com, no mínimo, 1000 registros de solicitações de tarefas;
    Definir, no início da simulação, a quantidade de processadores que serão utilizados;
    Ut = Unidades de tempo;
    A cada 4 ut uma tarefa é solicitada, mas esse tempo pode ser alterado durante a execução da simulação;

    As prioridades para execução das tarefas são:
    [1º] Gravação em dispositivo interno;
    [2º] Gravação em dispositivo externo;
    [3º] Leitura;
    [4º] Impressão.

    Desenvolver uma interface intuitiva e “amigável” para entendimento do que “está acontecendo”;
    As tarefas executadas, após o tempo determinado, deverão deixar a Fila;
    Qual o tempo médio que cada processador, em ut’s, dispende para atender uma      tarefa?
    Qual o tempo médio, que se leva, para atender cada tipo de tarefa?
    Quantos processos, cada processador executou?
*/

void geraraleatorio(void)
{
    int i, op;
    FILE *Ptrarq = fopen("tarefas.txt", "w");
    for(i = 0; i<1000; i++)
    {
        op = rand()%4+1;
        switch (op)
        {
        case 1:
            fprintf(Ptrarq, "G\n");
            break;
        case 2:
            fprintf(Ptrarq, "E\n");
            break;
        case 3:
            fprintf(Ptrarq, "L\n");
            break;
        case 4:
            fprintf(Ptrarq, "I\n");
            break;
        }
    }
    fclose(Ptrarq);
}

void simulacao(fila &f, tarefa &taref)
{
    int n, tempo=0, intervalo=4, valid = 0;
    FILE *Ptrarq = fopen("tarefas.txt", "r");
    printf("Digite a quantidade de processadores \n");
    scanf("%d", &n);
    processador core[n];
    
    if(Ptrarq == NULL)
        printf("Erro ao abrir arquivo! \n");
    else
    {
        inicializa(f);
        for(int i = 0; i < n; i++) //Inicializa todos os processadores
        {
            core[i].ocupado = 0;
            core[i].tarefas_executadas = 0;
        }
        while(!(feof(Ptrarq) &&  !valid))
        {
            if(tempo % intervalo == 0 && tempo != 0 && !feof(Ptrarq))
            {
                fscanf(Ptrarq, " %c", &taref.tipo);
                switch (taref.tipo)
                {
                case 'G':
                    taref.prioridade = 1;
                    taref.tempo_total = 5;
                    break;
                case 'E':
                    taref.prioridade = 2;
                    taref.tempo_total = 8;
                    break;
                case 'L':
                    taref.prioridade = 3;
                    taref.tempo_total = 4;
                    break;
                case 'I':
                    taref.prioridade = 4;
                    taref.tempo_total = 3;
                    break;   
                }

            
                if(!filacheia(f.fim))
                {
                    taref.tempo_chegada = tempo;
                    taref.tempo_restante = taref.tempo_total;
                    inserir(f, taref);
                }
                else
                    printf("Fila cheia! \n");

            }
            valid = 0;
            for(int i=0; i<n; i++) //Atualizacao dos processadores
            {
                if(!core[i].ocupado && !filavazia(f.fim))
                {
                    core[i].atual = remover(f);
                    core[i].ocupado = 1;
                    printf("Processador %d recebeu a tarefa\n", i);
                }
                if(core[i].ocupado)
                { 
                    core[i].atual.tempo_restante--;
                    valid = 1;
                    if(core[i].atual.tempo_restante == 0)
                    {
                        core[i].ocupado = 0;
                        core[i].tarefas_executadas++;
                        printf("Processador %d terminou a tarefa\n", i);
                    }
                    
                }
            }
            if(tempo % 20 == 0)
                intervalo = 1;
            if(tempo % 50 == 0)
                intervalo = 5;
            printf("%d\n", tempo);
            Sleep(10); 
            tempo++;
        }   
    }
}
 

int main(void)
{
    fila f;
    tarefa taref;
    srand(time(NULL));
    geraraleatorio();
    printf("Arquivo gerado! \n");
    simulacao(f, taref);


    return 0;
}
