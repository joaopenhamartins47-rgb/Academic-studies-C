#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parser_comando(char entrada[], char *comando)
{
    int i;
    for(i=0;entrada[i] != ' ';i++)
    {
        comando[i] = entrada[i];
    }
    comando[i] = '\0';
    return i;
}

char isSELECT(char comando[])
{
    return !strcmp(comando, "SELECT") || !strcmp(comando, "select");
}

char isUPDATE(char comando[])
{
    return !strcmp(comando, "UPDATE") || !strcmp(comando, "update");
}

char isDELETE(char comando[])
{
    return !strcmp(comando, "DELETE") || !strcmp(comando, "delete");
}

char isCREATE(char comando[])
{
    return !strcmp(comando, "CREATE") || !strcmp(comando, "create");
}

char isALTER(char comando[])
{
    return !strcmp(comando, "ALTER") || !strcmp(comando, "alter");
}

void parser_select(char entrada[], int i, char colunas[10][20], int *num_colunas, char tabela[], char condicao[50])
{
    int col = 0;   /* 0=colunas 1=pula FROM 2=tabela 3=verifica WHERE 4=le condicao 5=fim */
    int nc = 0;
    int j = 0;

    condicao[0] = '\0';   /* garante vazio se nao tiver WHERE */

    while(entrada[i] != '\0')
    {
        if(col == 0)
        {
            while(entrada[i] == ' ')
                i++;
            while(entrada[i] != ' ' && entrada[i] != ',' && entrada[i] != '\0')
            {
                colunas[nc][j] = entrada[i];
                j++;
                i++;
            }
            colunas[nc][j] = '\0';

            if(entrada[i] == ',')
            {
                nc++;
                j = 0;
                i++;
                while(entrada[i] == ' ')
                    i++;
            }
            else if(entrada[i] == ' ')
            {
                nc++;
                col = 1;
                i++;
            }
        }
        else if(col == 1)
        {
            while(entrada[i] == ' ')
                i++;
            while(entrada[i] != ' ' && entrada[i] != '\0') // pula a palavra FROM 
                i++;   
            while(entrada[i] == ' ')
                i++;
            col = 2;
            j = 0;
        }
        else if(col == 2)
        {
            while(entrada[i] != ' ' && entrada[i] != ';' && entrada[i] != '\0')
            {
                tabela[j] = entrada[i];
                j++;
                i++;
            }
            tabela[j] = '\0';
            col = 3;
        }
        else if(col == 3)
        {
            while(entrada[i] == ' ')
                i++;

            if(entrada[i] == 'W' || entrada[i] == 'w')
            {
                while(entrada[i] != ' ' && entrada[i] != '\0') // pula a palavra WHERE 
                    i++;   
                while(entrada[i] == ' ')
                    i++;
                j = 0;
                col = 4;
            }
            else
            {
                col = 5;
            }
        }
        else if(col == 4)
        {
            while(entrada[i] != ';' && entrada[i] != '\0')
            {
                condicao[j] = entrada[i];
                j++;
                i++;
            }
            condicao[j] = '\0';
            col = 5;
        }
        else
        {
            i++;
        }
    }

    *num_colunas = nc;
}




int main(void)
{
    int i, num_colunas, k;
    char comando[30], colunas[10][20], tabela[20], condicao[30];
    i = parser_comando("UPDATE INTO * FROM MOVIES", comando);
    parser_select("SELECT col1,col2 FROM tabela WHERE id=3", i, colunas, &num_colunas, tabela, condicao);
    
    printf("Comando: %s\n", comando);

    printf("Colunas (%d):\n", num_colunas);
    for(k = 0; k < num_colunas; k++)
        printf("  [%d] %s\n", k, colunas[k]);

    printf("Tabela: %s\n", tabela);
    printf("Condicao: %s\n", condicao);
    return 0;
}