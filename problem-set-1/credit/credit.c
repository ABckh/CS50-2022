#include <cs50.h>
#include <stdio.h>


long get_number(void);
bool check_number(long number);
int get_sum(long number);
int get_mult_sum(long number);
int get_first_numbers(long number);

int main(void)
{
    const int FIRST_NUMBERS = 2;
    long card_number = get_number();
    if (check_number(card_number) == false) printf("INVALID");
    else
    {
        if (get_first_numbers(card_number) > 50 && get_first_numbers(card_number) < 56)
        {
            printf("MASTERCARD\n");
        }
        else if (get_first_numbers(card_number) == 37 || get_first_numbers(card_number) == 37)
        {
            printf("AMERICAN EXPRESS\n");
        }
        else if (get_first_numbers(card_number) >= 40 && get_first_numbers(card_number) < 50)
        {
            printf("VISA\n");
        }
    }
}


long get_number(void)
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1000000000000 || number > 9999999999999999);
    return number;
}

bool check_number(long number)
{
    int mult_sum = get_mult_sum(number / 10);
    int sum = get_sum(number);
    if ((mult_sum + sum) % 10 == 0) return true;
    else return false;
}


int get_sum(long number)
{
// sum of digits, which weren't multiplied by 2
    int sum = 0;
    while (number > 0)
    {
        int last_number = number % 10;
        sum += last_number;
        number /= 100;
    }
    return sum;
}


int get_mult_sum(long number)
{
//  sum of digits, which were multiplied by 2
    int sum = 0;
    while (number > 0)
    {
        int last_number = number % 10;
        int multiplied_last_num = last_number * 2;
        if (multiplied_last_num < 10)
        {
            sum += multiplied_last_num;
        } else
        {
            sum += get_sum(multiplied_last_num) + 1;
        }
        number /= 100;
    }
    return sum;
}

int get_first_numbers(long number)
{
    while (number > 100)
    {
        number /= 10;
    }
    return number;
}
