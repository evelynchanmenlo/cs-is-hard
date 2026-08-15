# Strings practice by Evelyn

name = "Evelyn"
vowels = ["a", "e", "i", "o", "u"]

#prints your name in lowerclase
print(f"{name} in  lowercase is: {name.casefold()}")

# Print your name in uppercase
print(f"{name} in uppercase is: {name.upper()}")

# Print your name vertically, one letter per line.
for letter in name:
    print(letter)

# Print just the vowels in your name on the same line. Use the vowel list above.
# for letter in name:
#     if letter in vowels:
#         print(letter, end" ")
# print()

# Extra: Print your name backwards.
print(f"{name} backwards is: {name [::-1]}")
