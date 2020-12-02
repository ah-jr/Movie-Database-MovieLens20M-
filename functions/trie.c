// ======================================================================
// Funcoes Arvore Trie:


TRIE* getNewTrieNode()
{
	TRIE* node = (TRIE*)malloc(sizeof(TRIE));
	node->isLeaf = 0;
	node->movieID = 0;

	for (int i = 0; i < CHAR_SIZE; i++)
		node->character[i] = NULL;

	return node;
}


void insert(TRIE* head, char* str, int ID)
{
	TRIE* curr = head;
	while (*str)
	{
	    // Condicoes de insercao:
	    if (*str>127 || *str < 0)
        {
            if (curr->character[128] == NULL)
                curr->character[128] = getNewTrieNode();
            curr = curr->character[128];
	    }
        else
        {
            if (curr->character[*str] == NULL)
                curr->character[*str] = getNewTrieNode();
            curr = curr->character[*str];
        }

		str++;
	}
	curr->isLeaf = 1;
	curr->movieID = ID;
}

int search(TRIE* head, char* str, IDLIST **list)
{
	if (head == NULL)
		return 0;

	TRIE* curr = head;
	while (*str)
	{
		if(*str>127 || *str < 0) curr = curr->character[128];
		else curr = curr->character[*str];

		if (curr == NULL)
			return 0;

		str++;
	}

	saveIDs(curr, list);
	return curr->movieID;
}

int haveChildren(TRIE* curr)
{
	for (int i = 0; i < CHAR_SIZE; i++)
		if (curr->character[i])
			return 1;

	return 0;
}

int deletion(TRIE* *curr, char* str)
{
	if (*curr == NULL)
		return 0;

	if (*str)
	{
		if (*curr != NULL && (*curr)->character[*str - 'a'] != NULL &&
			deletion(&((*curr)->character[*str - 'a']), str + 1) &&
			(*curr)->isLeaf == 0)
		{
			if (!haveChildren(*curr))
			{
				free(*curr);
				(*curr) = NULL;
				return 1;
			}
			else {
				return 0;
			}
		}
	}

	if (*str == '\0' && (*curr)->isLeaf)
	{
		if (!haveChildren(*curr))
		{
			free(*curr);
			(*curr) = NULL;
			return 1;
		}

		else
		{
			(*curr)->isLeaf = 0;
			return 0;
		}
	}

	return 0;
}


//Função que lista IDs de um nodo:
int saveIDs(TRIE* head, IDLIST **first)
{
	if (head == NULL)
		return 0;

    TRIE* curr = head;
    if(curr->movieID != 0)
    {
        insertList(first, curr->movieID, 0);
    }

	for (int i = 0; i<129; i++)
	{
	    if(curr->character[i] != NULL) saveIDs(curr->character[i], first);
	}
	return 0;
}
