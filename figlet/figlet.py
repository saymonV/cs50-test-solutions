from pyfiglet import Figlet
from sys import argv
import random
import sys

figlet = Figlet()
fonts = figlet.getFonts()

def main():
    if len(argv) == 1:
        text = input("Input: ")
        random_font = random.choice(fonts)
        #print(f"{random_font}")
        figlet.setFont(font = random_font)
        print(figlet.renderText(text))
        return 0

    elif len(argv) == 3:
        if (argv[1] == "-f" or argv[1] == "--font") and font_check(argv[2]):
            text = input("Input: ")
            figlet.setFont(font = argv[2])
            print(figlet.renderText(text))
            return 0
        else:
            print("Invalid usage")
            sys.exit("Error has occured")

    else:
        print("Invalid usage")
        sys.exit("Error has occured")



def font_check(user_font):
    for w in fonts:
        if w == user_font:
            return True
    else:
        return False


main()