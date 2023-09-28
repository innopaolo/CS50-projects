#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

// Define FAT sytem size
const int block = 512;

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover [FILENAME].raw\n");
        return 1;
    }

    // Open memory card and check validity
    FILE *memcard = fopen(argv[1], "r");
    if (memcard == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    // Initialize file for recovered image and its filename
    FILE *outImage = NULL;
    char filename[8]; // 000.jpg plus null character is 8 bytes

    // Define buffer as an array of 512 bytes, called a block
    BYTE buffer[block];

    // Track JPEGs found
    int counter = 0;

    while (fread(buffer, sizeof(BYTE), block, memcard) == block)
    {
        // Ensure only JPEG files are written over
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Each found JPEG opens a new FILE with a new filename
            sprintf(filename, "%03i.jpg", counter);
            outImage = fopen(filename, "w");
            counter++;
        }
        // Check validity before writing
        // Separated condition to write contiguous blocks on same file
        if (outImage != NULL)
        {
            fwrite(buffer, sizeof(BYTE), block, outImage);
        }
    }
    fclose(memcard);
    fclose(outImage);
}