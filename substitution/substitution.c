#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


bool isnotunique(string letter);

int main(int argc, string argv[])
{
    // Error message if command line argument is more or less than 2
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Error message if 2nd command line argument is not 26 unique letters
    string letters = argv[1];

    for (int i = 0, n = strlen(letters); i < n; i++)
    {
        if (strlen(letters) != 26 || isalpha(letters[i]) == false || isnotunique(letters))
        {
            printf("Key must contain 26 unique letters.\n");
            return 1;
        }
    }

    // Get plaintext and initialize a variable that will map each plaintext char to its key
    string plain = get_string("plaintext:  ");
    int letter_map = 0;

    // Print ciphertext after each char is mapped to its key
    printf("ciphertext: ");

    for (int i = 0, n = strlen(plain); i < n; i++)
    {
        if (islower(plain[i]))
        {
            letter_map = plain[i] - 97; // Difference becomes the index number to match the char in the key
            char potato = tolower(letters[letter_map]); // Ensure the output stays in lowercase
            printf("%c", potato);
        }
        else if (isupper(plain[i]))
        {
            letter_map = plain[i] - 65; // // Difference becomes the index number to match the char in the key
            char potato = toupper(letters[letter_map]); // Ensure the output stays in uppercase
            printf("%c", potato);
        }
        else
        {
            printf("%c", plain[i]);
        }
    }
    printf("\n");
    return 0;
}


// Check if any of the letters are not unique
bool isnotunique(string letter)
{
    bool result = false; // Function will return false by default unless the condition below is met

    for (int i = 0, n = strlen(letter); i < n; i++)
    {
        for (int j = i + 1, o = strlen(letter); j < o; j++) // Nested for loops to compare each letter one by one
        {
            if (letter[i] == letter[j])
            {
                result = true;
                return result;
            }
        }
    }
    return result;
}