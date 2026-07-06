#ifndef INVT_H
#define INVT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define SUCCESS 0
#define FAILURE 1

#define TABLE_SIZE 28

#define MAGIC_STRING "&&**"


typedef struct sub_node
{
    int w_count;           
    char *f_name;          
    struct sub_node *link; 

} s_node;


typedef struct main_node
{
    char *word;               
    int f_count;              
    s_node *s_link;           
    struct main_node *m_link; 

} m_node;


typedef struct hash_arra
{
    int index;    
    m_node *head; 

} ht_arr;


typedef struct f_list
{
    char *data;          
    struct f_list *link; 

} flist;



// Initialize hash table
void insert_ht(ht_arr *table);

// Validate command line arguments
int validate_cla(int argc, char *argv[], flist **head_f_list);

// Check file is empty or not
int istextpresent(char *filename);

// Insert file name into linked list
int insert_first(char *filename, flist **head_f_list);

// Print file linked list
void print_list(flist **head_f_list);

// Creating database prototypes...

// Create database from files
int create_db(ht_arr *ht_table, flist *head);

// Insert word into database
int insert_word(ht_arr *ht_table, const char *word, const char *filename);

// Find hash index
int index_find(const char ch);

// Display database prototypes...

// Display complete database
void display_table(ht_arr *table);

// Search word in database
int search_db(ht_arr *ht_table);

// Save database into file
int save_db(ht_arr *h_table);

// Update database from saved file
int update_db(ht_arr *h_table);

// Validate files already present
void validate_files(ht_arr *h_table, flist **head_f_list);

// Delete element from file list
void delet_elemtent(flist **head_f_list, char *data);

#endif