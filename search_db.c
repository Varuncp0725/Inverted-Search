
#include "invt.h"

// Function to search a word in database
int search_db(ht_arr *ht_table)
{
    char word[20];

    
    printf("Enter the word to search : ");
    scanf("%s", word);

    // Find index using first character
    int index = index_find(word[0]);

    printf("===================================================================================\n");
    printf("| Index |        Word        | Files_Count |      File Name      | Word_Count |\n");
    printf("===================================================================================\n");

   
    m_node *mtemp = ht_table[index].head;

    int found = 0;

   
    for (int i = 0; mtemp != NULL; i++)
    {
        
        if(strcmp(mtemp->word, word) == 0)
        {
            found = 1;

         
            printf("| %-5d | %-18s | %-11d |",
                   index, mtemp->word, mtemp->f_count);

            s_node *sub = mtemp->s_link;

            if (sub == NULL)
            {
                printf(" %-19s | %-10s |\n", "-", "-");
            }
            else
            {
                
                while (sub)
                {
                  
                    printf(" %-19s | %-10d |\n", sub->f_name, sub->w_count);

                    
                    if (sub->link != NULL)
                    {
                        printf("| %-5s | %-18s | %-11s |", "", "", "");
                    }

                    sub = sub->link;
                }
            }

           
            printf("===================================================================================\n");

            return SUCCESS;
        }

        
        mtemp = mtemp->m_link;
    }

    
    if(!found)
    {
        printf("Word not found in the database.\n");
    }

    return FAILURE;
}