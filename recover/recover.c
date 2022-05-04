
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


// size of the blocks
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // file counter
    int counter = 0;

    unsigned char buffer[BLOCK_SIZE];

    FILE* image = NULL;

    // found a jpeg 0 = false, 1 = true
    int found = 0;

    // reads the file
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // check if the block start with JPEG Header
        if(buffer[0] ==  0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (found == 1)
            {
                fclose(image);
            }
            else
            {
                found = 1;
            }

            char filename[8];
            sprintf(filename, "%03d.jpg", counter);
            image = fopen(filename, "a");
            counter++;

        }

        if (found == 1)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, image);
        }

    }

    // close files
    fclose(file);
    fclose(image);

    return 0;
}