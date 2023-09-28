#include <stdio.h>

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

    FILE *what = fopen(argv[1], "w");
    uint8_t buffer;

    fread(h, sizeof(uint8_t), HEADER_SIZE, input);
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);
}