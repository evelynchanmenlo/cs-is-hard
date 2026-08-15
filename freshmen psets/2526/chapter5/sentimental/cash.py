# Cash by Evelyn Chan
from cs50 import get_float
QUARTERS = 25
DIMES = 10
NICKELS = 5
PENNIES = 1

while True:
    # Prompts the user to keep trying until they input a number above zero.
    change_owed = get_float("Change owed: ")
    if change_owed > 0:
        break
# This converts the "cents" that the user inputs into a whole number, and rounds it up.
change_owed = round(change_owed * 100)

count = 0
while QUARTERS <= change_owed:
    # For as many times you can use quarters, this decreases the amount by a quarter and
    # increases the count by 1
    change_owed -= QUARTERS
    count += 1

while DIMES <= change_owed:
    # the same goes for dimes
    change_owed -= DIMES
    count += 1

while NICKELS <= change_owed:
    # the same goes for nickels
    change_owed -= NICKELS
    count += 1

while PENNIES <= change_owed:
    # the same goes for pennies
    change_owed -= PENNIES
    count += 1

print(f"Count: {count}")
