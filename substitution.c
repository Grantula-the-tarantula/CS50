#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, string argv[])
{
    //Check if key is one string
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //Check if key has 26 characters
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    if (strlen(argv[1]) == 26)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {

            //Makes sure there are no repeated characters
            for (int j = i + 1, m = strlen(argv[1]); j < n; j++)
            {
                if (argv[1][i] == argv[1][j])
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }

            //Makes sure input key is only made up of alphabetic characters
            if (isalpha(argv[1][i]) == 0)
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }

        }


        //Get plaintext from user after checks have been made on key
        string plain = get_string("plaintext:  ");

        //Encipher and print the ciphertext
        printf("ciphertext: ");

        for (int i = 0, n = strlen(plain); i < n; i++)
        {
            //Get character and determine case or punctuation

            //Uppercase letters from plaintext
            //Converts ASCII to integer and then uses number to lookup in original key
            if (isupper(plain[i]) != 0)
            {
                int z = plain[i] - 64;
                printf("%c", toupper(argv[1][z - 1]));

            }

            //Lowercase letters from plaintext
            //Converts ASCII to integer and then uses number to lookup in original key
            if (islower(plain[i]) != 0)
            {
                int x = (plain[i]) - 96;
                printf("%c", tolower(argv[1][x - 1]));

            }

            //Punctuation and spaces
            if (isalpha(plain[i]) == 0)
            {
                printf("%c", plain[i]);
            }
        }

        printf("\n");

    }
}