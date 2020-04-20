#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(void)
{
    //Initialize variables
    string t = get_string("Text:  ");
    int letter_counter = 0;
    int sentence_counter = 0;
    float word_counter = 0;

    //Counting Number of letters, sentences, and words
    for (int i = 0, n = strlen(t); i < n; i++)
    {
        //Scan string and give number of letters
        if (isalpha(t[i]) != 0)
        {
            letter_counter += 1;
        }

        //Scan string and give number of sentences
        if (t[i] == '!' || t[i] == '?' || t[i] == '.')
        {
            sentence_counter += 1;
        }

        //Scan string and give number of words
        if (isblank(t[i]) != 0)
        {
            word_counter += 1;
        }

    }


    //Calculating Coleman-Liau Index
    //Adds one word due to not counting the last word in the sentence
    float l = (letter_counter / (word_counter + 1)) * 100;
    float s = (sentence_counter / (word_counter + 1)) * 100;
    int index = round(0.0588 * l - 0.296 * s - 15.8);


    //Output Grade Level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 1 && index <= 16)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

