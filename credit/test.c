#include <cs50.h>
#include <stdio.h>

bool valid_triangle(int x, int y, int z);

int main(void)
{
    int number[3];
    for (int i = 0; i < 3; i++)
    {
        number[i] = get_float("Number: ");
    }
    int valid = valid_triangle(number[0], number[1], number [2]);
    printf("%i\n", valid);
}

bool valid_triangle(int x, int y, int z)
{
    if (x <= 0 || y <= 0 || z <= 0)
    {
        return false;
    }
    if (x + y <= z || y + z <= x || x + z <= y)
    {
        return false;
    }
    else
    {
        return true;
    }
}