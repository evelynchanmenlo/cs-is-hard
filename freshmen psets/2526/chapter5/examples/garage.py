# Read about Python dictionaries here: https://www.w3schools.com/python/python_dictionaries.asp
# car1 is a dict. It contains keys and values. "make" is a key. "Toyota" is a value.
car1 = {"make":"Toyota", "model":"Corolla", "year":"2015", "color":"green"}

# This returns the value associated with the key "make"
str = car1["make"]
print(str)

# print out "I have a green 2015 Toyota Corolla" where the values are filled in from the dict.
print(f"I have a {car1["color"]} {car1["year"]} {car1["make"]} {car1["model"]}")

# create at least three more cars with keys for make, model, year, and color.
car2 = {"make":"Tesla", "model":"Cyber Truck", "year":"2025", "color":"pink"}
car3 = {"make":"Lamborghini", "model":"Urus", "year":"2026", "color":"turquoise"}
car4 = {"make":"Ferrari", "model":"F1-75", "year":"2022", "color":"red"}

# create a list called "garage" that contains all of these cars.
garage = [car1, car2, car3, car4]

# # print the contents of your garage.
print(garage)

# You got a brand new car! You get to choose the make, model, year, and color.
# Now add it to the garage. Bonus if you can create the car and add it
# in a single line of code.
garage.append(car4 := {"make":"Mercedes", "model":"G-Wagon", "year":"2026", "color":"orange"})

# Iterate through the list and print out "I have a [color] [make] [model]" for each car in the garage.
for cars in garage:
    print(f"I have a {cars["color"]} {cars["year"]} {cars["make"]} {cars["model"]}")

# Iterate through the list and print out every car that is newer than 2020.
for cars in garage:
    if (cars["make"] > 2020):
        print(f"I have a {cars["color"]} {cars["year"]} {cars["make"]} {cars["model"]}")
