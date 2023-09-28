#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Orc with a heart of gold prompts user for name
    string name = get_string("What be yer stinkin name, human?\n");
    printf("Yer alright then, %s\n", name);
}