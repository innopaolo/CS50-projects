#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Error message if command line argument is more or less than 2
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Error message if 2nd command line argument is not a digit
    string coconut_digit = argv[1];

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isdigit(coconut_digit[i]) == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Change the coconut digit from string into an int
    int key = atoi(coconut_digit);

    // Get plaintext
    string plain = get_string("plaintext:  ");

    // Plug in key and plain into Caesar's Algorithm +/- the A/a ASCII value to get an alphabetical index to work with % 26
    printf("ciphertext: "); // No new line to accomodate printed chars of encrypted letter in the for loop
    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        if (islower(plain[i]))
        {
            printf("%c", (plain[i] - 97 + key) % 26 + 97);
        }
        else if (isupper(plain[i]))
        {
            printf("%c", (plain[i] - 65 + key) % 26 + 65);
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
    return 0;
}