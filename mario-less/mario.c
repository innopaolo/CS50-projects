#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt user for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Print rows
    for (int row = 0; row < height; row++)
    {
        // Empty spaces to create angles
        for (int empty = height - 1; empty > row; empty--)
        {
            printf(" ");
        }

        // Print height
        for (int height2 = 0; height2 < row + 1; height2++)
        {
            printf("#");
        }
        // To make sure there's a new line for each row
        printf("\n");
    }

}