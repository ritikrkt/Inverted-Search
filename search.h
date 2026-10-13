#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1

#define MAX_WORD_LEN 100
#define MAX_FILE_NAME 100
#define HASH_SIZE 26

typedef struct sub_node
{
    int word_count;
    char file_name[MAX_FILE_NAME];
    struct sub_node *sub_link;

} Sub_node;


typedef struct main_node
{
    int file_count;
    char word[MAX_WORD_LEN];

    Sub_node *sub_link;
    struct main_node *main_link;

} Main_node;

typedef struct file_node
{
    char file_name[MAX_FILE_NAME];
    struct file_node *link;

} Flist;

typedef struct result_node
{
    char file_name[MAX_FILE_NAME];
    int count;
    struct result_node *link;
} Result_node;

int read_and_validation(int argc, char *argv[], Flist **head);

int insert_fileName(int index, Flist **head, char *argv[]);

int create_database(FILE *fptr_datafile, char *file_name,
                    Main_node *hash_table[]);

void display_database(Main_node *hash_table[]);

void search_database(Main_node *hash_table[]);

void save_database(Main_node *hash_table[]);

int create_indexlist(FILE *fp, Main_node *hash_table[]);

int update_database(Main_node *hash_table[], Flist **head);

#endif