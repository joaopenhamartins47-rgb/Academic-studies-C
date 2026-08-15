#include <stdio.h>
#include <stdlib.h>


/*
1) Função para importar os dados do arquivo texto “livros.txt” e gravar no arquivo binário
“livros.dat”. Arquivo de Livros contendo os campos: “autores”, “titulo_livro”, “editora”,
“ano” e “paginas”.
*/

struct Conteudo
{
    char autores[200], titulo_livro[200], editora[50];
    int ano, paginas;
};typedef struct Conteudo content;


struct autor_info
{
    char sobrenome[50], nome[50];
    struct autor_info *prox;
};

struct autor_dinamico
{
    struct autor_dinamico *prox;  
    struct autor_info *pAutor; 
};typedef struct autor_dinamico autor;

struct livros_dinamico
{
    char titulo[200];
    int paginas, ano;
    struct livros_dinamico *ant, *prox;
    struct autor *pListaAutor;

};typedef struct livros_dinamico livros;

struct editora_dinamico
{
    char editora[50];
    struct editora_dinamico *prox;
    struct livros *pLivros;

};typedef struct editora_dinamico editora;

void print_arq(void)
{
    FILE *Ptrarq = fopen("livros.txt", "r");
    if (Ptrarq == NULL)
        printf("Erro ao abrir arquivo! \n");
    else
    {
        content aux;
        while(!feof(Ptrarq))
        {
            fscanf(Ptrarq, "%[^|]|%[^|]|%[^|]|%d|%d\n", aux.autores, aux.titulo_livro, aux.editora, &aux.ano, &aux.paginas);
            printf("%s\t, %s\t, %s\t, %d\t, %d\t\n", aux.autores, aux.titulo_livro, aux.editora, aux.ano, aux.paginas);
        }
        fclose(Ptrarq);
    }
}

void record_txt_to_bin(void)
{
    FILE *Ptrarq = fopen("livros.txt", "r");
    if (Ptrarq == NULL)
        printf("Erro ao abrir arquivo! \n");
    else
    {
        FILE *Ptrarq_bin = fopen("livros.dat", "wb");
        content aux;
        while(!feof(Ptrarq))
        {
            fscanf(Ptrarq, "%[^|]|%[^|]|%[^|]|%d|%d\n", aux.autores, aux.titulo_livro, aux.editora, &aux.ano, &aux.paginas);
            fwrite(&aux, sizeof(aux), 1, Ptrarq_bin);
        }
        fclose(Ptrarq);
        fclose(Ptrarq_bin);
    }
}

void print_arq_bin(void)
{
    FILE *Ptrarq = fopen("livros.dat", "rb");
    if(Ptrarq == NULL)
        printf("Erro ao abrir arquivo! \n");
    else
    {
        content aux;
        while(!feof(Ptrarq))
        {
            fread(&aux, sizeof(aux), 1, Ptrarq);
            printf("%s\t, %s\t, %s\t, %d\t, %d\t\n", aux.autores, aux.titulo_livro, aux.editora, aux.ano, aux.paginas);
        }
        fclose(Ptrarq);
    }
}





int main(void)
{
    
    return 0;
}
