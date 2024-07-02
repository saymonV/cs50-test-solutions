greet = input("Greeting: ")

greet = greet.split()
greet = greet[0:1]
word = greet[0].rstrip()
print(f"{word}")
if word[0:5].lower() == "hello":
    print("$0")
elif word[0].lower() == "h":
    print("$20")
else:
    print("$100")

