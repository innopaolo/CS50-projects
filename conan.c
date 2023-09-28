#include <stdio.h>
#include <string.h>

int main(void)
{
    char x[200];
    printf("What is best in life?\n");
    fgets(x, 200, stdin);

    char *y = "To crush your enemies, see them driven before you, "
              "and hear the lamentation of their women.\n";

    if (strcmp(x, y) == 0)
    {
        printf("That is good!\n");
    }
    else
    {
        printf("Wrong!\n");
    }
    return 0;
}