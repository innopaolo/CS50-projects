#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number;

    // Prompt user for card number
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    // Find the checksum using a third duplicated variable for number
    long number3 = number / 1;

    // First total sum (8 variables because the most number of digits
    // asked for credit cards is 16, which is 8 digits each half.
    // If there are less digits inputted that are still valid, then the
    // extra variables will simply bring back zero value, which will
    // not affect the overall algorithm).
    int a = number3 % 10;
    int b = (number3 / 100) % 10;
    int c = (number3 / 10000) % 10;
    int d = (number3 / 1000000) % 10;
    int e = (number3 / 100000000) % 10;
    int f = (number3 / 10000000000) % 10;
    int g = (number3 / 1000000000000) % 10;
    int h = (number3 / 100000000000000) % 10;
    int totalsum1 = a + b + c + d + e + f + g + h;

    // Second total sum (same reason above why there are 8 variables)
    int i = ((number3 / 10) % 10) * 2;
    int j = ((number3 / 1000) % 10) * 2;
    int k = ((number3 / 100000) % 10) * 2;
    int l = ((number3 / 10000000) % 10) * 2;
    int m = ((number3 / 1000000000) % 10) * 2;
    int n = ((number3 / 100000000000) % 10) * 2;
    int o = ((number3 / 10000000000000) % 10) * 2;
    int p = ((number3 / 1000000000000000) % 10) * 2;

    // Second total sum extra operation in case some are double digits
    int i2 = (i / 10) + (i % 10);
    int j2 = (j / 10) + (j % 10);
    int k2 = (k / 10) + (k % 10);
    int l2 = (l / 10) + (l % 10);
    int m2 = (m / 10) + (m % 10);
    int n2 = (n / 10) + (n % 10);
    int o2 = (o / 10) + (o % 10);
    int p2 = (p / 10) + (p % 10);

    int totalsum2 = i2 + j2 + k2 + l2 + m2 + n2 + o2 + p2;

    // Add both total sums and check if last digit is zero
    int finalfinal = totalsum1 + totalsum2;
    int realfinalfinal = finalfinal % 10;


    // Find the first two digits using the duplicated variable for number
    long number2 = number * 1;
    while (number2 > 99)
    {
        number2 = number2 / 10;
    }


    // Find the number length using the original variable for number
    int length = 0;
    while (number != 0)
    {
        number = number / 10;
        length++;
    }

    // AMEX
    if ((length == 15) && (number2 / 10 == 3) && (number2 % 10 == 4 || number2 % 10 == 7) && (realfinalfinal == 0))
    {
        printf("AMEX\n");
    }


    // MASTERCARD
    else if (
        (length == 16) && (realfinalfinal == 0) && (number2 / 10 == 5) && (number2 % 10 == 1
                || number2 % 10 == 2
                || number2 % 10 == 3
                || number2 % 10 == 4
                || number2 % 10 == 5))
    {
        printf("MASTERCARD\n");
    }


    // VISA
    else if ((length == 13 || length == 16) && (number2 / 10 == 4) && (realfinalfinal == 0))
    {
        printf("VISA\n");
    }


    // INVALID
    else
    {
        printf("INVALID\n");
    }
}