from cs50 import get_string, get_int

answer = get_string("What's your name?\n")
print(f"Hello, {answer}")

answer1 = get_string("What's your birthday?\n")
print(f"Wow, {answer1} is a fun birthday date")

answer2 = get_string("Where do you live?\n")
print(f"I live in {answer2} too!")

x = get_int("x: ")
y = get_int("y: ")
if x < y:
    print("x is less than y\n")
elif y < x:
    print("y is less than x\n")
else:
    print("x is equal to y\n")

# No do while loop

#for loop
for i in [0, 1, 2]:
    print("x")
#another way of writing in for loops
for i in range(3):
    print("y")

#range - sequence of numbers
#list - sequence of multiple values
#tople - sequence of unchangeable values
#dict - collection of key/value pairs
#set - collection of unique values
