#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for(int i = 1; i <= height; i ++){
        int spaces;
        int blocks;
        for (spaces = 0; spaces < (height - i); spaces++)
        {
            printf(" ");
        }
        for (blocks = 0; blocks < (height - spaces); blocks++)
        {
            printf("#");
        }
        printf("\n");
    }
}
