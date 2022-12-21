#include <stdio.h>
#include <string.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    // prompt the user for a string of text
    string s = get_string("Input Readability Text: ");

    // initialize variables for letters, words, and sentences
    int letters = 0;
    int words = 1;
    int sentences = 0;

    // count the number of letters, words, and sentences in the text
    for (int i = 0; i < strlen(s); i++)
    {
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
        {
            letters++;
        }
        else if (s[i] == ' ')
        {
            words++;
        }
        else if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }

    // compute the Coleman-Liau index
    float L = (float)letters / (float)words * 100;
    float S = (float)sentences / (float)words * 100;
    float CLI = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(CLI);

    // print the grade level
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

    return 0;
}