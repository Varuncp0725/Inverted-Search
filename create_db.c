#include "invt.h"

// Function to create database by reading all files in file linked list
int create_db(ht_arr *ht_table, flist *head)
{
    flist *temp = head;          
    char word[20];             

    while(temp != NULL)
    { 
        
        FILE *fp = fopen(temp->data, "r");

        if(fp != NULL)
        {
           
            while(fscanf(fp, "%s", word) == 1)
            {
                // Insert word into hash table
                if(insert_word(ht_table, word, temp->data) == FAILURE)
                {
                    return FAILURE;
                }
            } 

            
            fclose(fp); 
        }
        else
        {
            
            return FAILURE;
        }

        
        temp = temp->link;
    }

    return SUCCESS;
}


// Function to find index based on first character of word
int index_find(const char ch)
{
    
    if(ch >= 'a' && ch <= 'z')
    {
        return ch - 'a';
    }

    
    else if(ch >= 'A' && ch <= 'Z')
    {
        char lower = tolower(ch);
        return lower - 'a';
    }

  
    else if(isdigit(ch))
    {
        return 26;
    }

   
    else
    {
        return 27;
    }
}


// Function to insert word into hash table
int insert_word(ht_arr * ht_table, const char *word, const char *filename)
{
    // Find index using first letter
    int index = index_find(word[0]); 

    // Get head of that index linked list
    m_node *main = ht_table[index].head;

    // Traverse main nodes
    while(main != NULL)
    {
        // If word already exists
        if(strcmp(word, main->word) == 0)
        {
            s_node *sub = main->s_link;

            // Traverse sub nodes (file list)
            while(sub != NULL)
            {  
                // If same file found
                if(strcmp(filename, sub->f_name) == 0)
                {
                    // Increase word count
                    sub->w_count++;
                    return SUCCESS;
                } 

                sub = sub->link;
            }

            // File not found, create new sub node
            s_node *new_subnode = malloc(sizeof(s_node));

            if(!new_subnode)
            {
                printf("Sub-node Dynamical allocation is Failued\n");
                return FAILURE;
            }

            new_subnode->f_name = strdup(filename);
            new_subnode->w_count = 1;

            // Insert at beginning
            new_subnode->link = main->s_link;
            main->s_link = new_subnode;

            // Increase file count
            main->f_count++;

            return SUCCESS;
        }

        // Move to next main node
        main = main->m_link;
    }

    // Word not found, create new main node
    m_node *new_Mnode = malloc(sizeof(m_node));

    if(!new_Mnode)
    {
        printf("main-node Dynamical allocation is Failued\n");
        return FAILURE;
    }

    new_Mnode->word = strdup(word);
    new_Mnode->f_count = 1;

    // Create new sub node for first file
    s_node *new_Snode = malloc(sizeof(s_node));

    if(!new_Snode)
    {
        printf("Sub-node Dynamical allocation is Failued\n");
        return FAILURE;
    }

    new_Snode->f_name = strdup(filename);
    new_Snode->w_count = 1;
    new_Snode->link = NULL;

    // Link sub node to main node
    new_Mnode->s_link = new_Snode;

    // Insert main node at beginning
    new_Mnode->m_link = ht_table[index].head;
    ht_table[index].head = new_Mnode;

    return SUCCESS;
}