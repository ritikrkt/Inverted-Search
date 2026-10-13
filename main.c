#include "search.h"

int main(int argc, char *argv[])
{
    Flist *head = NULL;

    Main_node *hash_table[HASH_SIZE] = {NULL};

    int choice;

    while (1)
    {
        printf("\n========== INVERTED SEARCH ==========\n");
        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Update Database\n");
        printf("5. Save Database\n");
        printf("6. Exit\n");
        printf("=====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
            {
                /* Read and validate files */
                read_and_validation(argc, argv, &head);

                /* Create database */
                Flist *temp = head;

                while (temp != NULL)
                {
                    FILE *fptr = fopen(temp->file_name, "r");

                    if (fptr == NULL)
                    {
                        printf("Unable to open %s\n",
                               temp->file_name);

                        temp = temp->link;
                        continue;
                    }

                    if (create_database(fptr,
                                        temp->file_name,
                                        hash_table) == SUCCESS)
                    {
                        printf("%s: Database created successfully\n",
                               temp->file_name);
                    }
                    else
                    {
                        printf("%s: Database creation failed\n",
                               temp->file_name);
                    }

                    fclose(fptr);

                    temp = temp->link;
                }

                break;
            }

            case 2:
            {
                /* Display database */
                display_database(hash_table);
                break;
            }

            case 3:
            {
                /* Search database */
                search_database(hash_table);
                break;
            }

            case 4:
            {
                update_database(hash_table, &head);
                break;
            }

            case 5:
            {
                /* Save database */
                save_database(hash_table);
                break;
            }

            case 6:
            {
                printf("\nExiting program...\n");
                return SUCCESS;
            }

            default:
            {
                printf("\nInvalid choice\n");
            }
        }
    }

    return SUCCESS;
}