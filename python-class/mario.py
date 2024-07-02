from cs50 import get_int
from sys import argv
import sys
#Command line setup
if len(argv) == 2:
    print(f"Hello, {argv[1]}")
else:
    print("Hello, World")
#ARGV je lista i zato radi FOR
#               pocinje od pozicije jedan pa ide do kraja
for arg in argv[1:]:   # moze i argv[1:5]
    print(arg)

# Ili
if len(sys.argv) != 2:
    print("Missing command line argument")
    sys.exit(1)
print(f"Hello, {sys.argv[1]}")



def main():

    for i in range(get_height()):
        print("#", end="!")

    print() #Novi red posle loopa




    for i in range(3):
    print("?" * 4) #PRints 4 times


def get_height():
    while True:
        try:

            n = int(input("Number: "))
            if n > 0:
                return n
            #You can use break to get out of loop or return
            #break
        except ValueError:
            print("Not a number")

main()
#LIST !!!!!!!!!!!!!!!

scores = []
score = get_int("Number: ")
#         sums up       length
average = sum(scores) / len(scores)

scores.append(score)
#or
scores += [score]

print(f"Average: {average}")

before = input("Beofore: ")
after = before.upper()
#Moze da se koristi for sa c za uzimanmje karaktera iz stringa
for c in before:
