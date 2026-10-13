#include "search.h"

int create_indexlist(FILE *fp, Main_node *hash_table[])
{
    int index;
    char word[MAX_WORD_LEN];
    int file_count;

    while (fscanf(fp, "#%d;%[^;];%d;", &index, word, &file_count) == 3)
    {
        Main_node *new_main = malloc(sizeof(Main_node));

        if (new_main == NULL)
        {
            return FAILURE;
        }

        new_main->file_count = file_count;
        strcpy(new_main->word, word);
        new_main->sub_link = NULL;
        new_main->main_link = NULL;

        Sub_node *sub_tail = NULL;

        for (int i = 0; i < file_count; i++)
        {
            char file_name[MAX_FILE_NAME];
            int word_count;

            fscanf(fp, "%[^;];%d;",
                   file_name, &word_count);

            Sub_node *new_sub = malloc(sizeof(Sub_node));

            if (new_sub == NULL)
            {
                return FAILURE;
            }

            strcpy(new_sub->file_name, file_name);
            new_sub->word_count = word_count;
            new_sub->sub_link = NULL;

            if (new_main->sub_link == NULL)
            {
                new_main->sub_link = new_sub;
            }
            else
            {
                sub_tail->sub_link = new_sub;
            }

            sub_tail = new_sub;
        }

        /* Consume ending # and newline */
            fscanf(fp, "%*c%*c");

        /* Insert Main Node into Hash Table */
        if (hash_table[index] == NULL)
        {
            hash_table[index] = new_main;
        }
        else
        {
            Main_node *main_temp = hash_table[index];

            while (main_temp->main_link != NULL)
            {
                main_temp = main_temp->main_link;
            }

            main_temp->main_link = new_main;
        }
    }

    return SUCCESS;
}