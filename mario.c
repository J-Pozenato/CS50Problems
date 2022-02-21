#include <cs50.h>
#include <stdio.h>

void repeat(char c, int count)  //repeats a char a number of times
{
    for (int i = 0; i < count; i++)
    {
        printf("%c", c);
    }


}

int main(void)
{
    int height = 0;


    while (height <= 0 || height > 8)    //check if the height is betwenn 1 and 9
    {
        height = get_int("Type the Height(1-9): ");
    }

    for (int i = 1; i <= height; i++)   //print the tower with the recieved height
    {
        repeat(' ', (height - i)); //print the left spaces
        repeat('#', i);   //print the left hashes
        repeat(' ', 2);   //print the middle spaces
        repeat('#', i);   //print the right hashes
        printf("\n"); //next line
    }
    return 0;

}




