#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float m = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0f;
            int shade = nearbyintf(m);

            // set the shade of grey equivalent to the color
            image[i][j].rgbtRed = shade;
            image[i][j].rgbtGreen = shade;
            image[i][j].rgbtBlue = shade;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0, n = (width/2); j < n; j++)
        {
            // take the last pixel in the row and copy to the first
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
    // create the new image
    RGBTRIPLE blured[height][width];
    double avgR, avgG, avgB;
    int count;


    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            {
                avgR = avgG = avgB = count = 0;
                // check the 3x3 matrix with [i][j] in the center
                for (int row = i - 1; row <= i + 1; row++)
                {
                    for (int col = j - 1; col <= j +1; col++)
                    {
                        // if the row or column are outside outside of the image boundary don't increase de values
                        if ((row >= 0 && row < height) && (col >= 0 && col < width) )
                        {
                            avgR += image[row][col].rgbtRed;
                            avgG += image[row][col].rgbtGreen;
                            avgB += image[row][col].rgbtBlue;
                            count++;
                        }
                    }
                }

                if(count != 0)  // just checking if anything went wrong to never divide by zero
                {
                    // calculate and round the averages
                    avgR = round(avgR/count);
                    avgG = round(avgG/count); //initialy I was using nearbyintf() but it was returning a number diferent from the check50
                    avgB = round(avgB/count);
                    // create the new pixel in the temporary image
                    blured[i][j].rgbtRed = avgR;
                    blured[i][j].rgbtGreen = avgG;
                    blured[i][j].rgbtBlue = avgB;
                }


            }
    }
    // sending the temporary image value to the output image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blured[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // create the new image a copying the original image to it

    RGBTRIPLE border[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            border[i][j] = image[i][j];
        }
    }

    double GxR, GyR, GxG, GyG, GxB, GyB;
    int GfinalR, GfinalG, GfinalB, multX, multY;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            {
                GxR = GxG = GxB = GyR = GyG = GyB = 0;

                // check the 3x3 matrix with [i][j] in the center
                for (int row = i - 1; row <= i + 1; row++)
                {
                    int nRow = row - i;

                    for (int col = j - 1; col <= j +1; col++)
                    {
                        int nCol = col - j;

                        // if the row or column are outside outside of the image boundary don't increase de values
                        if ((row >= 0 && row < height) && (col >= 0 && col < width) )
                        {

                            // creating all cases of the matrix Gx = [-1  0  1]  and  Gy = [-1  -2  -1]
                            switch (nRow)                     //     [-2  0  2]  and       [ 0   0   0]
                            {                                 //     [-1  0  1]  and       [ 1   2   1]
                                // Up
                                case -1:
                                    switch (nCol)
                                    {
                                        // left
                                        case -1:
                                            multX = -1;
                                            multY = -1;
                                            break;

                                        // mid
                                        case 0:
                                            multX = 0;
                                            multY = -2;
                                            break;

                                        // right
                                        case 1:
                                            multX = 1;
                                            multY = -1;
                                            break;
                                    }
                                    break;

                                // Mid
                                case 0:
                                    switch (nCol)
                                    {
                                        // left
                                        case -1:
                                            multX = -2;
                                            multY = 0;
                                            break;

                                        // mid
                                        case 0:
                                            multX = 0;
                                            multY = 0;
                                            break;

                                        // right
                                        case 1:
                                            multX = 2;
                                            multY = 0;
                                            break;
                                    }
                                    break;

                                // Down
                                case 1:
                                    switch (nCol)
                                    {
                                        // left
                                        case -1:
                                            multX = -1;
                                            multY = 1;
                                            break;

                                        // mid
                                        case 0:
                                            multX = 0;
                                            multY = 2;
                                            break;

                                        // right
                                        case 1:
                                            multX = 1;
                                            multY = 1;
                                            break;
                                    }
                                    break;
                            }
                            //for every iteration of the 3x3 matrix add the value of Gx and Gy
                            GxR += multX * image[row][col].rgbtRed;
                            GxG += multX * image[row][col].rgbtGreen;
                            GxB += multX * image[row][col].rgbtBlue;
                            GyR += multY * image[row][col].rgbtRed;
                            GyG += multY * image[row][col].rgbtGreen;
                            GyB += multY * image[row][col].rgbtBlue;


                         }




                    }
                }
                    // final value for the colors of the middle pixel
                    GfinalR = round(sqrt(GxR*GxR + GyR*GyR));
                    GfinalG = round(sqrt(GxG*GxG + GyG*GyG));
                    GfinalB = round(sqrt(GxB*GxB + GyB*GyB));

                    // create the new pixel in the temporary image
                    if (GfinalR > 255)
                    {
                        border[i][j].rgbtRed = 255;
                    }
                    else
                    {
                        border[i][j].rgbtRed = GfinalR;
                    }

                    if (GfinalG > 255)
                    {
                        border[i][j].rgbtGreen = 255;
                    }
                    else
                    {
                        border[i][j].rgbtGreen = GfinalG;
                    }

                    if (GfinalB > 255)
                    {
                        border[i][j].rgbtBlue = 255;
                    }
                    else
                    {
                        border[i][j].rgbtBlue = GfinalB;
                    }



            }
    }
    // sending the temporary image value to the output image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = border[i][j];
        }
    }

    return;
}
