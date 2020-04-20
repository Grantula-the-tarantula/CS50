#include "helpers.h"
#include <stdio.h>
#include <math.h>

int intmax(double n);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Loop through image from top left to bottom right (row by row)
    for (int i = 0; i < height; i++)
    {
        //Get color values from RGBTRIPLE, Calculate Average, and Change RGB to average
        for (int j = 0; j < width; j++)
        {
            int avg = round(((float) image[i][j].rgbtBlue + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtRed) / 3);

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
    //Loop through image from top left to bottom right (row by row)
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        //Take each pixel and swap it it with pixel on opposite side of image
        for (int j = 0; j < width / 2; j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    //Creates copy of image to use in calculation later
    RGBTRIPLE copyImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyImage[i][j] = image[i][j];
        }
    }

    //Iterate thought image pixel by pixel (top left to bottom right)
    //Checks for valid pixel on all sides (8 different options) + current pixel
    for (int i = 0, r, g, b; i < height; i++)
    {
        r = g = b = 0;
        float n = 0;

        for (int j = 0; j < width; j++)
        {
            r = g = b = n = 0;

            //Current Pixel
            if (i >= 0 && j >= 0)
            {
                r += copyImage[i][j].rgbtRed;
                g += copyImage[i][j].rgbtGreen;
                b += copyImage[i][j].rgbtBlue;
                n++;
            }
            //Left Pixel
            if (i >= 0 && j - 1 >= 0)
            {
                r += copyImage[i][j - 1].rgbtRed;
                g += copyImage[i][j - 1].rgbtGreen;
                b += copyImage[i][j - 1].rgbtBlue;
                n++;
            }
            //Right Pixel
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                r += copyImage[i][j + 1].rgbtRed;
                g += copyImage[i][j + 1].rgbtGreen;
                b += copyImage[i][j + 1].rgbtBlue;
                n++;
            }
            //Above Pixel
            if (i - 1 >= 0 && j >= 0)
            {
                r += copyImage[i - 1][j].rgbtRed;
                g += copyImage[i - 1][j].rgbtGreen;
                b += copyImage[i - 1][j].rgbtBlue;
                n++;
            }
            //Below Pixel
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                r += copyImage[i + 1][j].rgbtRed;
                g += copyImage[i + 1][j].rgbtGreen;
                b += copyImage[i + 1][j].rgbtBlue;
                n++;
            }
            //Diag Lower Right Pixel
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                r += copyImage[i + 1][j + 1].rgbtRed;
                g += copyImage[i + 1][j + 1].rgbtGreen;
                b += copyImage[i + 1][j + 1].rgbtBlue;
                n++;
            }
            //Diag Lower Left Pixel
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                r += copyImage[i + 1][j - 1].rgbtRed;
                g += copyImage[i + 1][j - 1].rgbtGreen;
                b += copyImage[i + 1][j - 1].rgbtBlue;
                n++;
            }
            //Diag Upper Right Pixel
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                r += copyImage[i - 1][j + 1].rgbtRed;
                g += copyImage[i - 1][j + 1].rgbtGreen;
                b += copyImage[i - 1][j + 1].rgbtBlue;
                n++;
            }
            //Diag Upper Left Pixel
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                r += copyImage[i - 1][j - 1].rgbtRed;
                g += copyImage[i - 1][j - 1].rgbtGreen;
                b += copyImage[i - 1][j - 1].rgbtBlue;
                n++;
            }

            //Assign final value to pixel
            //variable n is a float to remove rounding error
            image[i][j].rgbtRed = round(r / n);
            image[i][j].rgbtGreen = round(g / n);
            image[i][j].rgbtBlue = round(b / n);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    //Creates copy of image to use in calculation later
    RGBTRIPLE copyImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copyImage[i][j] = image[i][j];
        }
    }

    //Iterate thought image pixel by pixel (top left to bottom right)
    //Checks for valid pixel on all sides (8 different options) + current pixel
    //Gx Matrix [-1 0  1]       Gy Matrix [-1 -2 -1]
    //          [-2 0 -2]                 [ 0  0  0]
    //          [-1 0  1]                 [ 1  2  1]

    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width; j++)
        {

            float gxr, gxg, gxb, gyr, gyg, gyb;
            gxr = gxg = gxb = gyr = gyg = gyb = 0;

            //Left Pixel
            if (i >= 0 && j - 1 >= 0)
            {
                gxr += copyImage[i][j - 1].rgbtRed * -2;
                gxg += copyImage[i][j - 1].rgbtGreen * -2;
                gxb += copyImage[i][j - 1].rgbtBlue * -2;

                //Gy of left pixel == 0

            }
            //Right Pixel
            if ((i >= 0 && j + 1 >= 0) && (i >= 0 && j + 1 < width))
            {
                gxr += copyImage[i][j + 1].rgbtRed * 2;
                gxg += copyImage[i][j + 1].rgbtGreen * 2;
                gxb += copyImage[i][j + 1].rgbtBlue * 2;

                //Gy of right pixel == 0

            }
            //Above Pixel
            if (i - 1 >= 0 && j >= 0)
            {
                //Gx of above pixel == 0

                gyr += copyImage[i - 1][j].rgbtRed * -2;
                gyg += copyImage[i - 1][j].rgbtGreen * -2;
                gyb += copyImage[i - 1][j].rgbtBlue * -2;

            }
            //Below Pixel
            if ((i + 1 >= 0 && j >= 0) && (i + 1 < height && j >= 0))
            {
                //Gx of Below Pixel == 0

                gyr += copyImage[i + 1][j].rgbtRed * 2;
                gyg += copyImage[i + 1][j].rgbtGreen * 2;
                gyb += copyImage[i + 1][j].rgbtBlue * 2;

            }
            //Diag Lower Right Pixel
            if ((i + 1 >= 0 && j + 1 >= 0) && (i + 1 < height && j + 1 < width))
            {
                gxr += copyImage[i + 1][j + 1].rgbtRed * 1;
                gxg += copyImage[i + 1][j + 1].rgbtGreen * 1;
                gxb += copyImage[i + 1][j + 1].rgbtBlue * 1;

                gyr += copyImage[i + 1][j + 1].rgbtRed * 1;
                gyg += copyImage[i + 1][j + 1].rgbtGreen * 1;
                gyb += copyImage[i + 1][j + 1].rgbtBlue * 1;

            }
            //Diag Lower Left Pixel
            if ((i + 1 >= 0 && j - 1 >= 0) && (i + 1 < height && j - 1 >= 0))
            {
                gxr += copyImage[i + 1][j - 1].rgbtRed * -1;
                gxg += copyImage[i + 1][j - 1].rgbtGreen * -1;
                gxb += copyImage[i + 1][j - 1].rgbtBlue * -1;

                gyr += copyImage[i + 1][j - 1].rgbtRed * 1;
                gyg += copyImage[i + 1][j - 1].rgbtGreen * 1;
                gyb += copyImage[i + 1][j - 1].rgbtBlue * 1;

            }
            //Diag Upper Right Pixel
            if ((i - 1 >= 0 && j + 1 >= 0) && (i - 1 >= 0 && j + 1 < width))
            {
                gxr += copyImage[i - 1][j + 1].rgbtRed * 1;
                gxg += copyImage[i - 1][j + 1].rgbtGreen * 1;
                gxb += copyImage[i - 1][j + 1].rgbtBlue * 1;

                gyr += copyImage[i - 1][j + 1].rgbtRed * -1;
                gyg += copyImage[i - 1][j + 1].rgbtGreen * -1;
                gyb += copyImage[i - 1][j + 1].rgbtBlue * -1;

            }
            //Diag Upper Left Pixel
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                gxr += copyImage[i - 1][j - 1].rgbtRed * -1;
                gxg += copyImage[i - 1][j - 1].rgbtGreen * -1;
                gxb += copyImage[i - 1][j - 1].rgbtBlue * -1;

                gyr += copyImage[i - 1][j - 1].rgbtRed * -1;
                gyg += copyImage[i - 1][j - 1].rgbtGreen * -1;
                gyb += copyImage[i - 1][j - 1].rgbtBlue * -1;

            }

            //Calculate final Gx and Gy values for each pixel and assign color to pixel

            image[i][j].rgbtRed = (int) intmax(sqrt((gxr * gxr) + (gyr * gyr)));
            image[i][j].rgbtGreen = (int) intmax(sqrt((gxg * gxg) + (gyg * gyg)));
            image[i][j].rgbtBlue = (int) intmax(sqrt((gxb * gxb) + (gyb * gyb)));

        }
    }

    return;
}

int intmax(double n)
{
    int output = 0;

    if (n >= 255)
    {
        output = 255;
    }
    else if (n < 0)
    {
        output = 0;
    }
    else
    {
        output = (int) round(n);
    }
    return (output);
}
