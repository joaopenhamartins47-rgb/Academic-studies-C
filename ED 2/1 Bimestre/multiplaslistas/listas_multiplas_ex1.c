#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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


struct informacoes_autor
{
    char sobrenome[50], nome[50];
    struct informacoes_autor *prox;
};typedef struct informacoes_autor autor_info; 

struct autor_dinamico
{
    struct autor_dinamico *prox;  
    autor_info *pAutor; 
};typedef struct autor_dinamico autor;

struct livros_dinamico
{
    char titulo[200];
    int paginas, ano;
    struct livros_dinamico *ant, *prox;
    autor *pListaAutor;

};typedef struct livros_dinamico livros;

struct editora_dinamico
{
    char nome[50];
    struct editora_dinamico *prox;
    livros *pLivros;

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

void init(editora **ed_inicio, livros **li_inicio, autor **p_inicio, autor_info **aut_inicio)
{
    *ed_inicio = *li_inicio = *p_inicio = *aut_inicio = NULL;
}

autor_info *Busca_autor(autor_info *lista, char nome[], char sobrenome[])
{
    autor_info *aux = lista;
    while(aux != NULL && !(strcmp(aux->nome, nome) == 0 && strcmp(aux->sobrenome, sobrenome) == 0))
        aux = aux->prox;
    
    return aux;
}

editora *Busca_editora(editora *lista, char nome[])
{
    editora *aux = lista;
    while(aux != NULL && strcmp(aux->nome, nome) != 0)
        aux = aux->prox;
    return aux;
}


editora *criar_editora(char nome[])
{
    editora *novo = (editora*)malloc(sizeof(editora));
    novo->prox = NULL;
    novo->pLivros = NULL;
    strcpy(novo->nome, nome);
    return novo;
}

livros *criar_livros(int paginas, char titulo[], int ano)
{
    livros *novo = (livros*)malloc(sizeof(livros));
    novo->prox = NULL;
    novo->ant = NULL;
    novo->pListaAutor = NULL;
    novo->paginas = paginas;
    novo->ano = ano;
    strcpy(novo->titulo, titulo);
    return novo;
}

autor *criar_ponteiro_autor(void)
{
    autor *novo = (autor*)malloc(sizeof(autor));
    novo->pAutor = NULL;
    novo->prox = NULL;
    return novo;
}

autor_info *criar_autor(char nome[], char sobrenome[])
{
    autor_info *novo = (autor_info *)malloc(sizeof(autor_info));
    novo->prox = NULL;
    strcpy(novo->nome, nome);
    strcpy(novo->sobrenome, sobrenome);
    return novo;
}



void dynamic_multiple_lists(editora **cont_ed, livros **cont_li, autor **cont_pon, autor_info **cont_autor)
{
    FILE *Ptrarq = fopen("livros.dat", "rb");
    if(!Ptrarq)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        content cont_bin;
        editora *aux_ed = *cont_ed;
        livros *aux_li = *cont_li;
        autor *aux_au = *cont_pon;
        while(!feof(Ptrarq))
        {
            fread(&cont_bin, sizeof(content), 1, Ptrarq);
            aux_ed = Busca_editora(*cont_ed, cont_bin.editora);
            if(!aux_ed)
            {
                editora *novo = criar_editora(cont_bin.editora);

                if(!*cont_ed) //Primeiro elemento
                    *cont_ed = novo;
                
                else
                {
                    editora *andador = *cont_ed;
                    while(andador->prox != NULL)
                        andador = andador->prox;
                    andador->prox = novo;
                }
                aux_ed = novo;
            }
            aux_li = criar_livros(cont_bin.paginas, cont_bin.titulo_livro, cont_bin.ano);
            if(!aux_ed->pLivros)
                aux_ed->pLivros = aux_li;
            else
            {
                livros *and_li = aux_ed->pLivros;
                while(and_li->prox != NULL)
                    and_li = and_li->prox;      
                
                and_li->prox = aux_li;
                aux_li->ant = and_li;
            }
        }
    }
}




int main(void)
{
    
    return 0;
}
