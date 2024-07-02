#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

//Making a constant for header size
const int HEADER_SIZE = 44;

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open a file\n");
        return 2;
    }

    // Read header
    // TODO #3
    WAVHEADER header;
    fread(&header, HEADER_SIZE, 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header))
    {
        printf("WAV format\n");

        // Open output file for writing
        // TODO #5
        FILE *output = fopen(argv[2], "w");
        if (output == NULL)
        {
            printf("Could not open output file\n");
            return 3;
        }
        // Write header to file
        // TODO #6
        fwrite(&header, HEADER_SIZE, 1, output);

        // Use get_block_size to calculate size of block
        // TODO #7
        int size = get_block_size(header);

        // Write reversed audio to file
        // TODO #8
        //Create a buffer
        int8_t buffer[size];

        //We set pointer at the end of the file
        fseek(input, - 1 * size, SEEK_END);

        //Loop backwards up to header
        while (ftell(input) > HEADER_SIZE - size)
        {
            fread(&buffer, size, 1, input);
            fwrite(&buffer, size, 1, output);
            fseek(input, - 2 * size, SEEK_CUR);
        }

        fclose(input);
        fclose(output);
        return 0;

    }
    else
    {
        printf("Input is not a WAV file.\n");
        return 3;
    }
}
// Checking if given file WAV format
int check_format(WAVHEADER header)
{
    // TODO #4
    //Store characters from header and compare it
    char temp[5];
    for (int i = 0; i < 4; i++)
    {
        temp[i] = header.format[i];
    }
    temp[4] = '\0';

    if (strcmp(temp, "WAVE") == 0)
    {
        return 1;
    }
    return 0;
}
// Returns block size 
int get_block_size(WAVHEADER header)
{
    // TODO #7
    //Using the formula calculating size of a block
    int channels = header.numChannels;
    int bps = header.bitsPerSample;
    return channels * bps / 8;
}