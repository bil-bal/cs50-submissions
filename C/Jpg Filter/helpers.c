#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg = round(((float) image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = width - 1, k = 0; j >= 0; j--, k++)
        {
            image_[i][k].rgbtBlue = image[i][j].rgbtBlue;
            image_[i][k].rgbtGreen = image[i][j].rgbtGreen;
            image_[i][k].rgbtRed = image[i][j].rgbtRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image_[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_[i][j].rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_[height][width];
    int count;
    int avg[] = {0, 0, 0};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            count = 0;
            avg[0] = 0;
            avg[1] = 0;
            avg[2] = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k >= height || j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    else
                    {
                        avg[0] += image[i + k][j + l].rgbtBlue;
                        avg[1] += image[i + k][j + l].rgbtGreen;
                        avg[2] += image[i + k][j + l].rgbtRed;
                        count++;
                    }
                }

            }
            //printf("%d\n", count);
            image_[i][j].rgbtBlue = round((float) avg[0] / count);
            image_[i][j].rgbtGreen = round((float) avg[1] / count);
            image_[i][j].rgbtRed = round((float) avg[2] / count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image_[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_[height][width];

    int avg[] = {0, 0, 0, 0, 0, 0};

    int red = 0;
    int blue = 0;
    int green = 0;

    int rx = 0;
    int gx = 0;
    int bx = 0;

    int ry = 0;
    int gy = 0;
    int by = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg[0] = 0;
            avg[1] = 0;
            avg[2] = 0;
            avg[3] = 0;
            avg[4] = 0;
            avg[5] = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i + k < 0 || i + k >= height || j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    else
                    {
                        if (k == -1 && l == -1)
                        {
                            avg[0] += (image[i + k][j + l].rgbtBlue * -1);
                            avg[1] += (image[i + k][j + l].rgbtGreen * -1);
                            avg[2] += (image[i + k][j + l].rgbtRed * -1);

                            avg[3] += (image[i + k][j + l].rgbtBlue * -1);
                            avg[4] += (image[i + k][j + l].rgbtGreen * -1);
                            avg[5] += (image[i + k][j + l].rgbtRed * -1);
                        }
                        else if (k == -1 && l == 0)
                        {
                            avg[0] += (image[i + k][j + l].rgbtBlue * 0);
                            avg[1] += (image[i + k][j + l].rgbtGreen * 0);
                            avg[2] += (image[i + k][j + l].rgbtRed * 0);

                            avg[3] += (image[i + k][j + l].rgbtBlue * -2);
                            avg[4] += (image[i + k][j + l].rgbtGreen * -2);
                            avg[5] += (image[i + k][j + l].rgbtRed * -2);
                        }
                        else if (k == -1 && l == 1)
                        {
                            avg[0] += (image[i + k][j + l].rgbtBlue * 1);
                            avg[1] += (image[i + k][j + l].rgbtGreen * 1);
                            avg[2] += (image[i + k][j + l].rgbtRed * 1);

                            avg[3] += (image[i + k][j + l].rgbtBlue * -1);
                            avg[4] += (image[i + k][j + l].rgbtGreen * -1);
                            avg[5] += (image[i + k][j + l].rgbtRed * -1);
                        }
                        else if (k == 0 && l == -1)
                        {
                            avg[0] += (image[i + k][j + l].rgbtBlue * -2);
                            avg[1] += (image[i + k][j + l].rgbtGreen * -2);
                            avg[2] += (image[i + k][j + l].rgbtRed * -2);

                            avg[3] += (image[i + k][j + l].rgbtBlue * 0);
                            avg[4] += (image[i + k][j + l].rgbtGreen * 0);
                            avg[5] += (image[i + k][j + l].rgbtRed * 0);
                        }
                        else if (k == 0 && l == 0)
                        {
                            avg[0] += (image[i + k][j + l].rgbtBlue * 0);
                            avg[1] += (image[i + k][j + l].rgbtGreen * 0);
                            avg[2] += (image[i + k][j + l].rgbtRed * 0);

                            avg[3] += (image[i + k][j + l].rgbtBlue * 0);
                            avg[4] += (image[i + k][j + l].rgbtGreen * 0);
                            avg[5] += (image[i + k][j + l].rgbtRed * 0);
                        }
                        else if (k == 0 && l == 1)
                        {
                            avg[0] += (image[i + k][j + l].rgbtBlue * 2);
                            avg[1] += (image[i + k][j + l].rgbtGreen * 2);
                            avg[2] += (image[i + k][j + l].rgbtRed * 2);

                            avg[3] += (image[i + k][j + l].rgbtBlue * 0);
                            avg[4] += (image[i + k][j + l].rgbtGreen * 0);
                            avg[5] += (image[i + k][j + l].rgbtRed * 0);
                        }
                        else if (k == 1 && l == -1)
                        {
                            avg[0] += (image[i + k][j + l].rgbtBlue * -1);
                            avg[1] += (image[i + k][j + l].rgbtGreen * -1);
                            avg[2] += (image[i + k][j + l].rgbtRed * -1);

                            avg[3] += (image[i + k][j + l].rgbtBlue * 1);
                            avg[4] += (image[i + k][j + l].rgbtGreen * 1);
                            avg[5] += (image[i + k][j + l].rgbtRed * 1);
                        }
                        else if (k == 1 && l == 0)
                        {
                            avg[0] += (image[i + k][j + l].rgbtBlue * 0);
                            avg[1] += (image[i + k][j + l].rgbtGreen * 0);
                            avg[2] += (image[i + k][j + l].rgbtRed * 0);

                            avg[3] += (image[i + k][j + l].rgbtBlue * 2);
                            avg[4] += (image[i + k][j + l].rgbtGreen * 2);
                            avg[5] += (image[i + k][j + l].rgbtRed * 2);
                        }
                        else if (k == 1 && l == 1)
                        {
                            avg[0] += (image[i + k][j + l].rgbtBlue * 1);
                            avg[1] += (image[i + k][j + l].rgbtGreen * 1);
                            avg[2] += (image[i + k][j + l].rgbtRed * 1);

                            avg[3] += (image[i + k][j + l].rgbtBlue * 1);
                            avg[4] += (image[i + k][j + l].rgbtGreen * 1);
                            avg[5] += (image[i + k][j + l].rgbtRed * 1);
                        }
                    }
                }
            }

            bx = avg[0];
            gx = avg[1];
            rx = avg[2];

            by = avg[3];
            gy = avg[4];
            ry = avg[5];

            blue = round(sqrt(bx * bx + by * by));
            green = round(sqrt(gx * gx + gy * gy));
            red = round(sqrt(rx * rx + ry * ry));

            if (blue > 255)
            {
                image_[i][j].rgbtBlue = 255;
            }
            else
            {
                image_[i][j].rgbtBlue = blue;
            }
            if (green > 255)
            {
                image_[i][j].rgbtGreen = 255;
            }
            else
            {
                image_[i][j].rgbtGreen = green;
            }
            if (red > 255)
            {
                image_[i][j].rgbtRed = 255;
            }
            else
            {
                image_[i][j].rgbtRed = red;
            }

        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = image_[i][j].rgbtBlue;
            image[i][j].rgbtGreen = image_[i][j].rgbtGreen;
            image[i][j].rgbtRed = image_[i][j].rgbtRed;
        }
    }

    return;
}
