#include "invt.h"

// Function to display the complete hash table contents
void display_table(ht_arr *table) 
{
    
    printf("=====================================================================================================\n");

    
    printf("| Index |        Word      | Files_Count |      File Name       | Word_Count |\n");

    
    printf("=====================================================================================================\n");

    for (int i = 0; i < TABLE_SIZE; i++) 
    {
       
        m_node *main = table[i].head;

        
        while (main) 
        {
           
            printf("| %-5d | %-16.16s | %-11d |", 
                   i, main->word, main->f_count);

            s_node *sub = main->s_link;

            if (sub == NULL) 
            {
                printf(" %-20s | %-10s |\n", "-", "-");
            } 
            else 
            {
                
                printf(" %-20.20s | %-10d |\n", sub->f_name, sub->w_count);

               
                sub = sub->link;

        
                while (sub) 
                {
                    
                    printf("| %-5s | %-16s | %-11s | %-20.20s | %-10d |\n", 
                           " ", " ", " ", sub->f_name, sub->w_count);

                  
                    sub = sub->link;
                }
            }

            printf("=====================================================================================================\n");

            main = main->m_link;
        }
    }
}