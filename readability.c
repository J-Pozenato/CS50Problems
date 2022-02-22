#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

int countLetters(string text);
int countWords(string text);
int countSentences(string text);

int main(void)
{
    float index;

    string text = get_string("Text: ");
    // printf("%s\n", text);
    float letters = countLetters(text);
    float words = countWords(text);
    float sentences = countSentences(text);

    float L = 100 * (letters/words);
    float S = 100 * (sentences/words);

    index = 0.0588 * L - 0.296 * S - 15.8;
    int rIndex = round(index);

    if (rIndex < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (rIndex > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", rIndex);
    }



}

int countLetters(string text)
{
    int i = 0;
    int n = 0;

    do
    {
        if (isalpha(text[i]))   //checks for letters then count
        {
            n++;
        }

        i++;
    }
    while (text[i] != 0); // when it reaches the end of the array Stop the loop

    return n;
}

int countWords(string text)
{
    int i = 0;
    int n = 1;

    do
    {       // Checks for spaces then count a word
        if (text[i] == 32)
        {   // ASCII. 32 == space
            n++;
        }

        i++;
    }
    while (text[i] != 0);

    return n;
}

int countSentences(string text)
{
    int i = 0;
    int n = 0;

    do
    {   // Checks for "." , "?" or "!" then count a sentence
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {   // ASCII 33 == !, 63 == ?, 46 == .
            n++;
        }

        i++;
    }
    while (text[i] != 0);

    return n;
}