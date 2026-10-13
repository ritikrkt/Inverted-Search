#include "search.h"

int read_and_validation(int argc, char *argv[], Flist **head)
{
    for (int i = 1; i < argc; i++)
    {
        char *extn = strrchr(argv[i], '.');

        /* Check .txt extension */
        if (extn == NULL || strcmp(extn, ".txt") != 0)
        {
            printf("%s is not a valid txt file\n", argv[i]);
            continue;
        }

        printf("%s is valid txt file\n", argv[i]);

        /* Check whether file is present */
        FILE *fptr = fopen(argv[i], "r");

        if (fptr == NULL)
        {
            printf("%s file does not exist\n", argv[i]);
            continue;
        }

        /* Check whether file is empty */
        fseek(fptr, 0, SEEK_END);

        if (ftell(fptr) == 0)
        {
            printf("%s file is empty\n", argv[i]);
            fclose(fptr);
            continue;
        }

        fclose(fptr);

        /* Insert filename into Flist */
        if (insert_fileName(i, head, argv) == SUCCESS)
        {
            printf("%s file successfully inserted in flist\n", argv[i]);
        }
        else
        {
            printf("%s file is not inserted in flist\n", argv[i]);
        }
    }

    return SUCCESS;
}