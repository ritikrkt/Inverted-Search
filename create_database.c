#include "search.h"

int create_database(FILE *fptr_datafile, char *file_name,
                    Main_node *hash_table[])
{
    char word[MAX_WORD_LEN];
    int index = 0;
    int ch;

    while ((ch = fgetc(fptr_datafile)) != EOF)
    {
        if (isalpha(ch))
        {
            word[index++] = tolower(ch);
        }
        else
        {
            if (index > 0)
            {
                word[index] = '\0';
                index = 0;

                int hash_index = word[0] - 'a';

                Main_node *main_temp = hash_table[hash_index];

                /* Search for the word */
                while (main_temp != NULL)
                {
                    if (strcmp(main_temp->word, word) == 0)
                    {
                        break;
                    }

                    main_temp = main_temp->main_link;
                }

                /* Word not found -> create Main Node */
                if (main_temp == NULL)
                {
                    Main_node *new_main = malloc(sizeof(Main_node));

                    if (new_main == NULL)
                        return FAILURE;

                    strcpy(new_main->word, word);
                    new_main->file_count = 0;
                    new_main->sub_link = NULL;
                    new_main->main_link = NULL;

                    /* Insert Main Node */
                    if (hash_table[hash_index] == NULL)
                    {
                        hash_table[hash_index] = new_main;
                    }
                    else
                    {
                        Main_node *temp = hash_table[hash_index];

                        while (temp->main_link != NULL)
                        {
                            temp = temp->main_link;
                        }

                        temp->main_link = new_main;
                    }

                    main_temp = new_main;
                }

                /* Search file in Sub Node */
                Sub_node *sub_temp = main_temp->sub_link;

                while (sub_temp != NULL)
                {
                    if (strcmp(sub_temp->file_name, file_name) == 0)
                    {
                        sub_temp->word_count++;
                        break;
                    }

                    sub_temp = sub_temp->sub_link;
                }

                /* File not found -> create Sub Node */
                if (sub_temp == NULL)
                {
                    Sub_node *new_sub = malloc(sizeof(Sub_node));

                    if (new_sub == NULL)
                        return FAILURE;

                    strcpy(new_sub->file_name, file_name);
                    new_sub->word_count = 1;
                    new_sub->sub_link = NULL;

                    /* Insert Sub Node */
                    if (main_temp->sub_link == NULL)
                    {
                        main_temp->sub_link = new_sub;
                    }
                    else
                    {
                        Sub_node *temp = main_temp->sub_link;

                        while (temp->sub_link != NULL)
                        {
                            temp = temp->sub_link;
                        }

                        temp->sub_link = new_sub;
                    }

                    main_temp->file_count++;
                }
            }
        }
    }

    /* Handle last word */
    if (index > 0)
    {
        word[index] = '\0';

        int hash_index = word[0] - 'a';

        Main_node *main_temp = hash_table[hash_index];

        while (main_temp != NULL)
        {
            if (strcmp(main_temp->word, word) == 0)
                break;

            main_temp = main_temp->main_link;
        }

        if (main_temp == NULL)
        {
            Main_node *new_main = malloc(sizeof(Main_node));

            if (new_main == NULL)
                return FAILURE;

            strcpy(new_main->word, word);
            new_main->file_count = 0;
            new_main->sub_link = NULL;
            new_main->main_link = NULL;

            if (hash_table[hash_index] == NULL)
            {
                hash_table[hash_index] = new_main;
            }
            else
            {
                Main_node *temp = hash_table[hash_index];

                while (temp->main_link != NULL)
                    temp = temp->main_link;

                temp->main_link = new_main;
            }

            main_temp = new_main;
        }

        Sub_node *sub_temp = main_temp->sub_link;

        while (sub_temp != NULL)
        {
            if (strcmp(sub_temp->file_name, file_name) == 0)
            {
                sub_temp->word_count++;
                break;
            }

            sub_temp = sub_temp->sub_link;
        }

        if (sub_temp == NULL)
        {
            Sub_node *new_sub = malloc(sizeof(Sub_node));

            if (new_sub == NULL)
                return FAILURE;

            strcpy(new_sub->file_name, file_name);
            new_sub->word_count = 1;
            new_sub->sub_link = NULL;

            if (main_temp->sub_link == NULL)
            {
                main_temp->sub_link = new_sub;
            }
            else
            {
                Sub_node *temp = main_temp->sub_link;

                while (temp->sub_link != NULL)
                    temp = temp->sub_link;

                temp->sub_link = new_sub;
            }

            main_temp->file_count++;
        }
    }

    return SUCCESS;
}