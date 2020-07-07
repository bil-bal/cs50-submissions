from cs50 import get_string
import re

def main():
    number = get_string("Number: ")

    length = len(number)

    if re.search("^37|^34(.*)", number) and length == 15 and luhn(number):
        print("AMEX")
    elif re.search("^51|^52|^53|^54|^55(.*)", number) and length == 16 and luhn(number):
        print("MASTERCARD")
    elif re.search("^4(.*)", number) and (length == 13 or length == 16) and luhn(number):
        print("VISA")
    else:
        print("INVALID")


def luhn(number):
    sumn = 0
    number = number[::-1]

    for i in range(len(number)):
        if i % 2 != 0:
            tmp = int(number[i]) * 2
            if tmp > 9:
                sumn += int(str(tmp)[0]) + int(str(tmp)[1])
            else:
                sumn += tmp
        else:
            sumn += int(number[i])

    if sumn % 10 == 0:
        return True
    else:
        return False


main()