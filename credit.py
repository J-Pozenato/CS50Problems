# TODO

from cs50 import get_int


def get_digit(number, n):
    return number // 10**n % 10
    

def check_valid(number):
    mult = 0
    countT = 0
    count2 = 0
    count3 = 0

    for i in range(1, lenght, 2):
        mult = get_digit(number, i) * 2
        # print("mult ", mult)

        for j in range(len(str(mult)), -1, -1):
            count3 += get_digit(mult, j)
            # print("count3 ", count3)

    for i in range(0, lenght, 2):
        count2 += get_digit(number, i)
        # print("count2 ", count2)

    countT = count3 + count2
    # print("countT ", countT)

    if (countT % 10) == 0:
        return True

    else:
        print("INVALID\n")
        return False


def check_flag(number):
    if (lenght == 15) and (get_digit(number, lenght - 1) == 3) and ((get_digit(number, lenght - 2) == 4) or (get_digit(number, lenght - 2) == 7)):
        print("AMEX\n")

    elif (lenght == 16 or lenght == 13) and get_digit(number, lenght - 1) == 4:
        print("VISA\n")

    elif lenght == 16 and get_digit(number, lenght - 1) == 5 and (get_digit(number, lenght - 2) <= 5 and get_digit(number, lenght - 2) > 0):
        print("MASTERCARD\n")

    else:
        print("INVALID\n")

    return


number = get_int("Number: ")
lenght = len(str(number))
# print(get_digit(number, 1))

if check_valid(number):
    # print("valid")
    check_flag(number)
