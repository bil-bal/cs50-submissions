#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int count = 0;

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if ((argv[1][i] >= 65 && argv[1][i] <= 90) || (argv[1][i] >= 97 && argv[1][i] <= 122))
        {
            count += 1;
        }
        else
        {
            return 1;
        }

    }

    if (count != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        for (int j = i + 1; j < strlen(argv[1]); j++)
        {
            if (argv[1][i] == argv[1][j] && argv[1][i] != ' ')
            {
                return 1;
            }
        }
    }


    string s = get_string("plaintext: ");
    int size = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        size += 1;
    }

    char str[size + 1];

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= 65 && s[i] <= 90)
        {
            str[i] = toupper(argv[1][s[i] - 65]);
        }
        else if (s[i] >= 97 && s[i] <= 122)
        {
            str[i] = tolower(argv[1][s[i] - 97]);
        }
        else
        {
            str[i] = s[i];
        }
    }
    str[size] = '\0';

    printf("ciphertext: %s\n", (string) str);

    return 0;
}

