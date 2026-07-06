#include "invt.h"

// Function to update database from backup file
int update_db(ht_arr *h_table)
{
  
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        if(h_table[i].head != NULL)
        {
            printf("ERROR : Hash table is not empty\n");
            return FAILURE;
        }
    }

    char filename[20];

    printf("Enter the file name : ");
    scanf("%s", filename);

  
    if(strstr(filename, ".txt") == NULL)
    {
        printf("ERROR : file name is not valid\n");
        return FAILURE;
    }

    
    FILE *fp = fopen(filename, "r");

    if(!fp)
        return FAILURE;


    char magic_string[20];

    int len = strlen(MAGIC_STRING);

    fread(magic_string, 1, len, fp);

    magic_string[len] = '\0';

  
    if(strcmp(magic_string, MAGIC_STRING) != 0)
    {
        printf("ERROR : The Magic String is not matching\n");

        fclose(fp);

        return FAILURE;
    }

    
    char line[256];

    while(fscanf(fp, "%255[^\n]", line) == 1)
    {
       
        fgetc(fp);

        char *token = strtok(line, ";#\n");

        if(token == NULL)
            continue;

       
        token = strtok(NULL, ";#\n");

        if(token == NULL)
            continue;

        char word[30];

        strncpy(word, token, sizeof(word) - 1);

        word[sizeof(word) - 1] = '\0';

       
        token = strtok(NULL, ";#\n");

        if(token == NULL)
            continue;

        int f_count = atoi(token);

       
        for(int j = 0; j < f_count; j++)
        {
            char *wcount_tok = strtok(NULL, ";#\n");
            char *fname_tok  = strtok(NULL, ";#\n");

            if(wcount_tok == NULL || fname_tok == NULL)
                break;

            int w_count = atoi(wcount_tok);

           
            for(int k = 0; k < w_count; k++)
            {
                insert_word(h_table, word, fname_tok);
            }
        }
    }

   
    fclose(fp);

    return SUCCESS;
}