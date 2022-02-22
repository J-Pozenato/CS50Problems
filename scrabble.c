#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // checks which of the scores is higher then print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int compute_score(string word)
{


    int s;
    int count = 0;
    int i = 0;

    do   // Do Loop, while the score of the character is greater than 0
    {
        if (islower(word[i]))
        {
            s = POINTS[(word[i] - 97)];
        }
        else if (isupper(word[i]))
        {
            s = POINTS[(word[i] - 65)];
        }
        else
        {
            s = 0;  // When checking a character that isn't a letter returns 0 then exit the loop
        }

        i++;
        count += s;
    }
    while (s != 0);

    return count;
}
