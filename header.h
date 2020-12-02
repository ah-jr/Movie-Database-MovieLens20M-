// ///////////////////////////////////////////////////////////////////////////////////////
//                                      TRABALHO FINAL                                  //
// ///////////////////////////////////////////////////////////////////////////////////////
//  Nome do Arquivo:    header.h;                                                       //
//  Objetivo:           Organizar estruturas e funcoes em um arquivo.                   //
//  Autoria:            Airton Hoch Junior                                              //
//                      Laura Cardenas Grippa                                           //
// ///////////////////////////////////////////////////////////////////////////////////////

// BIBLIOTECAS  //////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sys\timeb.h>

// DEFINICOSES   //////////////////////////////////////////////////////////////////////////

#define CHAR_SIZE 129
#define TITLE_SIZE 1000
#define GENRE_SIZE 30
#define TABLE_SIZE 5000
#define TAG_SIZE 10000
#define RATING_MAX 1000
#define MOVIE_MAX 10000

//  ESTRUTURAS DE DADOS /////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------------------
//  Tipo:   Lista Encadeada
//  Nome:   LIST
//  Campos: ID          (inteiro)
//          *next       (IDLIST)
typedef struct idList
{
	int ID;
	float rating;
	struct idList *next;
} IDLIST;
// ---------------------------------------------------------------------------------------
//  Tipo:   Arvore Trie
//  Nome:   TRIE
//  Campos: isLeaf         (inteiro)
//          movieID        (inteiro)
//          *character[ ]  (TRIE)
typedef struct trie
{
	int isLeaf;
	int movieID;
	struct trie *character[CHAR_SIZE];
} TRIE;
// ---------------------------------------------------------------------------------------
//  Tipo:   Lista Encadeada
//  Nome:   GENRELIST
//  Campos: genre[ ]       (char)
//          *next          (GERNELIST)
typedef struct genreList
{
	char genre[GENRE_SIZE];
	struct genreList *next;
} GENRELIST;
// ---------------------------------------------------------------------------------------
//  Tipo:   Lista Encadeada
//  Nome:   HASHLIST
//  Campos: title[ ]        (char)
//          movieID         (int)
//          *genrelist      (GERNELIST)
//          ratingAvg       (float)
//          ratingQnt       (int)
//          *next           (HASHLIST)
typedef struct hashlist
{
	char title[TITLE_SIZE];
	int movieID;
	GENRELIST *genreList;
	float ratingAvg;
	int ratingQnt;
	struct hashlist *next;
} HASHLIST;
// ---------------------------------------------------------------------------------------
//  Tipo:   Dupla de Vetores
//  Nome:   USERRATING
//  Campos: movieID[ ]      (int)
//          rating[ ]       (float)
//          ratingNum       (int)
typedef struct userRatings
{
    int movieID[RATING_MAX];
    float rating[RATING_MAX];
    int ratingNum;
}USERRATING;
// ---------------------------------------------------------------------------------------
//  Tipo:   Arvore Binaria de Pesquisa
//  Nome:   ABP
//  Campos: tag[ ]           (char)
//          *movieID         (int)
//          movieNum         (int)
//          *left            (ABP)
//          *right           (ABP)
typedef struct abp
{
    char tag[TAG_SIZE];
    int *movieID;
    int movieNum;
    struct abp *left;
    struct abp *right;
}ABP;
// ---------------------------------------------------------------------------------------

// FUNCOES  //////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------------------------------------------------
int hash(int ID);
//  Nome:       hash;
//  Objetivo:	computa e retorna a função hash.
// ---------------------------------------------------------------------------------------
void insertHashList(HASHLIST **head, char title[], GENRELIST *genreList, float ratingAvg, int ratingQnt, int movieID);
//  Nome:       insertHashList;
//  Objetivo:	insere dados do filme em uma lista hash.
// ---------------------------------------------------------------------------------------
void printHashList(HASHLIST *head);
//  Nome:       printHashList;
//  Objetivo:	imprime a lista hash.
// ---------------------------------------------------------------------------------------
void printHashTable(HASHLIST *table[]);
//  Nome:       printHashTable;
//  Objetivo:	imprime a tabela hash.
// ---------------------------------------------------------------------------------------
void insertHashTable(HASHLIST *table[], char title[], GENRELIST *genreList, float ratingAvg, int ratingQnt, int ID);
//  Nome:       insertHashTable;
//  Objetivo:	insere os dados do filme em uma tabela hash.
// ---------------------------------------------------------------------------------------
HASHLIST *searchHashTable(HASHLIST *table[], int ID);
//  Nome:       searchHashTable;
//  Objetivo:	procura um ID na tabela hash e retorna um ponteiro para o nodo da lista.
// ---------------------------------------------------------------------------------------
IDLIST* createList();
//  Nome:       createList;
//  Objetivo:	cria e retorna uma lista de IDs.
// ---------------------------------------------------------------------------------------
void insertList(IDLIST **head, int ID, float rating);
//  Nome:       insertList;
//  Objetivo:	insere um ID e um rating em uma lista de IDs.
// ---------------------------------------------------------------------------------------
void printList(IDLIST *head);
//  Nome:       printList;
//  Objetivo:	imprime a lista de IDs e ratings.
// ---------------------------------------------------------------------------------------
GENRELIST* createGenreList();
//  Nome:       createGenreList;
//  Objetivo:	cria e retorna uma lista de generos.
// ---------------------------------------------------------------------------------------
void insertGenreList(GENRELIST **head, char genre[]);
//  Nome:       insertGenreList;
//  Objetivo:	insere um genero na lista de generos.
// ---------------------------------------------------------------------------------------
void printGenreList(GENRELIST *head);
//  Nome:       printGenreList;
//  Objetivo:	imprime a lista de generos.
// ---------------------------------------------------------------------------------------
TRIE* getNewTrieNode();
//  Nome:       getNewTrieNode;
//  Objetivo:	cria e retorna um novo nodo de uma arvore trie.
// ---------------------------------------------------------------------------------------
void insert(TRIE *head, char* str, int ID);
//  Nome:       insert;
//  Objetivo:	insere uma palavra em uma arvore trie.
// ---------------------------------------------------------------------------------------
int search(TRIE* head, char* str, IDLIST **list);
//  Nome:       search;
//  Objetivo:	procura uma palavra na arvore trie e retorna 1 se achou e 0 se nao achou.
// ---------------------------------------------------------------------------------------
int haveChildren(TRIE* curr);
//  Nome:       haveChildren;
//  Objetivo:	checa se uma arvore trie tem filhos.
// ---------------------------------------------------------------------------------------
int deletion(TRIE **curr, char* str);
//  Nome:       deletion;
//  Objetivo:	deleta um nodo de uma arvore trie.
// ---------------------------------------------------------------------------------------
int saveIDs(TRIE* head, IDLIST **first);
//  Nome:       saveIDs;
//  Objetivo:	salva todos os IDs contidos em uma arvore trie.
// ---------------------------------------------------------------------------------------
void leArqRating(HASHLIST *table[], USERRATING userList[]);
//  Nome:       leArqRating;
//  Objetivo:	le o arquivo de avaliacoes e salva os dados em uma tabela hash
//				em uma lista de usuarios.
// ---------------------------------------------------------------------------------------
void leArqMovie(TRIE* head, HASHLIST *table[]);
//  Nome:       leArqMovie;
//  Objetivo:	le o arquivo de filmes e salva os dados em uma arvore trie e 
//				uma tabela hash.
// ---------------------------------------------------------------------------------------
void printInfoMovie(char title[], TRIE* head, HASHLIST *table[]);
//  Nome:       printInfoMovie;
//  Objetivo:	imprime os filmes, com prefixo, ordenados pelos valores de rating.
// ---------------------------------------------------------------------------------------
ABP* newABP(char tag[]);
//  Nome:       newABP;
//  Objetivo:   cria um novo nodo de uma ABP.
// ---------------------------------------------------------------------------------------
void insertABP(ABP* node, char tag[], int movieID, int FLAG, int C, ABP *dad);
//  Nome:       insertABP;
//  Objetivo:   insere as informacoes de uma tag em uma ABP.
// ---------------------------------------------------------------------------------------
ABP* searchABP(ABP* node, char tag[]);
//  Nome:       searchABP;
//  Objetivo:   procura uma tag em uma ABP.
// ---------------------------------------------------------------------------------------
void leArqTags(ABP* tags);
//  Nome:       leArqTags;
//  Objetivo:   le o arquivo de tags e salva os dados do arquivo em uma ABP.
// ---------------------------------------------------------------------------------------
void printInfoUser(int user, USERRATING* userList, HASHLIST *table[]);
//  Nome:       printInfoUser;
//  Objetivo:   imprime os filmes avaliados por um usuario.
// ---------------------------------------------------------------------------------------
void printTopMovies(char title[], HASHLIST *table[]);
//  Nome:       printTopMovies;
//  Objetivo:   imprime os melhores filmes de um determinado genero.
// ---------------------------------------------------------------------------------------
int genreCheck(char *genre, GENRELIST *head);
//  Nome:       genreCheck;
//  Objetivo:   checa se um genero consta em uma lista de generos.
// ---------------------------------------------------------------------------------------
void searchMoviesByGenre(HASHLIST *head, int *movieIDs, int *count, char *genre);
//  Nome:       searchMoviesByGenre;
//  Objetivo:   salva, em um vetor, os todos os filmes de um determinado genero.
// ---------------------------------------------------------------------------------------
int belongToTag(int IDs[], int size, int movieID);
//  Nome:       belongToTag;
//  Objetivo:   checa se um ID de um filme pertence a uma determinada tag.
// ---------------------------------------------------------------------------------------
void printMoviesWithTags(char *prefix, HASHLIST *table[], ABP* tags);
//  Nome:       printMoviesWithTags;
//  Objetivo:   imprime os filmes que possuem uma determinada tag.
// ---------------------------------------------------------------------------------------
int IDbelongs(int *top10, int ID);
//  Nome:       IDbelongs;
//  Objetivo:   checa se um ID de um filme pertence a lista top 10.
// ---------------------------------------------------------------------------------------
void sortMovies(int *movies, int size, HASHLIST *table[], int *top10);
//  Nome:       sortMovies;
//  Objetivo:   ordena os 10 melhores filmes de um vetor de filmes.
// ---------------------------------------------------------------------------------------
void sortMovies2(int *movies, float *rating, int size);
//  Nome:       sortMovies2;
//  Objetivo:   ordena os filmes de um vetor de filmes pelo rating.
// ---------------------------------------------------------------------------------------

// ARQUIVOS .c  //////////////////////////////////////////////////////////////////////////

#include "functions/list.c"
#include "functions/trie.c"
#include "functions/hash.c"
#include "functions/file.c"
#include "functions/abp.c"
#include "functions/commands.c"

// ---------------------------------------------------------------------------------------