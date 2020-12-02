// ======================================================================
// Funcao Hash:

int hash(int ID){
	return ID*2654435761 % TABLE_SIZE;
}


// Funcao que insere nas listas encadeadas da tabela hash:
void insertHashList(HASHLIST **head, char title[], GENRELIST *genreList, float ratingAvg, int ratingQnt, int movieID)
{
    HASHLIST *newNode = malloc(sizeof(HASHLIST));
    strcpy(newNode->title, title);
    newNode->movieID = movieID;
    newNode->genreList = genreList;
    newNode->ratingAvg = ratingAvg;
    newNode->ratingQnt = ratingQnt;
    newNode->next = NULL;

    if(*head == NULL)
         *head = newNode;
    else
    {
        HASHLIST *lastNode = *head;
        while(lastNode->next != NULL)
            lastNode = lastNode->next;

        lastNode->next = newNode;
    }
}


// Funcao que printa lista de Hashes:
void printHashList(HASHLIST *head)
{
    HASHLIST *temp = head;

    while(temp != NULL)
    {
         printf("%s->", temp->title);
         temp = temp->next;
    }
    printf("NULL\n");
}


// Funcao que printa a tabela Hash:
void printHashTable(HASHLIST *table[]){
	int i = 0;
	for(i = 0; i < TABLE_SIZE; i++){
		printf("[%d] ", i);
		printHashList(table[i]);
	}
}


// Insere na tabela Hash:
void insertHashTable(HASHLIST *table[], char title[], GENRELIST *genreList, float ratingAvg, int ratingQnt, int ID){
    int hashCode = hash(ID);
	insertHashList(&table[hashCode], title, genreList, ratingAvg, ratingQnt, ID);
}


// Procura dados do filme pelo ID na tabela Hash e retorna ponteiro:
HASHLIST *searchHashTable(HASHLIST *table[], int ID){

    int hashCode = hash(ID);
	HASHLIST *temp = table[hashCode];

	while(temp != NULL){
		if(temp->movieID == ID){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

