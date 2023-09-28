#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    string word = get_string("Player 1: ");
    int score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {

        if (islower(word[i]))
        {
            int index = word[i] - 97;
            score = score + POINTS[index];
        }
        else if (isupper(word[i]))
        {
            int index = word[i] - 65;
            score = score + POINTS[index];
        }
    }
    printf("score:%i\n", score);
}