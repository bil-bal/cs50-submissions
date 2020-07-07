#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }


    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);

    long fsize = ftell(file);

    fseek(file, 0, SEEK_SET);

    unsigned char *bytes = malloc(fsize);

    fread(bytes, fsize, 1, file);

    fclose(file);

    unsigned char buffer[512];

    int count = 0;

    int start = 0;

    char s[7] = "000.jpg";

    FILE *jpg;

    for (int i = 0; i < fsize / 512; i++)
    {
        memcpy(buffer, bytes + i * 512, 512);

        if (buffer[0] == 255 && buffer[1] == 216 && buffer[2] == 255 && (buffer[3] >= 224 || buffer[3] <= 255))
        {
            sprintf(s, "%03d.jpg", count);
            jpg = fopen(s, "a");
            count++;
            start = 1;
        }

        if (start == 1)
        {
            fwrite(&buffer, 1, 512, jpg);
        }
    }
}
