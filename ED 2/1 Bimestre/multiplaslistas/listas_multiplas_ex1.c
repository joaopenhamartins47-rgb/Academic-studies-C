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




void dynamic_multiple_lists(editora **cont_ed, autor_info **cont_autor)
{
    FILE *Ptrarq = fopen("livros.dat", "rb");
    if(!Ptrarq)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        content cont_bin;
        editora *aux_ed;
        autor_info *aux_info;
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
            livros *novo_li = criar_livros(cont_bin.paginas, cont_bin.titulo_livro, cont_bin.ano);
            if(!aux_ed->pLivros)
                aux_ed->pLivros = novo_li;
            else
            {
                
                livros *aux_li = aux_ed->pLivros;
                while(aux_li->prox != NULL)
                aux_li = aux_li->prox;      
            
                aux_li->prox = novo_li;
                novo_li->ant = aux_li;
                 
            }
            char sobrenome[35], nome[35];
            int j, k, i=0;
            while(cont_bin.autores[i] != '\0')
            {
                j=0;
                k=0;
                if(cont_bin.autores[i] == ' ')
                    i++;
                while(cont_bin.autores[i] != ',')
                {
                    sobrenome[j] = cont_bin.autores[i];
                    j++;
                    i++;
                }
                i++; //Pra pular a , e nao deixar copiar pro nome
                if(cont_bin.autores[i] == ' ')
                    i++;
                while(cont_bin.autores[i] != ';' && cont_bin.autores[i] != '\0')
                {
                    nome[k] = cont_bin.autores[i];
                    k++;
                    i++;
                }
                sobrenome[j] = '\0';
                nome[k] = '\0';
                aux_info = Busca_autor(*cont_autor, nome, sobrenome);
                if(!aux_info) //Se nao tem, cria e insere na lista
                {
                    autor_info *novo_info = criar_autor(nome, sobrenome);
                    if(!*cont_autor)
                        *cont_autor = novo_info;
                    else
                    {
                        autor_info *and_info=*cont_autor;
                        while(and_info->prox != NULL)
                            and_info = and_info->prox;
                        and_info->prox = novo_info;
                    }
                    aux_info = novo_info;
                }
                //Agora cria o pautor para apontar para o autor com as informacoes
                autor *novo_au = criar_ponteiro_autor();
                
                autor *lista_au = novo_li->pListaAutor;
                if(!novo_li->pListaAutor)
                    novo_li->pListaAutor = novo_au;
                else
                {
                    autor *and_au = lista_au;
                    while(and_au->prox != NULL)
                        and_au = and_au->prox;
                    and_au->prox = novo_au;
                }
                novo_au->pAutor = aux_info;  
                if(cont_bin.autores[i] == ';')
                    i++;       
            }
        }
    }
}

//3 - Exclusao de um livro do arq binario e da lista dinamica

void Exclusao_livro(char titulo[], editora **inicio)
{
    FILE *Ptrarq = fopen("livros.dat", "rb");
    if(!Ptrarq)
        printf("Erro ao abrir arquivo!\n");
    else
    {
        content conteudo;
        fread(&conteudo, sizeof(content), 1, Ptrarq);
        while(!feof(Ptrarq) && strcmp(titulo, conteudo.titulo_livro) != 0)
            fread(&conteudo, sizeof(content), 1, Ptrarq);

        if(!feof(Ptrarq)) //Significa que achou
        {
            //Exclusao do arq binario primeiro
            FILE *Temp = fopen("temp.dat", "wb");
            fseek(Ptrarq, 0, 0);
            fread(&conteudo, sizeof(content), 1, Ptrarq);
            while(!feof(Ptrarq))
            {
                if(strcmp(titulo, conteudo.titulo_livro) != 0)
                    fwrite(&conteudo, sizeof(content), 1, Temp);
                fread(&conteudo, sizeof(content), 1, Ptrarq);
            }
            fclose(Ptrarq);
            fclose(Temp);
            remove("livros.dat");
            rename("temp.dat", "livros.dat");
            

            //Agora, exclusao da lista dinamica

            //Percorre as editoras
            editora *aux = *inicio;
            livros *procura = NULL;
            int parada = 0;
            while(aux != NULL && !parada)
            {
                procura = aux->pLivros;
                while(procura != NULL && strcmp(procura->titulo, titulo) != 0)
                    procura = procura->prox;
                if(procura != NULL)
                    parada = 1;
                else
                    aux = aux->prox;
            }
                

            if(!aux)
                printf("Livro nao encontrado na lista dinamica! \n");
            else
            {

                //Exclui de dentro pra fora, entao primeiro é o pAutor
                autor *aux_au = procura->pListaAutor;
                while(aux_au != NULL)
                {
                    autor *remover = aux_au;
                    aux_au = aux_au->prox;
                    free(remover);
                }
                //Agora remove o livro
                if(!procura->ant) //Se ele for o primeiro
                {
                    aux->pLivros = procura->prox;
                    if(procura->prox != NULL)
                        procura->prox->ant = NULL;
                }
                    
                
                else{ //Entre 2
                    procura->ant->prox = procura->prox;
                    if(procura->prox != NULL)
                        procura->prox->ant = procura->ant;
                }
                free(procura);
               
            }   
        }
        else
            printf("Titulo do livro nao encontrado! \n");
    }

}




int main(void)
{
    
    return 0;
}
