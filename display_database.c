#include "search.h"

void display_database(Main_node *hash_table[])
{
    int i;

    printf("\n========== DATABASE ==========\n");

    for (i = 0; i < HASH_SIZE; i++)
    {
        Main_node *main_temp = hash_table[i];

        if (main_temp != NULL)
        {
            printf("\n[%d]\n", i);

            while (main_temp != NULL)
            {
                printf("Word: %s\n", main_temp->word);
                printf("File Count: %d\n", main_temp->file_count);

                Sub_node *sub_temp = main_temp->sub_link;

                while (sub_temp != NULL)
                {
                    printf("    File: %s, Word Count: %d\n",
                           sub_temp->file_name,
                           sub_temp->word_count);

                    sub_temp = sub_temp->sub_link;
                }

                main_temp = main_temp->main_link;
            }
        }
    }

    printf("\n===============================\n");
}