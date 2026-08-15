#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            int average =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Update pixel values
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
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
            // Compute red sepia values
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                 .189 * image[i][j].rgbtBlue);
            // For certain colors, the formula can result in a number greater than the max value for
            // an 8-bit color, so you cap it at 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            // compute green sepia values
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                   .168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            // compute blue sepia values
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                  .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // update pixel values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
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
            // swap each pixel with its corresponding pixel on the other side of the row
            int copy_red = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = copy_red;

            int copy_green = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = copy_green;

            int copy_blue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = copy_blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // initilize a copy of image
    RGBTRIPLE copy[height][width];
    float red_sum = 0;
    float green_sum = 0;
    float blue_sum = 0;
    float count = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // creates a new copy of the image
            copy[i][j] = image[i][j];
        }
    }
    // loops over the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red_sum = 0;
            green_sum = 0;
            blue_sum = 0;
            count = 0;

            // loops over the neighboring pixels
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int m = j - 1; m <= j + 1; m++)
                {
                    // only if they are one column or one row away from the pixel
                    if (0 <= k && k < height && 0 <= m && m < width)
                    {
                        count++;
                        // add the values of pixels to sum
                        red_sum = red_sum + copy[k][m].rgbtRed;
                        green_sum = green_sum + copy[k][m].rgbtGreen;
                        blue_sum = blue_sum + copy[k][m].rgbtBlue;
                    }
                }
            }

            // finds the average in order to sucessfuly blur pixels
            red_sum = round(red_sum / count);
            green_sum = round(green_sum / count);
            blue_sum = round(blue_sum / count);

            // update pixel values
            image[i][j].rgbtRed = red_sum;
            image[i][j].rgbtGreen = green_sum;
            image[i][j].rgbtBlue = blue_sum;
        }
    }
    return;
}

// Edges (optional, more challenging)
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
// Artwork filter
void artwork(int height, int width, RGBTRIPLE image[height][width])
{
   // initilize a copy of image
    RGBTRIPLE copy[height][width];
    float red_sum = 0;
    float green_sum = 0;
    float blue_sum = 0;
    float count = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // creates a new copy of the image
            copy[i][j] = image[i][j];
        }
    }
    // loops over the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red_sum = 0;
            green_sum = 0;
            blue_sum = 0;
            count = 0;

            // loops over the neighboring pixels
            for (int k = i - 1; k <= i + 1; k++)
            {
                for (int m = j - 1; m <= j + 1; m++)
                {
                    // only if they are one column or one row away from the pixel
                    if (0 <= k && k < height && 0 <= m && m < width)
                    {
                        count++;
                        // add the values of pixels to sum
                        red_sum = red_sum + copy[k][m].rgbtRed;
                        green_sum = green_sum + copy[k][m].rgbtGreen;
                        blue_sum = blue_sum + copy[k][m].rgbtBlue;
                    }
                }
            }

            // finds the average in order to sucessfuly blur pixels
            red_sum = round(red_sum / count);
            green_sum = round(green_sum / count);
            blue_sum = round(blue_sum / count);

            // update pixel values
            image[i][j].rgbtRed = red_sum;
            image[i][j].rgbtGreen = green_sum;
            image[i][j].rgbtBlue = blue_sum;
        }
    }


    //daniel caesar filter
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int brightness = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3;
            if (brightness > 128)
            {
                int new_red = image[i][j].rgbtRed * 1.5;
                if (new_red > 255)
                {
                    image[i][j].rgbtRed = 255;
                }
                else
                {
                    image[i][j].rgbtRed = new_red;
                }

                int new_green = image[i][j].rgbtGreen * 1.5;
                if (new_green > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }
                else
                {
                    image[i][j].rgbtGreen = new_green;
                }
                int new_blue = image[i][j].rgbtBlue * 1.3;
                if (new_blue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = new_blue;
                }
            }
            else
            {
                image[i][j].rgbtRed = round(image[i][j].rgbtRed * 0.2);
                image[i][j].rgbtGreen = round(image[i][j].rgbtGreen * 0.2);
                int new_blue = round(image[i][j].rgbtBlue * 0.8 + 40);

                if (new_blue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
                else
                {
                    image[i][j].rgbtBlue = new_blue;
                }
            }

        }
    }
    return;
}
