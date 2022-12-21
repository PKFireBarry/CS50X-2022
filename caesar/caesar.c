#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    int i, N = 0;

    //fail save for inputs
    //if argc is less that 2 or greater than 2 print below

    if (argc != 2)
    {
        printf("Usage: ./caesar.c Key\n");
        return 1;
    }
    else printf("the key is %s\n", argv[1]);

    printf("Checking Key in the cipher key.....\n");

    //checking argv[1] to make sure it only contains numbers

    for (i = 0 ; i < strlen(argv[1]) ; ++i)
    {
        if (!(argv[1][i] >= '0' && argv[1][i] <= '9'))
        {
            N = 1;
            break;
        }
    }

    if(N == 1)
    {
        printf("Key contains a char that isnt a number! FIX IT.\n");
    }
   else
    {
        printf("Key only contains numbers! NICE\n");
    }

    //converting argv[1] to a int

    int k = atoi(argv[1]);

    //getting the words to scrambble

    string plaintext = get_string("\n");
    printf("ciphertext: ");


    //implement letter shift corrisponding to key on each char(uppercase or lowercase)
    // (plaintext - 65 or 97 + key) %26

    for (int j = 0; j < strlen(plaintext); j++)
    {
        //printf(cirpertext)
        if(isupper(plaintext[j]))
        {
            printf("%c", (plaintext[j] - 65 + k) % 26 + 65);
        }

        else if (islower(plaintext[j]))
        {
            printf("%c", (plaintext[j] - 97 + k) % 26 + 97);
        }

        else
        {
            printf("%c", plaintext[j]);
        }
    }
    printf("\n");

    return 0;
}














