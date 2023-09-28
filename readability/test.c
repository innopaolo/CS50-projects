#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);


int main(void)
{

    // Get values for words, sentences, and letters
    string text = get_string("Text: ");
    int lcount = count_letters(text);
    int wcount = count_words(text);
    int scount = count_sentences(text);


    // Calculate Coleman-Liau index
    float fart = wcount / 1.0;
    float L = lcount / fart * 100.0;
    float S = scount / fart * 100.0;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    printf("%i %i %i\n", lcount, wcount, scount);
    printf("%f\n", L);
    printf("%f\n", S);
    printf("%i\n", index);
}






int count_letters(string text)
{
    int count = 0;

    // Count letters
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text [i] < 123)) // Exclude spaces and special chars using ASCII values
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 1;

    // Count letters
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32) // Count spaces using its ASCII value 32 + variable starts at 1 (last word = no space!)
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;

    // Count sentences
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63) // ASCII values for ?, ! and period.
        {
            count++;
        }
    }
    return count;
}