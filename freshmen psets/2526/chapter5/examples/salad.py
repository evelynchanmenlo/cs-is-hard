# Evelyn Chan
# https://bit.ly/43K7j4m
# Let's create a Salad!
# Read this: https://www.w3schools.com/python/python_ref_list.asp

def main():
    # Create a salad with five different ingredients.
    # One of them must be a carrot.
    salad = ["carrot", "buffalo dressing", "tzatziki", "caesar dressing", "ranch"]

    # Print the ingredients in your salad, with each ingredient on its own line.
    for ingredient in salad:
        print(ingredient)

    # Add three new ingredients to your salad. One of them must be a carrot.
    salad.append("italian dressing")
    salad.append("carrot")
    salad.append("spicy mayo")

    # Print the ingredients in your salad, with each ingredient on its own line.
    for ingredient in salad:
        print(ingredient)

    # Now, use a Python list method to remove ALL carrots from your salad. #nocarrots
    while "carrot" in salad:
        salad.remove("carrot")

    # Create a separate function that removes carrots from a salad.
    def to_carrots(salad):
        while "carrot" in salad:
            salad.remove("carrot")

    # Create a function that removes any given ingredient from a salad.

    # Create a function that builds a new salad by doing the following:
    #   Prompt the user for the number of ingredients
    #   Prompt the user for each ingredient and edd it to salad

if __name__ == "__main__":
    main()
