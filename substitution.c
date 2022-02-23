#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#define _GNU_SOURCE
#include <string.h>

bool checkKey(string keytext);
void cipher(string text, string keyTest);

int main(int argc, string argv[])
{
    char key[26];
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }

    strcpy(key, argv[1]);   //store key in a diferent memory place
    //while i was testing everythin i did to variables with de value of argv[1] changed its value too, it was a nightmare


    //  printf("\n%s\n", argv[1]);
    //printf("%s\n", key);

    if (!checkKey(argv[1]))
    {
        return 1;
    }

    //printf("%s\n", argv[1]);
    //printf("%s\n", key);

    string plain = get_string("plaintext: ");


    cipher(plain, key); //function to chenge the written message
    return 0;

}


bool checkKey(string keytext) //function which checks if the key is valid
{
    int strl = strlen(keytext);


    if (strl != 26) //checking the key size
    {
        printf("\nKey must contain 26 characters.");
        return false;
    }
    string sortText = keytext;
    int temp = 0;
    string copy = keytext;

    for (int i = 0; i < strl; i++)  //setting it all to uppercase
    {
        keytext[i] = toupper(keytext[i]);
    }

    for (int i = 0; i < strl; i++)  //sorting the key by alphabetical order then checking for repeated letters
    {
        for (int j = i + 1; j < strl; j++)
        {
            if (copy[i] > sortText[j])
            {
                temp = sortText[i];
                sortText[i] = sortText[j];
                sortText[j] = temp;
            }
        }
    }

    for (int i = 0; i < strl; i++)
    {
        int a = 65 + i;
        int b = 97 + i;

        if (sortText[i] != a && sortText[i] != b)
        {

            return false;
        }
    }
    return true;


}

void cipher(string text, string keyTest)
{

    for (int i = 0; i < strlen(text); i++)
    {
        if (islower(text[i]))
        {
            // use lowercase version of cipher
            text[i] = keyTest[(text[i] - 97)];
            text[i] = tolower(text[i]);
        }
        else if (isupper(text[i]))
        {
            // use uppercase version of cipher
            text[i] = keyTest[(text[i] - 65)];
            text[i] = toupper(text[i]);
        }
        // printf("\n%s", text);
    }

    printf("ciphertext: %s\n", text);

}