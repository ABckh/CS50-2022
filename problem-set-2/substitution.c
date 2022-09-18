#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void to_cipher(string text,string key);

int main(int argc, string argv[])
{
   if (argc == 1 || argc > 2 )
   {
      printf("Usage: ./substitution key\n");
      return 1;
   }
   else if (strlen(argv[1]) < 26)
   {
      printf("Key must contains 26 characters\n");
      return 1;
   }

   string key = argv[1];
   string plaintext = get_string("plaintext:  ");
   printf("ciphertext: ");
   to_cipher(plaintext, key);

}

void to_cipher(string text, string key)
{
   int i = 0;
   while (text[i] != '\0')
   {
      if (isalpha(text[i]))
      {
         if (isupper(text[i]))
         {
            int letter_num = (int) text[i] - 65;
            int ciphered  = key[letter_num];
            printf("%c", toupper(ciphered));
         }
         else
         {
            int letter_num = (int) text[i] - 97;
            int ciphered  = key[letter_num];
            printf("%c", tolower(ciphered));
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
