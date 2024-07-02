import cs50


def main():
    # Getting input from a user
    text = cs50.get_string("Text: ")
    # Variables for counting
    letters = 0
    words = 1
    sentences = 0
    # Looping and cheching every character in a string
    for i in text:
        if i.isalpha():
            letters += 1
        if i == " ":
            words += 1
        if i == "!" or i == "." or i == "?":
            sentences += 1
    # Calculating average
    avrgLetters = letters / words * 100.0
    avrgSentences = sentences / words * 100.0
    # Indexing using formula
    index = round(0.0588 * avrgLetters - 0.296 * avrgSentences - 15.8)

    # Printing out Grade
    if index <= 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    elif index > 1 and index < 16:
        print(f"Grade {index}")


main()