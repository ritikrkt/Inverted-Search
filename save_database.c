#include "search.h"

void save_database(Main_node *hash_table[])
{
    FILE *fp;

    fp = fopen("database.txt", "w");

    if (fp == NULL)
    {
        printf("ERROR: Unable to create database.txt\n");
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++)
    {
        Main_node *main_temp = hash_table[i];

        while (main_temp != NULL)
        {
            fprintf(fp, "#%d;%s;%d;",
                    i,
                    main_temp->word,
                    main_temp->file_count);

            Sub_node *sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                fprintf(fp, "%s;%d;",
                        sub_temp->file_name,
                        sub_temp->word_count);

                sub_temp = sub_temp->sub_link;
            }

            fprintf(fp, "#\n");

            main_temp = main_temp->main_link;
        }
    }

    fclose(fp);

    printf("\nDatabase successfully saved to database.txt\n");
}