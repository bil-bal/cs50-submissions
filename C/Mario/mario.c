#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n = 0;
    do 
    {
        n = get_int("Height: ");
    } 
    while (n < 1 || n > 8);

    for (int j = 1; j < n + 1; j++) 
    {
        int k = n - j;
        while (k != 0) 
        {
            printf(" ");
            k--;
        }

        int l = n - (n - j);
        while (l != 0) 
        {
            printf("#");
            l--;
        }
        printf("  ");

        int c = n - (n - j);
        while (c != 0) 
        {
            printf("#");
            c--;
        }

        printf("\n");
    }
        
}
