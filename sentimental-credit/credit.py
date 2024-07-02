import cs50


def main():
    credit_card = (get_cc_number())
    if checksum(credit_card):
        cc_type(credit_card)
    else:
        print("INVALID")

# Function makes sure we get valid input from the user


def get_cc_number():
    cc_number = cs50.get_string("Number: ")
    cc_length = len(cc_number)
    if (cc_length > 16 or cc_length < 13) or cc_length == 14:
        print("INVALID")
    else:
        return cc_number

# Function checks credit card type


def cc_type(cc):
    # f2d -> first two digits
    length = len(cc)
    f2d = int(cc[:2])
    first_digit = int(cc[:1])
    # Printing cards names
    if (f2d == 34 or f2d == 37) and length == 15:
        print("AMEX")
    elif (f2d > 50 and f2d < 56) and length == 16:
        print("MASTERCARD")
    elif first_digit == 4 and (length == 13 or length == 16):
        print("VISA")
    else:
        print("INVALID")

# Using Luhn’s Algorithm making  sure credit card number is valid


def checksum(cc):
    sum = 0
    # Enumerate outputs index(i) and value for each character (ch)
    for i, ch in enumerate(cc[::-1]):
        if i % 2 == 0:
            sum += int(ch)
        else:
            for char in str(int(ch)*2):
                sum += int(char)
    return sum % 10 == 0


main()