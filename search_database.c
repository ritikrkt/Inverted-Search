#include "search.h"

void search_database(Main_node *hash_table[])
{
    char input[500];
    char *word;

    Result_node *result_head = NULL;

    printf("\nEnter words to search: ");
    scanf(" %[^\n]", input);

    /* Get first word */
    word = strtok(input, " ");

    while (word != NULL)
    {
        int hash_index = tolower(word[0]) - 'a';

        Main_node *temp = hash_table[hash_index];

        /* Search word */
        while (temp != NULL)
        {
            if (strcmp(temp->word, word) == 0)
            {
                Sub_node *sub_temp = temp->sub_link;

                /* Add each matching file to result list */
                while (sub_temp != NULL)
                {
                    Result_node *result_temp = result_head;

                    /* Check whether file already exists */
                    while (result_temp != NULL)
                    {
                        if (strcmp(result_temp->file_name,
                                   sub_temp->file_name) == 0)
                        {
                            result_temp->count += sub_temp->word_count;
                            break;
                        }

                        result_temp = result_temp->link;
                    }

                    /* File not already present */
                    if (result_temp == NULL)
                    {
                        Result_node *new_result =
                            malloc(sizeof(Result_node));

                        if (new_result == NULL)
                            return;

                        strcpy(new_result->file_name,
                               sub_temp->file_name);

                        new_result->count = sub_temp->word_count;
                        new_result->link = result_head;

                        result_head = new_result;
                    }

                    sub_temp = sub_temp->sub_link;
                }

                break;
            }

            temp = temp->main_link;
        }

        /* Next search word */
        word = strtok(NULL, " ");
    }

    /* Sort result list by match count in descending order */

    Result_node *ptr1;
    Result_node *ptr2;

    for (ptr1 = result_head; ptr1 != NULL; ptr1 = ptr1->link)
{
    for (ptr2 = ptr1->link; ptr2 != NULL; ptr2 = ptr2->link)
    {
        if (ptr1->count < ptr2->count)
        {
            int temp_count = ptr1->count;
            ptr1->count = ptr2->count;
            ptr2->count = temp_count;

            char temp_file[MAX_FILE_NAME];

            strcpy(temp_file, ptr1->file_name);
            strcpy(ptr1->file_name, ptr2->file_name);
            strcpy(ptr2->file_name, temp_file);
        }
    }
}

    /* Display result */
    printf("\n========== SEARCH RESULT ==========\n");

    if (result_head == NULL)
    {
        printf("No matching files found.\n");
        return;
    }

    Result_node *result_temp = result_head;

    while (result_temp != NULL)
    {
        printf("File: %s, Match Count: %d\n",
               result_temp->file_name,
               result_temp->count);

        result_temp = result_temp->link;
    }

    printf("===================================\n");
}