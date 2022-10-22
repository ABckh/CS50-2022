from audioop import mul


FIRST_NUMBERS = 2


def main() -> None:
    card_number = get_card_number()
    if check_number(card_number) == False:
        print("INVALID")
    else:
        first_numbers = get_first_numbers(card_number)
        if first_numbers > 50 and first_numbers < 56:
            print("MASTERCARD");
        elif first_numbers == 37 or first_numbers == 37:
            print("AMERICAN EXPRESS");
        elif first_numbers>= 40 and first_numbers < 50:
            print("VISA");


def get_card_number() -> int:
    while True:
        try:    
            number = int(input("Number: "))
            if number > 1000000000000 or number < 9999999999999999:
                return number
        except:
            print("Please enter correct card number ")


def check_number(number: int) -> bool:
    mult_sum = get_mult_sum(number // 10)
    sum = get_sum(number)
    if (mult_sum + sum) % 10 == 0:
        return True
    else:
        return False


def get_sum(number: int) -> int:
    sum = 0
    while number > 0:
        sum += int(number % 10)
        number //= 100
    return sum
        

def get_mult_sum(number: int) -> int:
    sum = 0
    while number > 0:
        mult_last_num = (number % 10) * 2
        if mult_last_num < 10:
            sum += mult_last_num
        else:
            sum += get_sum(mult_last_num) + 1
        number //= 100
    return sum


def get_first_numbers(number: int) -> int:
    while number > 100:
        number //= 10
    return number

main()