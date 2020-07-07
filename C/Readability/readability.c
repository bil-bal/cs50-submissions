#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(void)
{
    int sentences = 0;
    int words = 1;
    int letters = 0;

    string s = get_string("Text: ");
    for (int i = 0; i < strlen(s);i++)
    {
        if (s[i] == 46 || s[i] == 63 || s[i] == 33)
        {
            sentences += 1;
        } else if (s[i] == 32)
        {
            words += 1;
        } else if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))
        {
            letters += 1;
        }
    }


    float S = ((float) sentences / words) * 100.0;

    float L = ((float) letters / words) * 100.0;

    float index = 0.0588 * L -0.296 * S - 15.8;

    float ti = index - (int) index;

    if (ti < 0.5)
    {
        index = ceil(index - 0.5);
    } else if (ti >= 0.5)
    {
        index = ceil(index);
    }
    if ((int) index < 1)
    {
        printf("Before Grade 1\n");
    } else if ((int) index > 16)
    {
        printf("Grade 16+\n");
    } else
    {
        printf("Grade %d\n", (int) index);
    }

}