#include <cs50.h>
#include <stdio.h>

int fib(int n);

int main(void)
{
    // Print requested fibonacci number in place
    int n = get_int("Fibonacci place: ");
    printf("Number: %i\n", fib(n));
}

int fib(int n)
{
    // Two base cases due to nature of fib formula (sum of first two digits)
    if (n == 0)
        return 0;
    else if (n == 1)
        return 1;

    // Recursive case
    return (fib(n - 1) + fib(n - 2));
}