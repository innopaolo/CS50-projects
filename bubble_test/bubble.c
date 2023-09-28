#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x = 6;
    int numbers[] = {5, 2, 1, 3, 6, 4};
    int temp = 0;
    int counter = 0;

            for (int i = 0; i < x; i++)
            {
                for (int j = i + 0; j < x; j++)
                {
                    if (numbers[i] > numbers[j])
                    {
                        temp = numbers[i];
                        numbers[i] = numbers[j];
                        numbers[j] = temp;
                        counter += 1;
                    }
                }
                // No Swap
                if (counter == 0)
                    break;
                else
                    counter = 0;
            }

    for (int i = 0; i < 6; i++)
    {
        printf("%i", numbers[i]);
    }
    printf("\n");
}
