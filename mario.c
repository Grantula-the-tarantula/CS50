// Prints a Pyramid a Height of n

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    int m;
    int b;

    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8 || n == 0);

    m = n - 1;
    b = n / n;

    //Exterior Loop for Rows, Interior Loop for Columns

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf(" ");
        }
        m = m - 1;

        for (int k = 0; k < b; k++)
        {
            printf("#");
        }

        for (int q = 0; q < 2; q++)
        {
            printf(" ");
        }

        for (int z = 0; z < b; z++)
        {
            printf("#");
        }
        b = b + 1;

        printf("\n");
    }

}
