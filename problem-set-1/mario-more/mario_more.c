#include <stdio.h>
#include <cs50.h>


void blocks(int height, int spaces);

int main(void)
{
    int height;
    do {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for(int i = 1; i <= height; i ++){
        int spaces;
            for (spaces = 0; spaces < (height - i); spaces++)
        {
            printf(" ");
        }
        blocks(height, spaces);
        printf(" ");
        blocks(height, spaces);
        printf("\n");
    }
}


void blocks(int height, int spaces)
{
    for (int blocks = 0; blocks < (height - spaces); blocks++)
    {
        printf("#");
    }
}

