#define  _GNU_SOURCE
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#define DICTIONARY "dictionaries/large"

int main(int argc, char *argv[])
{
    FILE *file = fopen(DICTIONARY, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", DICTIONARY);
        return 1;
    }

    char last[46 + 1];
    char word[46 + 1];
    int count = 1;

    // reads each line of the dictionary and create a new word in the hashtable
    while (fscanf(file, "%s", word) != EOF)
    {
        if (strlen(word) > 1)
        {
            if (word[0] == last[0] && word[1] == last[1])
            {
                count++;
            }
            else
            {
                if (strlen(last) > 1)
                {
                    printf("%c%c: %i\n", last[0], last[1], count);
                    count = 1;
                }
            }
        }
        strcpy(last, word);

    }

    fclose(file);
    return 0;
}