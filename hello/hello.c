#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //ask  them for a name
    string name = get_string("whats your name? ");
    //print hello + the name that was input
    printf("hello %s\n", name);
}