#include <stdio.h>
#include <math.h>
#include "helpers.h"


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take's each color and calculate average
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            int avrg = round((blue + green + red) / 3.0);

            // Set colors to an average value
            image[i][j].rgbtBlue = avrg;
            image[i][j].rgbtGreen = avrg;
            image[i][j].rgbtRed = avrg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Store each color
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            // Sepia formula
            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);

            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);

            // Set new color values
            if (sepiaBlue <= 255)
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }
            else
            {
                image[i][j].rgbtBlue = 255;
            }
            // Making sure color is in range
            if (sepiaGreen <= 255)
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }
            else
            {
                image[i][j].rgbtGreen = 255;
            }
            if (sepiaRed <= 255)
            {
                image[i][j].rgbtRed = sepiaRed;
            }
            else
            {
                image[i][j].rgbtRed = 255;
            }

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
            //Using temporary variable we swap places of pixels
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Making a copy of an image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    //First two for loops iterate over every pixel
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {
            // Temporary variables for each color
            int tempBlue = 0, tempGreen = 0, tempRed = 0;

            // Keeping count each time we add new pixel
            float count = 0.0;

            // Last two for loops iterate 9 pixels around original pixel
            for (int k = -1; k <= 1; k++)
            {
                for (int n = -1; n <= 1; n++)
                {
                    // Making sure we are not doing anything outside of an image height
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Making sure we are not doing anything outside of an image width
                    else if (j + n < 0 || j + n >= width)
                    {
                        continue;
                    }
                    else
                    {
                        tempBlue += image[i + k][j + n].rgbtBlue;
                        tempGreen += image[i + k][j + n].rgbtGreen;
                        tempRed += image[i + k][j + n].rgbtRed;
                        count ++;
                    }
                }
            }
            // Using formula to calculate blur
            copy[i][j].rgbtBlue = round(tempBlue / count);
            copy[i][j].rgbtGreen = round(tempGreen / count);
            copy[i][j].rgbtRed = round(tempRed / count);
        }
    }
    // Copy image back to original
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
