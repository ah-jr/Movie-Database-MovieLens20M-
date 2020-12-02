// ======================================================================
// Funcoes Arvore ABP:

// Cria ABP nova:
ABP* newABP(char tag[])
{
    ABP* node = malloc(sizeof(ABP));

    node->movieID = malloc(sizeof(int));

    strcpy(node->tag, tag);
    node->movieNum = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}

// Insere tag em ABP:
insertABP(ABP* node, char tag[], int movieID, int FLAG, int C, ABP* dad)
{
    if (node == NULL){
        node = newABP(tag);
        node->movieID[node->movieNum] = movieID;
        node->movieNum = node->movieNum + 1;
        if (C == 1) dad->right = node;
        else dad->left = node;
    }
    else if (strcmp(node->tag, tag) == 0){
        if(belongToTag(node->movieID, node->movieNum, movieID) == 0)
        {
            int *tempArray = malloc(sizeof(int) * node->movieNum);

            for (int i=0; i<node->movieNum; i++)
            {
                tempArray[i] = node->movieID[i];
            }
            node->movieID = realloc(node->movieID, (sizeof(int) * node->movieNum + 1));

            for (int i=0; i<node->movieNum; i++)
            {
                node->movieID[i] = tempArray[i];
            }
            node->movieID[node->movieNum] = movieID;
            node->movieNum = node->movieNum + 1;

            free(tempArray);

        }
    }

    else if (strlen(tag) < strlen(node->tag))
        insertABP(node->left, tag, movieID, FLAG, 0, node);
    else if (strlen(tag) >= strlen(node->tag))
        insertABP(node->right, tag, movieID, FLAG, 1, node);

}

// Procura na arvore ABP:
ABP* searchABP(ABP* node, char tag[])
{
    if (node == NULL || strcmp(node->tag, tag) == 0)
       return node;

    if (strlen(node->tag) <= strlen(tag))
       return searchABP(node->right, tag);

    return searchABP(node->left, tag);
}

// Checa se um filme ja esta em uma lista
int belongToTag(int IDs[], int size, int movieID)
{
    for (int i = 0; i<size; i++)
    {
        if (IDs[i] == movieID) return 1;
    }
    return 0;
}

