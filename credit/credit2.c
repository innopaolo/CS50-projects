#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long number = get_long("Number: ");

    int i = ((number / 10) % 10) * 2;
    int j = ((number / 1000) % 10) * 2;
    int k = ((number / 100000) % 10) * 2;
    int l = ((number / 10000000) % 10) * 2;
    int m = ((number / 1000000000) % 10) * 2;
    int n = ((number / 100000000000) % 10) * 2;
    int o = ((number / 10000000000000) % 10) * 2;
    int p = ((number / 1000000000000000) % 10) * 2;

    if (i > 99 )
}