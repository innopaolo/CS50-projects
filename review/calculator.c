#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Make a calculator
    long x = get_long("Number 1: ");
    long y = get_long("Number 2: ");
    printf("%li\n", x + y);

}