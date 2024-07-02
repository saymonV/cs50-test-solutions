from cs50 import get_string

answer = get_string("Whats your name?")

name = "Nikola"
print(f"Hello, {name}")
words = set()
def check(word):
    if word.lower() in words:
        return True
    else:
        return False
 


def load(dictionary):
    file = open(dictionary, "r")
    for line in file:
        word = line.rstrip()
        words.add(word)
    close(file)
    return True


def size():

    return len(words)

i = 0
while i < 3:
    print("Hello")
    i += 1

for i in range(3):
    print("Hello")

while True:
    print("Meow")

--------------------------------------

#Calculator
from cs50 import get_int
x = int(input("x: "))
y = int(input ("y: "))\
z = x / y
print(f"{z}")

if s == "Y" or s == "y":
    printf("Yes")
elif s == "N" or s == "n":
    printf("No")
s = s.lower()
if s in ["Y", "y"]:
    print("AGREE")
elif s in ["N", "n"]:
    print("Not agreed")
