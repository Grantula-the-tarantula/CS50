#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define FAT_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //Open Memory Card File, Confirm filename has been entered
    FILE *f = fopen(argv[1], "r");

    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    // if (!f)
    // {
    //     return 1;
    // }

    //Create Memory to Store Data
    BYTE *fat_block_p = malloc(FAT_SIZE);
    if (fat_block_p == NULL)
    {
        printf("Not enough memory for this operation\n");
        return 1;
    }


    //Initialize counter, output file for image
    int counter = 0;
    char filename[8];

    //Output file for pictures
    FILE *image = NULL;

    //Iterate through Card data and populate Buffer Array
    while (fread(fat_block_p, FAT_SIZE, 1, f) == 1)
    {
        //Check for jpeg signature in first 4 bytes
        if (fat_block_p[0] == 0xff && fat_block_p[1] == 0xd8 && fat_block_p[2] == 0xff && (fat_block_p[3] & 0xf0) == 0xe0)
        {


            //Create a new file if BYTE is start of new jpeg file
            sprintf(filename, "%03i.jpg", counter);
            image = fopen(filename, "w");
            fwrite(fat_block_p, FAT_SIZE, 1, image);
            counter++;

        }

        //Continue writing to image
        if (counter > 0)
        {
            image = fopen(filename, "a");
            fwrite(fat_block_p, FAT_SIZE, 1, image);
            fclose(image);

        }


    }

    //Close files and clear memory
    free(fat_block_p);
    fclose(f);


    return 0;

}
