#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    // Prompt for number then print function result
    int n = get_int("Number:  ");
    printf("Collatz: %i\n", collatz(n));
}

int collatz(int n)
{
    // Recursion base case
    if (n == 1)
        return 0;
    // Two recursive cases depending on even or odd
    else if ((n % 2) == 0)
        return collatz(n / 2) + 1;
    else
        return collatz(3 * n + 1) + 1; // Plus one to add to the counter of steps
}