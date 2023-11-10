#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i<height; i++){
        for (int j = 0; j<width;j++){
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;
            int gray = (round)((r + g + b) / 3.0);
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i<height; i++){
        for (int j = 0; j<width/2;j++){
            RGBTRIPLE temp  = image[i][j];
            image[i][j]=image[i][width-j-1];
            image[i][width-j-1]=temp;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width];
    for (int i = 0; i<height; i++){
        for (int j = 0; j<width;j++){
            int newGreen = 0;
            int newRed = 0;
            int newBlue= 0;
            float count = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if ( (0 <= i + x && i + x < height) && (0 <= j + y && j + y < width)) {

                        newGreen+=image[x+i][j+y].rgbtGreen;
                        newBlue+=image[x+i][j+y].rgbtBlue;
                        newRed+=image[x+i][j+y].rgbtRed;
                        count++;
                    }
                }
            }
            tempImage[i][j].rgbtRed = (round)(newRed/count);
            tempImage[i][j].rgbtGreen =(round) (newGreen/count);
            tempImage[i][j].rgbtBlue = (round)(newBlue/count);

        }
    }
    for (int i = 0; i<height; i++){
        for (int j = 0; j<width;j++){
            image[i][j]=tempImage[i][j];
        }}
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width];
    int gX[3][3]={{-1,0,1},{-2,0,2},{-1,0,1}};

    int gY[3][3]={{-1,-2,-1},{0,0,0},{1,2,1}};

    for (int i = 0; i<height; i++){
        for (int j = 0; j<width;j++){
            int yGreen = 0;
            int yRed = 0;
            int yBlue= 0;
            int xGreen = 0;
            int xRed = 0;
            int xBlue= 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if ( (0 <= i + x && i + x < height) && (0 <= j + y && j + y < width)) {
                        xGreen+=image[x+i][j+y].rgbtGreen*gX[x+1][y+1];
                        xBlue+=image[x+i][j+y].rgbtBlue*gX[x+1][y+1];
                        xRed+=image[x+i][j+y].rgbtRed*gX[x+1][y+1];
                        yGreen+=image[x+i][j+y].rgbtGreen*gY[x+1][y+1];
                        yBlue+=image[x+i][j+y].rgbtBlue*gY[x+1][y+1];
                        yRed+=image[x+i][j+y].rgbtRed*gY[x+1][y+1];
                    }
                }
            }

            tempImage[i][j].rgbtRed = ((round)(sqrt(xRed * xRed + yRed * yRed)) <= 255) ? (round)(sqrt(xRed * xRed + yRed * yRed)) : 255;
            tempImage[i][j].rgbtGreen = ((round)(sqrt(xGreen * xGreen + yGreen * yGreen)) <= 255) ? (round)(sqrt(xGreen * xGreen + yGreen * yGreen)) : 255;
            tempImage[i][j].rgbtBlue = ((round)(sqrt(xBlue * xBlue + yBlue * yBlue)) <= 255) ? (round)(sqrt(xBlue * xBlue + yBlue * yBlue)) : 255;


        }
    }
    for (int i = 0; i<height; i++){
        for (int j = 0; j<width;j++){
            image[i][j]=tempImage[i][j];
        }}
    return;
}
