// ======================================================================
// Funcoes que computa os comandos:

void printInfoMovie(char title[], TRIE* head, HASHLIST *table[])
{
    IDLIST *list = {NULL};
    HASHLIST *temp;
    int hashCode, i=0;
    search(head, title, &list);
    IDLIST *curr = list;
    int *movies = malloc(sizeof(int)*100000);
    float *rating = malloc(sizeof(float)*100000);


    printf("\nID\tVOTOS\tMEDIA\tTITULO\n\n");

    while(curr != NULL)
    {
        hashCode = hash(curr->ID);
        temp = table[hashCode];
        while(temp != NULL)
        {
            if(temp->movieID == curr->ID){

                movies[i] = curr->ID;
                rating[i] = temp->ratingAvg/temp->ratingQnt;
                i++;
            }
            temp = temp->next;
        }
        curr = curr->next;
    }

    sortMovies2(movies, rating, i);


    for (int j = 0; j < i; j++)
    {
        printf("%d:\t", movies[j]);
        hashCode = hash(movies[j]);
        temp = table[hashCode];
        while(temp != NULL)
        {
            if(temp->movieID == movies[j]){
                printf("%d\t", temp->ratingQnt);
                if (temp->ratingQnt != 0) printf("%.2f\t", temp->ratingAvg / temp->ratingQnt);
                else printf("N/A\t");
                printf("%s\t", temp->title);
                printf("\n");
                printf("GENRES:\t");
                printGenreList(temp->genreList);
                printf("\n");
                printf("\n");
            }
            temp = temp->next;
        }
    }
}


void sortMovies2(int *movies, float *rating, int size)
{
    for (int gap = size/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < size; i += 1)
        {
            float temp = rating[i];
            int temp2 = movies[i];
            int j;
            for (j = i; j >= gap && rating[j - gap] < temp; j -= gap) {
                rating[j] = rating[j - gap];
                movies[j] = movies[j - gap];
            }
            rating[j] = temp;
            movies[j] = temp2;
        }
    }
}


void printInfoUser(int user, USERRATING* userList, HASHLIST *table[])
{
    HASHLIST *temp;
    int hashCode;

    printf("MEDIA\tVOTOS\tRATING\tTITULO\n\n");

    for(int i = 0; i < userList[user].ratingNum; i++){
        hashCode = hash(userList[user].movieID[i]);
        temp = table[hashCode];
        if (temp->ratingQnt != 0) printf("%.2f\t", temp->ratingAvg / temp->ratingQnt);
        else printf("N/A\t");
        printf("%d\t", temp->ratingQnt);
        printf("%.2f\t", userList[user].rating[i]);
        printf("%s\n", temp->title);
    }
}


void printTopMovies(char genre[], HASHLIST *table[])
{
    HASHLIST *temp;
    int *movieIDs = malloc(sizeof(int) * MOVIE_MAX);
    int top10[10] = {0};
    int count = 0;
    int hashCode;

    for (int i = 0; i< TABLE_SIZE; i++)
    {
        temp = table[i];
        searchMoviesByGenre(temp, movieIDs, &count, genre);
    }

    sortMovies(movieIDs, count, table, top10);

    printf("\nMEDIA\tCOUNT\tTITULO\n\n");

    for (int i = 0; i < 10; i++)
    {
        hashCode = hash(top10[i]);
        temp = table[hashCode];
        while(temp != NULL)
        {
            if(temp->movieID == top10[i]){
                if (temp->ratingQnt != 0) printf("%.2f\t", temp->ratingAvg / temp->ratingQnt);
                else printf("N/A\t");
                printf("%d\t", temp->ratingQnt);
                printf("%s\n", temp->title);
                printf("GENRES:\t");
                printGenreList(temp->genreList);
                printf("\n");
                printf("\n");
                break;
            }
            temp = temp->next;
        }
    }
}


void sortMovies(int *movies, int size, HASHLIST *table[], int *top10)
{
    HASHLIST *temp;
    int hashCode, IDTEMP, flag = 1;
    float maxTemp = 0;
    float AVG = 0;

    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < size; i++)
        {
            flag = 1;
            hashCode = hash(movies[i]);
            temp = table[hashCode];
            while(flag)
            {
                if(temp->movieID != movies[i])
                    temp = temp->next;
                else flag = 0;
            }
            if(temp->ratingQnt != 0) AVG = temp->ratingAvg/temp->ratingQnt;
            if(AVG > maxTemp && (IDbelongs(top10, temp->movieID) == 0) && temp->ratingQnt > 1000) {
                maxTemp = AVG;
                IDTEMP = temp->movieID;
            }
        }
        top10[j] = IDTEMP;
        maxTemp = 0;
    }
}


int IDbelongs(int *top10, int ID)
{
    for (int i = 0; i<10; i++)
    {
        if (ID == top10[i]) return 1;
    }
    return 0;
}


void printMoviesWithTags(char *prefix, HASHLIST *table[], ABP* tags)
{
    int i=0, j=0, k=0;
    ABP *requiredTag, *referenceTag;
    int hashCode, flag = 0;
    HASHLIST *temp;
    char readTags[10][TAG_SIZE];
    int arraySize[10];

    i+=2;
    while (prefix[i-1] != '\0' && prefix[i-2] != '\0')
    {
        if(prefix[i] == 39){
            readTags[j][k] = '\0';
            j++;
            arraySize[j] = k;
            k=0;
            i+=3;
        }
        else
        {
            readTags[j][k] = prefix[i];
            k++;
            i++;
        }
    }

    printf("FILMES com as TAGS: ");
    for (int u = 0; u < j; u++)
        printf("[%s] ", readTags[u]);

    printf("\nMEDIA\tVOTOS\tTITULO\n\n");


    referenceTag = searchABP(tags, readTags[0]);
    if (referenceTag != NULL)
    {
        for (int m = 0; m < referenceTag->movieNum; m++)
        {
            for (int l = 1; l < j; l++)
            {
                requiredTag = searchABP(tags, readTags[l]);
                if (requiredTag != NULL)
                {
                    for (int p = 0; p < requiredTag->movieNum; p++)
                    {
                        if (requiredTag->movieID[p] == referenceTag->movieID[m])
                            flag++;
                    }
                }
            }
            if (flag == j - 1)
            {
                hashCode = hash(referenceTag->movieID[m]);
                temp = table[hashCode];
                while(temp != NULL)
                {
                    if(temp->movieID == referenceTag->movieID[m]){
                        if (temp->ratingQnt != 0) printf("%.2f\t", temp->ratingAvg / temp->ratingQnt);
                        else printf("N/A\t");
                        printf("%d\t", temp->ratingQnt);
                        printf("%s\n", temp->title);
                        break;
                    }
                    temp = temp->next;
                }
            }
            flag = 0;
        }
    }
    j = 0;
}
