#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int get_index(string text);
float get_number_of_letters(string text);
float get_number_of_words(string text);
float get_number_of_sentences(string text);


int main(void)
{
    string text = get_string("Text: ");
    int grade = get_index(text);
    if (grade == 10)
    {
        printf("Grade: X");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1")
    }
    else
    {
        printf("Grade: %i\n", grade);
    }
}


int get_index(string text)
{
    // index = 0.0588 * L - 0.296 * S - 15.8
    float number_of_letters = get_number_of_letters(text);
    float number_of_words = get_number_of_words(text);
    float number_of_sentences = get_number_of_sentences(text);

    // average number of letters per 100 words
    float l = 100.0f *  number_of_letters / number_of_words;

    // average number of sentences per 100 words
    float s = 100.0f * number_of_sentences / number_of_words ;

    float index =0.0588 * l - 0.296 * s - 15.8;
    return round(index);
}

float get_number_of_letters(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 'A' && text[i] <= 'z')
       {
            counter++;
        }
    }
    return counter;
}


float get_number_of_words(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ' || text[i] == '\n')
        {
            counter++;
        }
    }
    return counter+1;
}


float get_number_of_sentences(string text)
{
    int counter = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((int) text[i] == 33 || (int) text[i] == 46 || (int) text[i] == 63)
        {
            counter++;
        }
    }
    return counter;
}
