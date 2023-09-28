#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt for Pyramid Height
    int x;
    do
    {
        x = get_int("Height: ");
    }
    while (x < 1 || x > 8);

    // Print rows
    for (int row = 0; row < x; row++)
    {
        // Empty spaces to create angles
        for (int empty = x - 1; empty > row; empty--)
        {
            printf(" ");
        }

        // Left height
        for (int h_lft = 0; h_lft <= row; h_lft++)
        {
            printf("#");
        }
        // Middle gap
        printf("  ");

        // Right height
        for (int h_rgt = 0; h_rgt <= row; h_rgt++)
        {
            printf("#");
        }
        printf("\n");
    }
}
