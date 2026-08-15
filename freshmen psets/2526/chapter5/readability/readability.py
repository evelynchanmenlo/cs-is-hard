from cs50 import get_string
MIN = 1
MAX = 16
letters = 0
words = 1
sentences = 0

# This prompts the user for input.
text = get_string("Text: ")

# letters count
for char in text:
    # If each char is alphabetical, then it would add to the letters count.
    if char.isalpha():
        letters += 1

#words count
for char in text:
    # This counts the amount of spaces in the string.
    # So, every new space indicates that there is a new word.
    if char.isspace():
        words += 1

#sentences count
for char in text:
    #This counts the amount of puncuation in the string.
    #The amount of puncuation used indiciates how many sentences there are.
    if char == "." or char == "!" or char == "?":
    sentences += 1

# This finds the average of letters per 100 words in the text.
L = (letters / words) * 100
# This finds the average of sentences per 100 words in the text.
S = (sentences / words) * 100
# Inputs L and S into the Coleman-Liau index to find the grade level.
index = round(0.0588 * L - 0.296 * S - 15.8)

# If the reading level is too low, it will print "Before Grade 1"
if index < MIN:
    print("Before Grade 1")
# If the reading level is too high, it will print that it is too high.
elif index >= MAX:
    print("Grade 16+")
else:
    print(f"Grade {index}")
