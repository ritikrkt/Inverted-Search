#include "search.h"

int update_database(Main_node *hash_table[], Flist **head)
{
    FILE *fp = fopen("database.txt", "r");

    if (fp == NULL)
    {
        printf("Unable to open database.txt\n");
        return FAILURE;
    }

    Main_node *update_hash_table[HASH_SIZE] = {NULL};

    if (create_indexlist(fp, update_hash_table) != SUCCESS)
    {
        printf("\nDatabase loading failed\n");
        fclose(fp);
        return FAILURE;
    }

    printf("\nDatabase loaded successfully\n");

    char new_file_name[MAX_FILE_NAME];

    printf("\nEnter file name to update: ");
    scanf("%s", new_file_name);

    /* Check .txt extension */
    char *extn = strrchr(new_file_name, '.');

    if (extn == NULL || strcmp(extn, ".txt") != 0)
    {
        printf("%s is not a valid txt file\n",
               new_file_name);

        fclose(fp);
        return FAILURE;
    }

    /* Check duplicate file in database */
    int duplicate = 0;

    for (int i = 0; i < HASH_SIZE; i++)
    {
        Main_node *main_temp = update_hash_table[i];

        while (main_temp != NULL)
        {
            Sub_node *sub_temp = main_temp->sub_link;

            while (sub_temp != NULL)
            {
                if (strcmp(sub_temp->file_name,
                           new_file_name) == 0)
                {
                    duplicate = 1;
                    break;
                }

                sub_temp = sub_temp->sub_link;
            }

            if (duplicate)
            {
                break;
            }

            main_temp = main_temp->main_link;
        }

        if (duplicate)
        {
            break;
        }
    }

    if (duplicate)
    {
        printf("%s already exists in database\n",
               new_file_name);
    }
    else
    {
        FILE *new_file = fopen(new_file_name, "r");

        if (new_file == NULL)
        {
            printf("%s file does not exist\n",
                   new_file_name);
        }
        else
        {
            if (create_database(new_file,
                                new_file_name,
                                update_hash_table)
                == SUCCESS)
            {
                printf("\n%s added successfully\n",
                       new_file_name);

                /* Add new file to Flist */
                Flist *new_node =
                    malloc(sizeof(Flist));

                if (new_node != NULL)
                {
                    strcpy(new_node->file_name,
                           new_file_name);

                    new_node->link = NULL;

                    if (*head == NULL)
                    {
                        *head = new_node;
                    }
                    else
                    {
                        Flist *temp = *head;

                        while (temp->link != NULL)
                        {
                            temp = temp->link;
                        }

                        temp->link = new_node;
                    }

                    printf("%s added to file list\n",
                           new_file_name);
                }
            }
            else
            {
                printf("\n%s update failed\n",
                       new_file_name);
            }

            fclose(new_file);
        }
    }

    /*
     * Make updated database
     * the current database
     */
    for (int i = 0; i < HASH_SIZE; i++)
    {
        hash_table[i] = update_hash_table[i];
    }

    /* Display updated database */
    display_database(hash_table);

    fclose(fp);

    return SUCCESS;
}