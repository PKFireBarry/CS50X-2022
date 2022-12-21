#include <cs50.h>
#include <stdio.h>


int main(void)
{

    int n;
    do
    {
//get input from the user
        n = get_int("How high is the stack of blocks (1-8 ONLY)? \n");
    }
    //check input is or is not between 1<8
    while (n < 1 || n > 8);

//for each row
    for (int r = 0; r < n; r++)
    {
        for (int s = 0 ; s < n - r - 1 ; s++)
        {
            printf(" ");
        }
        for (int c = 0 ; c <= r; c++)
        {
            printf("#");
        }
//add a space
        printf("\n");
    }





}