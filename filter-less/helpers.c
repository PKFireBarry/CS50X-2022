#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gs = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/ 3.0);
            image[i][j].rgbtRed = gs;
            image[i][j].rgbtGreen = gs;
            image[i][j].rgbtBlue = gs;
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

            //sepia formula
            //sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
            //sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
            //sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlu
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;


            // Convert image to sepia
            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            int sepiaGreen = round (.349 * red + .686 * green + .168 * blue);
            int sepiaBlue = round (.272 * red + .534 * green + .131 * blue);

            //if values are above threshold then reduce to 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            //updated values
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
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tmp;
        }
    }
    return;
}
// Blur image

void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r, b, g;
            r = 0;
            b = 0;
            g = 0;
            float count = 0.00;

            //getting the pixel values
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentx = i + x;
                    int currenty = j + y;

                    //check boarder pixels
                    if (currentx < 0 || currentx >= (height -1) || currenty < 0 || currenty >= (width -1))
                    {
                        continue;
                    }
                    //get pixel values
                    r += image[currentx][currenty].rgbtRed;
                    b += image[currentx][currenty].rgbtBlue;
                    g += image[currentx][currenty].rgbtGreen;

                    count++;
                }

                //getting the average of pixels

                tmp[i][j].rgbtRed = round(r / count);
                tmp[i][j].rgbtBlue = round(b / count);
                tmp[i][j].rgbtGreen = round(g / count);
            }
        }
    }

    //copy the pixels to the output from the tmp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
        }

    }
   return;
}