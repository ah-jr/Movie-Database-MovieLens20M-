// ======================================================================
// Funcoes Leitura de Arquivos:


// Le ratings.csv

void leArqRating(HASHLIST *table[], USERRATING userList[])
{
    FILE *p = fopen("files/rating.csv", "r");

    char temp[TITLE_SIZE];
    int userTEMP, userMax, movieIDTEMP, ratingNumTEMP;
    HASHLIST *hashTEMP;

    int x = 0;
    for(int i = 0; i < 39; i++) getc(p);

    while(!feof(p))
    {
        while(!feof(p))
        {
            temp[x] = getc(p);
            if(temp[x] == ',')
            {
                temp[x] = '\0';
                break;
            }
            x++;
        }
        // CONSIDERAR USERID:
        userTEMP = atoi(temp);

        x = 0;

        while(!feof(p))
        {
            temp[x] = getc(p);
            if(temp[x] == ',')
            {
                temp[x] = '\0';
                break;
            }
            x++;
        }
        x = 0;
        movieIDTEMP = atoi(temp);

        while(!feof(p))
        {
            temp[x] = getc(p);
            if(temp[x] == ',')
            {
                temp[x] = '\0';
                break;
            }
            x++;
        }
        x = 0;

        ratingNumTEMP = userList[userTEMP].ratingNum;
        if (ratingNumTEMP < 999)
        {
            userList[userTEMP].movieID[ratingNumTEMP] = movieIDTEMP;
            userList[userTEMP].rating[ratingNumTEMP] = atof(temp);
            userList[userTEMP].ratingNum++;
        }

        hashTEMP = searchHashTable(table, movieIDTEMP);
        if(hashTEMP != NULL)
        {
            hashTEMP->ratingAvg += atof(temp);
            hashTEMP->ratingQnt++;

        }

        while(getc(p) != '\n' && !feof(p));

        if (userTEMP > userMax) userMax = userTEMP;
    }

    fclose(p);
}


// Le tag.csv
void leArqTags(ABP* tags)
{
    FILE *p = fopen("files/tag.csv", "r");

    char tagTEMP[TAG_SIZE], temp[TITLE_SIZE];
    int movieIDTEMP, tagNumTEMP;
    int FLAG = 0, brazilCount =0;
    ABP *root;

    int x = 0;
    for(int i = 0; i < 36; i++) getc(p);

    while(!feof(p))
    {
        while(getc(p) != ',' && !feof(p));
        x = 0;

        while(!feof(p))
        {
            temp[x] = getc(p);
            if(temp[x] == ',')
            {
                temp[x] = '\0';
                break;
            }
            x++;
        }
        x = 0;
        movieIDTEMP = atoi(temp);
        getc(p);
        while(!feof(p))
        {
            temp[x] = getc(p);
            if(temp[x] == '"')
            {
                temp[x] = '\0';
                break;
            }
            x++;
        }
        x = 0;
        if(strlen(temp) < 100)
        {
            strcpy(tagTEMP, temp);
            insertABP(tags, tagTEMP, movieIDTEMP, FLAG, 1, root);
            FLAG = 0;
        }

        while(getc(p) != '\n' && !feof(p));
    }
    fclose(p);
}


// Le movie.csv

void leArqMovie(TRIE* head, HASHLIST *table[])
{
    IDLIST *IDs = {0};
    FILE *p = fopen("files/movie.csv", "r");

    char temp[TITLE_SIZE];
    char titleTEMP[TITLE_SIZE];
    GENRELIST *genreList = {0};
    int IDTEMP;

    int x = 0;
    for(int i = 0; i < 26; i++) getc(p);

    while(!feof(p))
    {
        //Le ID:
        getc(p);
        while(!feof(p))
        {
            temp[x] = getc(p);
            if(temp[x] == ',')
            {
                temp[x] = '\0';
                break;
            }
            x++;
        }
        IDTEMP = atoi(temp);
        x = 0;

        //Le Titulo:
        getc(p);
        while(!feof(p))
        {
            temp[x] = getc(p);
            if(temp[x] == '"')
            {
                temp[x] = '\0';
                break;
            }
            x++;
        }
        x = 0;
        strcpy(titleTEMP, temp);
        insert(head, temp, IDTEMP);

        //Le genero:
        getc(p);
        getc(p);


        while(!feof(p))
        {
            temp[x] = getc(p);
            if(temp[x] == '|')
            {
                temp[x] = '\0';
                insertGenreList(&genreList, temp);
                x = -1;
            }
            if(temp[x] == '"')
            {
                temp[x] = '\0';
                insertGenreList(&genreList, temp);
                break;
            }
            x++;
        }
        x = 0;

        insertHashTable(table, titleTEMP, genreList, 0, 0, IDTEMP);
        genreList = createGenreList();

    }
    fclose(p);
}

