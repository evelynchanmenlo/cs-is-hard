# Hello Mario by Evelyn Chan
from cs50 import get_int

# infinite loop instead of a do while loop (which doesnt exist in python)
while True:
    height = get_int("Height: ")
    if height >= 1 and height < 9:
        break

spaces = height
for row in range(1, height + 1):
    print(" " * (spaces - row), end="")
    print("#" * row, end="")
    print("  ", end="")
    print("#" * row)
