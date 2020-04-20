//Checks for valid Credit Card
//Outputs Credit Card Brand or Invalid

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //Only allows numbers between 13-16 digits
    long n;
    long m;
    long c;
    long b;
    long i = 10;
    int num = 0;
    int sum1 = 0;
    int sum2 = 0;
    int check;
    int checksum;
    int digits;
    int digit;

    do
    {
        n = get_long("Number: ");
        if (n > 9999999999999999 || n < 1000000000000)
        {
        printf("INVALID\n");
        exit(0);
        }
    }
    while (n > 9999999999999999 || n < 1000000000000);



    m = n;
    c = n;
    b = m;

    //Checksum Test
    //Checking Second Digit (from right)
    do
    {
        n = n / i;
        num = (n % 10) * 2;
        i = 100;

        if (num > 9)
        {
            num = (num % 10) + 1;
        }
        else
        {
            num = num + 0;
        }

        sum1 = sum1 + num;
        //printf("sum1=%i\n", sum1);

    }
    while (n > 0);

    //Checking First Digit (from right)
    do
    {
        sum2 = sum2 + (m % 10);
        m = m / i;
    }
    while (m > 0);

    //printf("sum1=%i\n", sum1);
    //printf("sum2=%i\n", sum2);

    //Checksum Test
    check = sum1 + sum2;
    checksum = check % 10;

    printf("checksum=%i\n", checksum);

    //Finding First Digit, Two Digits on the card
    do
    {
        c = c / 10;
        digits = c % 100;
    }
    while (c > 100);

    do
    {
        b = b / 10;
        digit = b % 10;
    }
    while (b > 10);

    //Outputting Brand of card

    if ((digits == 34 || digits == 37) && checksum == 0)
    {
        printf("AMEX\n");
    }
    else if (digit == 4 && checksum == 0)
    {
        printf("VISA\n");
    }
    else if ((digits == 51 || digits == 52 || digits == 53 || digits == 54 || digits == 55) && checksum == 0)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

}
