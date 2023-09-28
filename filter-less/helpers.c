#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each pixel with nested loops
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Average RGB values to a float
            float gryscl = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;

            // Round off average to an int
            int grysclR = round(gryscl);

            // Assign final greyscale value back to image RGB
            image[i][j].rgbtBlue = grysclR;
            image[i][j].rgbtGreen = grysclR;
            image[i][j].rgbtRed = grysclR;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each pixel with nested loops
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Assign RGB values to shorter names and get released from BYTE's 8 bit restriction.
            // These values need to go beyond 8 bits and not wrap around in order for the later
            // if conditionals to work.
            float b = image[i][j].rgbtBlue;
            float g = image[i][j].rgbtGreen;
            float r = image[i][j].rgbtRed;

            // Run algorithm to determine sepia values and round off the sum
            int sepBl = round((.131 * b) + (.534 * g) + (.272 * r));
            int sepGr = round((.168 * b) + (.686 * g) + (.349 * r));
            int sepRd = round((.189 * b) + (.769 * g) + (.393 * r));

            // Ensure sepia values are not over 8 bits
            if (sepBl > 255)
            {
                sepBl = 255;
            }

            if (sepGr > 255)
            {
                sepGr = 255;
            }

            if (sepRd > 255)
            {
                sepRd = 255;
            }

            // Reassign new sepia values to image RGB
            image[i][j].rgbtBlue = sepBl;
            image[i][j].rgbtGreen = sepGr;
            image[i][j].rgbtRed = sepRd;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate through each row
    for (int i = 0; i < height; i++)
    {
        // Divide width in half and iteration stops there for the columns.
        // Ensures mirroring doesn't go back to original after halfway point.
        for (int j = 0; j < width / 2; j++)
        {
            // Create a temp for each color value
            int tempB;
            int tempG;
            int tempR;
            int jj = j + 1;

            // Switch pixels on horizontally opposite sides
            tempB = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - jj].rgbtBlue;
            image[i][width - jj].rgbtBlue = tempB;

            tempG = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - jj].rgbtGreen;
            image[i][width - jj].rgbtGreen = tempG;

            tempR = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - jj].rgbtRed;
            image[i][width - jj].rgbtRed = tempR;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy image to a temp 2D array
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
            // Average RGB values of 3x3 grid around pixel
            float averageB = 0;
            float averageG = 0;
            float averageR = 0;
            int pxl_counter = 0;

            // X and Y variables ensure it loops only three times
            for (int k = i - 1, x = 1; x < 4; x++, k++)
            {
                for (int l = j - 1, y = 1; y < 4; y++, l++)
                {
                    // Ensure out-of-bounds pixels are ignored
                    if (k < 0 || l < 0 || k > height - 1 || l > width - 1)
                    {
                        continue;
                    }
                    averageB += temp[k][l].rgbtBlue;
                    averageG += temp[k][l].rgbtGreen;
                    averageR += temp[k][l].rgbtRed;
                    pxl_counter++;
                }
            }
            // Round off values and write to image the new value
            // Determine value of divisor using counter
            int blurB = round(averageB / pxl_counter);
            int blurG = round(averageG / pxl_counter);
            int blurR = round(averageR / pxl_counter);

            image[i][j].rgbtBlue = blurB;
            image[i][j].rgbtGreen = blurG;
            image[i][j].rgbtRed = blurR;
        }
    }
    return;
}
