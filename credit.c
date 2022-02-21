#include <cs50.h>
#include <stdio.h>
#include <math.h>

int getLenght(long num) //function that counts the lenght of a long
{
    int count = 0;

    while (num > 0)
    {
        num /= 10;
        count++;
    }
    return (count);
}

int digitReturn(long n, int e)  //function that returns a digit inside of a long
{
    long digit = pow(10, e);
    while (n >= digit)
    {
        n /= 10;
    }

    return (n % 10);
}

void checkFlag(long num)  //function that checks the flag of the card
{
    int lenght = getLenght(num);

    if (lenght == 15 && (digitReturn(num, 1) == 3) && ((digitReturn(num, 2) == 4) || (digitReturn(num, 2) == 7)))
    {
        printf("AMEX\n");
    }
    else if ((lenght == 16 || lenght == 13) && (digitReturn(num, 1) == 4))
    {
        printf("VISA\n");
    }
    else if (lenght == 16 && (digitReturn(num, 1) == 5) && ((digitReturn(num, 2) <= 5) && (digitReturn(num, 2) > 0)))
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}







bool checkValid(long num)   //function that checks if the card is valid using the Luhn’s algorithm
{
    int lenght = getLenght(num);
    int mult = 0;
    int countT = 0;
    int count2 = 0;
    int count3 = 0;

    for (int i = (lenght - 1); i > 0; i -= 2)
    {
        mult = (digitReturn(num, i) * 2);

        for (int j = getLenght(mult); j > 0; j--)
        {
            count3 += (digitReturn(mult, j));
        }


    }

    for (int i = lenght; i > 0; i -= 2)
    {
        count2 += digitReturn(num, i);
    }

    countT = count3 + count2;

    if ((countT % 10) == 0)
    {
        return true;
    }
    else
    {
        printf("INVALID\n");
        return false;
    }
}

long askCreditNum() //function that asks for the user to input the credit card number
{
    long creditNum = 0;

//    while (creditNum < 1000000000000 )
//    {
    creditNum = get_long("Write the number of the credit card: ");

//    }

    return (creditNum);
}



int main(void)
{
    long creditNum;
    bool valid = false;

//    while(!valid)
//    {
    creditNum = askCreditNum();
    if (checkValid(creditNum) == false)
    {
        return 0;
    }
    else
    {
        checkFlag(creditNum);
    }

//    }
}
