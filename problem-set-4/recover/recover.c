#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("The file was not found\n");
        return 1;
    }

    BYTE buffer[512];
    int count  = 0;
    char filename[13];
    FILE* jpeg;

    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
//          if first jpeg
            if (fopen("000.jpg", "r") == NULL)
            {
                sprintf(filename, "%03i.jpg", count);
                jpeg = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, jpeg);
                count++;
            }
//          else: close the previous file;
            else
            {
                fclose(jpeg);
                sprintf(filename, "%03i.jpg", count);
                jpeg = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, jpeg);
                count++;
            }
        }
        else
        {
//            if already found a jpeg
            if (fopen(filename, "r") != 0)
            {
                fwrite(buffer, 1, BLOCK_SIZE, jpeg);
            }
        }
    }
    printf("%i jpeg files are ready to watch!!!\n", count - 1);
    fclose(jpeg);
    fclose(file);
}