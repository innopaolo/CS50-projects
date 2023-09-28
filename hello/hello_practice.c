#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char name[50];
    printf("whats your name? ");
    scanf("%s", name);
    printf("%s, eh? sounds like a wanker\n", name);
    sleep(2);
    printf("now away with ye, ");
    sleep(1);
    printf("i gots some ladies that needs some polishin");

    for (int i = 0; i < 4; i++)
    {
        sleep(1);
        printf(".");
    }

    printf("\n");
}