from cs50 import get_string


def count_letters(text):
    countL = 0

    # Checks if the char is a letter
    for char in text:
        if char.isalpha():
            print(char.isalpha())
            countL += 1

    return countL


def count_words(text):
    countW = 1

    # Checks for spaces then count a word
    # ASCII 32 == space
    for char in text:
        if ord(char) == 32:
            countW += 1

    return countW


def count_sentences(text):
    countS = 0

    for char in text:
        asc = ord(char)

        # Checks for "." , "?" or "!" then count a sentence
        # ASCII 33 == !, 63 == ?, 46 == .
        if asc == 46 or asc == 63 or asc == 33:
            countS += 1

    return countS


# asks for the text to evaluate
text = get_string("Text: ")

# call the functions that calculate the number of letters, words and sentences
letters = count_letters(text)
words = count_words(text)
sentences = count_sentences(text)
print(letters)
print(words)
print(sentences)

L = 100 * (letters/words)
S = 100 * (sentences/words)

# calculate index a round it
index = 0.0588 * L - 0.296 * S - 15.8
rIndex = round(index)

# prints the Grade according to the rounded Index
if rIndex < 1:
    print("Before Grade 1\n")

elif rIndex > 16:
    print("Grade 16+\n")

else:
    print(f"Grade {rIndex}\n")