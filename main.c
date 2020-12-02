#include "header.h"

int main()
{
    // Declaracao de dados:
	TRIE* head = getNewTrieNode();
    IDLIST *list = {NULL};
    GENRELIST *genreList = {NULL};
    HASHLIST *table = malloc(sizeof(HASHLIST) * TABLE_SIZE);
    USERRATING* userList = malloc(sizeof(USERRATING) * 138494);
    ABP* tags = newABP("START");

    // Inicialização do vetor de usuários:
    for (int i = 0; i<138494; i++)
        userList[i].ratingNum = 0;


    // Inicializacao das variaveis de controle de tempo:
    double tempo;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    QueryPerformanceFrequency(&frequency);

    // Leitura dos arquivos + criacao das estruturas de dados:
    printf("Processando dados! Aguarde. ");
    QueryPerformanceCounter(&start);
    leArqMovie(head, table);
    leArqTags(tags);
    leArqRating(table, userList);
    QueryPerformanceCounter(&end);
    tempo = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    printf("Pronto!\n");
    printf("Tempo decorrido: %fs\n\n", tempo);

    // Tratamento do input do usuario:
    char op[10];
    int input;
    char prefix[TITLE_SIZE];

    printf("Entre com um comando:\n\n");
    printf("movie <prefix>\t\t\tProcurar um filme por prefixo\n");
    printf("user <userid>\t\t\tListar filmes avaliados por um usuario\n");
    printf("top10 <genre>\t\t\tListar os 10 melhores filmes de um genero\n");
    printf("tag <'tag1' 'tag2' ...>\t\tProcurar um filme que possui um conjunto de tags\n");
    printf("sair\t\t\t\tterminar o programa\n");


    while (1)
    {
        printf("\n");
        scanf("%s", op);
        gets(prefix);

        if(strcmp(op, "movie") == 0){
            printf("\nFILMES ENCONTRADOS: \n");
            printInfoMovie(prefix+1, head, table);
        }
        else if(strcmp(op, "user") == 0){
            input = atoi(prefix+1);
            printf("\nFILMES ENCONTRADOS: \n");
            printInfoUser(input, userList, table);
        }
        else if(strcmp(op, "tag") == 0){
            printf("\n\n%s\n\n", prefix+1);
            printMoviesWithTags(prefix, table, tags);
        }
        else if(strcmp(op, "top10") == 0)
            printTopMovies(prefix+1, table);
        else if(strcmp(op, "sair") == 0) break;
        else
            printf("COMANDO INVALIDO\n");
    }

    return 0;
}
