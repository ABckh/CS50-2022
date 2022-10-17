#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtRed + 
                          image[i][j].rgbtGreen + 
                          image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sum_red, sum_green, sum_blue, counter;
            sum_red = sum_green = sum_blue = counter = 0;

            for (int k = -1; k < 2; k++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }
                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }
                    sum_red += image[i + k][j + c].rgbtRed;
                    sum_green += image[i + k][j + c].rgbtGreen;
                    sum_blue += image[i + k][j + c].rgbtBlue;
                    counter++;
                }   
            }
            image[i][j].rgbtRed = round(sum_red / counter);
            image[i][j].rgbtGreen = round(sum_green / counter);
            image[i][j].rgbtBlue = round(sum_blue / counter);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float x_red, x_green, x_blue, y_red, y_green, y_blue;
            x_red = x_green = x_blue = y_red = y_green = y_blue =  0;
            
            for (int k = -1; k < 2; k++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }
                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }
                    x_red += temp[i + k][j + c].rgbtRed * gx[k + 1][c + 1];
                    x_green += temp[i + k][j + c].rgbtGreen * gx[k + 1][c + 1]; 
                    x_blue += temp[i + k][j + c].rgbtBlue * gx[k + 1][c + 1];

                    y_red += temp[i + k][j + c].rgbtRed * gy[k + 1][c + 1];
                    y_green += temp[i + k][j + c].rgbtGreen * gy[k + 1][c + 1];
                    y_blue += temp[i + k][j + c].rgbtBlue * gy[k + 1][c + 1];
                }
            }
            int red = round(sqrt(x_red * x_red + y_red * y_red));
            int green = round(sqrt(x_green * x_green + y_green * y_green));
            int blue = round(sqrt(x_blue * x_blue + y_blue * y_blue));

            if (red > 255)
                red = 255;
            if (green > 255)
                green = 255;
            if (blue > 255)
                blue = 255;

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
}
