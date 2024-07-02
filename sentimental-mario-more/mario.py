import cs50

# Declaring main functioin


def main():
    # Calling functions inside main
    height = get_pyramid_height()
    print_pyramid(height)

# Making sure we prompt until we get int in range


def get_pyramid_height():
    while True:
        try:
            h = cs50.get_int("Height: ")
            if h > 8 or h < 1:
                print("Enter a number between 1 and 8")
            else:
                return h
        except ValueError:
            print("Not an interger number")

# Printing pyramid using for loop


def print_pyramid(h):
    for i in range(h):
        # Spaces at the begining
        for j in range(h - i - 1):
            print(" ", end="")
        # Left side
        for y in range(i + 1):
            print("#", end="")
        # Space in the middle
        print("  ", end="")
        # Right side
        for k in range(i + 1):
            print("#", end="")
        print()


main()
