#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("The winner is the 1st player, with %i points\n", score1);
    }
    else if (score2 > score1)
    {
        printf("The winner is the 2nd player, with %i points\n", score2);
    }
    else
    {
        printf("Draw!\n");
    }
}

int compute_score(string word)
{
    int sum = 0;
    for (int i = 0, n = strlen(word); i < n; i++ )
    {
        char letter = word[i];
        if (isalpha(letter))
        {
            int letter_number;
            if (isupper(letter))
            {
                letter_number = (int) letter - 65;
            }
            else
            {
                letter_number = (int) letter - 97;
            }
            sum += POINTS[letter_number];
        }
    }
    return sum;
}

