#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average and round off the RGB values
            float gryscl = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            int x = round(gryscl / 3.0);

            image[i][j].rgbtBlue = x;
            image[i][j].rgbtGreen = x;
            image[i][j].rgbtRed = x;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Create temp to switch pixels
            // JJ variable because j starts at 0
            RGBTRIPLE temp[height][width];
            int jj = j + 1;

            temp[i][j] = image[i][j];
            image[i][j] = image[i][width - jj];
            image[i][width - jj] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Copy image to use unchanged RGB values for equations
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average variables to be updated by 3x3 grid around each pixel
            float averageB = 0;
            float averageG = 0;
            float averageR = 0;
            int counter = 0;

            // 3x3 grid
            for (int k = i - 1, x = 1; x < 4; x++, k++)
            {
                for (int l = j - 1, y = 1; y < 4; y++, l++)
                {
                    // Ensure pixels outside the grid are not included
                    if (k < 0 || l < 0 || k > height - 1 || l > width - 1)
                    {
                        continue;
                    }
                    averageB += temp[k][l].rgbtBlue;
                    averageG += temp[k][l].rgbtGreen;
                    averageR += temp[k][l].rgbtRed;
                    counter++;
                }
            }
            // Round off value with counter as divisor
            int blurB = round(averageB / counter);
            int blurG = round(averageG / counter);
            int blurR = round(averageR / counter);

            image[i][j].rgbtBlue = blurB;
            image[i][j].rgbtGreen = blurG;
            image[i][j].rgbtRed = blurR;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy for equations
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Iterate through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize Gx, Gy, and kernels
            float GxB = 0;
            float GxG = 0;
            float GxR = 0;

            float GyB = 0;
            float GyG = 0;
            float GyR = 0;

            int X[] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
            int Y[] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };

            int counter = 0;

            // S and T to ensure 3 loops
            for (int k = i - 1, s = 0; s < 3; s++, k++)
            {
                for (int l = j - 1, t = 0; t < 3; t++, l++)
                {
                    // Sum of Gx and Gy values
                    if (k >= 0 && l >= 0 && k < height && l < width)
                    {
                        GxB += X[counter] * (temp[k][l].rgbtBlue);
                        GxG += X[counter] * (temp[k][l].rgbtGreen);
                        GxR += X[counter] * (temp[k][l].rgbtRed);

                        GyB += Y[counter] * (temp[k][l].rgbtBlue);
                        GyG += Y[counter] * (temp[k][l].rgbtGreen);
                        GyR += Y[counter] * (temp[k][l].rgbtRed);
                    }
                    counter++;
                }
            }
            // Round off the kernel convolution
            int edgeB = round(sqrt((GxB * GxB) + (GyB * GyB)));
            int edgeG = round(sqrt((GxG * GxG) + (GyG * GyG)));
            int edgeR = round(sqrt((GxR * GxR) + (GyR * GyR)));

            if (edgeB > 255)
            {
                edgeB = 255;
            }
            if (edgeG > 255)
            {
                edgeG = 255;
            }
            if (edgeR > 255)
            {
                edgeR = 255;
            }

            image[i][j].rgbtBlue = edgeB;
            image[i][j].rgbtGreen = edgeG;
            image[i][j].rgbtRed = edgeR;
        }
    }
    return;
}