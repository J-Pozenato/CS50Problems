// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


// Number of bytes in .wav header
const int HEADER_SIZE = 44;


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t header[HEADER_SIZE]; // define size of header, 8bits * HEADER_SIZE(44)

    // Copy header from input file to output file
    fread(header, HEADER_SIZE, 1, input);
    fwrite(header, HEADER_SIZE, 1, output);

    int16_t buffer;
    //Read samples from input file and write updated data to output file
    while(fread(&buffer, sizeof(int16_t), 1, input))
    {
        // change volume by factor
        buffer *= factor;
        fwrite(&buffer, sizeof(int16_t), 1, output); //write into the output file whit the new volume
    }
    // Close files
    fclose(input);
    fclose(output);
}
