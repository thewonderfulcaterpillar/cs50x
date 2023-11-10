#include <cs50.h>
#include <stdio.h>
int getLevel(void);

int main(void)
{
    int level = getLevel();
    for (int i = 1; i < level+1; i++){

        for (int a = 0; a < (level-i); a ++)
        {
            printf (" ");
        }

        for (int b = 0; b < (i); b ++)
        {
            printf ("#");
        }
        printf ("  ");
        for (int c = 0; c < (i); c ++)
        {
            printf ("#");
        }
        printf("\n");
    }


    return 0;
}

int getLevel(void)
{
    int x = 0;
    while (x>8 || x<=0)
        {
            x = get_int("Enter a number from 1 to 8:");}
    return x;
}