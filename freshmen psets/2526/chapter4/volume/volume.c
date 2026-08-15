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

    // crate an array of 44 (header size) bytes for your header
    uint8_t header[HEADER_SIZE];
    // read the header from the input file
    fread(&header, sizeof(uint8_t), HEADER_SIZE, input);
    // write the header to the output file
    fwrite(&header, sizeof(uint8_t), HEADER_SIZE, output);

    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // multiply the same value by the volume factor
        buffer = buffer * factor;
        // write new sample to output file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
