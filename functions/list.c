// ======================================================================
// Funcoes Listas:

IDLIST* createList(){
	return NULL;
}


// Insercao na lista encadeada:
void insertList(IDLIST **head, int ID, float rating)
{
    IDLIST *newNode = malloc(sizeof(IDLIST));
    newNode->ID = ID;
    newNode->rating = rating;
    newNode->next = NULL;

    if(*head == NULL)
         *head = newNode;
    else
    {
        IDLIST *lastNode = *head;
        while(lastNode->next != NULL)
            lastNode = lastNode->next;

        lastNode->next = newNode;
    }
}


// Imprime uma lista encadeada:
void printList(IDLIST *head)
{
    IDLIST *temp = head;


    while(temp != NULL)
    {
         printf("%d->", temp->ID);
         temp = temp->next;
    }
    printf("NULL\n");
}

// Criacao de lista de generos:
GENRELIST* createGenreList(){
	return NULL;
}

// Insercao na lista de generos:
void insertGenreList(GENRELIST **head, char genre[])
{
    GENRELIST *newNode = malloc(sizeof(GENRELIST));
    strcpy(newNode->genre, genre);
    newNode->next = NULL;

    if(*head == NULL)
         *head = newNode;
    else
    {
        GENRELIST *lastNode = *head;
        while(lastNode->next != NULL)
            lastNode = lastNode->next;

        lastNode->next = newNode;
    }
}

// Imprime uma lista de genero:
void printGenreList(GENRELIST *head)
{
    GENRELIST *temp = head;


    while(temp != NULL)
    {
        printf("%s", temp->genre);
        temp = temp->next;
        if (temp != NULL) printf(" | ");
    }
}

// Procura filmes que possuem algum genero
void searchMoviesByGenre(HASHLIST *head, int *movieIDs, int *count, char *genre)
{
    HASHLIST *temp = head;

    while(temp != NULL)
    {
        if(genreCheck(genre, temp->genreList))
        {
            movieIDs[*count] = temp->movieID;
            *count = *count + 1;
        }
        temp = temp->next;
    }
}

// Checa se um genero esta em uma lista
int genreCheck(char *genre, GENRELIST *head)
{
    GENRELIST *temp = head;

    while(temp != NULL)
    {
        if (stricmp(temp->genre, genre) == 0) return 1;
        temp = temp->next;
    }
    return 0;
}

