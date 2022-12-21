#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK 512

int main(int argc, char *argv[])
{
    // Check that a filename is provided as an argument
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    typedef uint8_t BYTE;

    BYTE buffer[BLOCK];

    size_t bytes_read;

    FILE *current_file = NULL;
    FILE *file = fopen(argv[1], "r");

    char filename[8];

    int filecounter = 0;

    bool found_jpeg = false;

    // TODO: Open the Memory Card
    if (file == NULL)
    {
        printf("Failed to open file %s\n", argv[1]);
        return 1;
    }

    // repeat until memory end of card
    while ((bytes_read = fread(buffer, sizeof(BYTE), BLOCK, file)) > 0)
    {
        // if start of new Jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            found_jpeg = true;

            // close the current file and start a new one
            if (current_file != NULL)
            {
                fclose(current_file);
            }

            printf("Found a new Jpeg\n");
            sprintf(filename, "%03i.jpg", filecounter);
            current_file = fopen(filename, "w");
            filecounter++;
        }
        // if already found Jpeg
        if (found_jpeg)
        {
            fwrite(buffer, sizeof(BYTE), bytes_read, current_file);
        }
    }
    // close any remaining files
    fclose(file);
    if (current_file != NULL)
    {
        fclose(current_file);
    }
    return 0;
}