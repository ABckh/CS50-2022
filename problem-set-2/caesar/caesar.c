#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void to_cipher(string text, int key);
int are_digits(string text);

int main(int argc, string argv[])
{
   if (argc == 1 || argc > 2 || are_digits(argv[1]) == 0)
   {
      printf("Usage: ./caesar key\n");
      return 1;
   }

   int key = atoi(argv[1]);
   if (key > 26)
   {
      key %= 26;
   }
   string plaintext = get_string("plaintext:  ");
   printf("ciphertext: ");
   to_cipher(plaintext, key);

}

int are_digits(string text)
{
   int i = 0;
   while (text[i] != '\0')
   {
      if (isdigit(text[i]) == 0) return 0;
      i++;
   }
   return 1;
}

void to_cipher(string text, int key)
{
   int i = 0;
   while (text[i] != '\0')
   {
      if (isalpha(text[i]))
      {
         if (isupper(text[i]))
         {
            int letter_num = (int) text[i] - 65;
            int rotated  = (letter_num+key)%26;
            int rotated_num = rotated + 65;
            printf("%c", rotated_num);
         }
         else
         {
            int letter_num = (int) text[i] - 97;
            int rotated  = (letter_num+key)%26;
            int rotated_num = rotated + 97;
            printf("%c", rotated_num);
         }
      }
      else
      {
         printf("%c", text[i]);
      }
      i++;
   }
   printf("\n");
}

