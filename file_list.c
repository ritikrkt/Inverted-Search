#include "search.h"

int insert_fileName(int index, Flist **head, char *argv[])
{
    Flist *new = malloc(sizeof(Flist));

    if (new == NULL)
    {
        return FAILURE;
    }

    strcpy(new->file_name, argv[index]);
    new->link = NULL;

    /* If list is empty */
    if (*head == NULL)
    {
        *head = new;
        return SUCCESS;
    }

    /* Check duplicate file */
    Flist *temp = *head;

    while (temp != NULL)
    {
        if (strcmp(temp->file_name, argv[index]) == 0)
        {
            free(new);
            return FAILURE;
        }

        if (temp->link == NULL)
        {
            break;
        }

        temp = temp->link;
    }

    /* Insert at last */
    temp->link = new;

    return SUCCESS;
}