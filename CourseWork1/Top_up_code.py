"""
Top-Up Code - Top-Up Management for Tickets

Purpose:
Handles the creation, loading, and display of Top-Up options
linked to specific ticket categories. Allows guests to add
top-ups to their basket.

Features:
- TopUp class:
    - Represents a single top-up option with category, title, description, and price
    - __str__ method formats the top-up for display with price in pounds

- Functions:
    - load_topups(): Reads all top-ups from 'mobile_products.csv' and returns TopUp objects
    - view_topups_for_category(category_title, basket):
        - Displays all top-ups for the selected category
        - Allows user to repeatedly add multiple top-ups to the basket
        - Input 'q' exits to main menu

Notes:
- Uses CSV file 'mobile_products.csv' to load top-up information
- Basket is updated directly from this module
"""

import csv  # Import the CSV module to read data from CSV files
from buy_a_ticket_code import add_to_basket#does nothing forgot to remove in submition     



# Class to represent a single Top-Up option
class TopUp:
    # Constructor that runs automatically when a new object is created
    # 'self' refers to the instance of the object being created
    def __init__(self, category_title, title, description, price): #paremeters 
        self.category_title = category_title  # The category this top-up belongs to
        self.title = title                      # Name/title of the top-up
        self.description = description          # Description of the top-up
        self.price = price                      # Price of the top-up (stored in pence)

    # Method to define how the TopUp object should be represented as a string
    def __str__(self):#when print self # dunder double underscore automactially cled by python is certain situation 
        # Convert pence to pounds for guest view when printing
        price_in_pounds = self.price / 100
        # Format the title and price neatly for printing
        return f"{self.title} - £{price_in_pounds:.2f}"#hopython should show the text


# Function to read all top-ups from the CSV file and return a list of TopUp objects
def load_topups():
    topups = []  # Initialize an empty list to store all top-up objects
    try:
        # Open the CSV file safely in read mode
        with open('mobile_products.csv', mode='r') as file:
            # DictReader allows us to access CSV columns by header names
            reader = csv.DictReader(file)

            # Loop through each row of the CSV to create TopUp objects
            for row in reader:
                #can now be printed has a object
                topup = TopUp(#calls TopUp function to turn row into object. easy to acces.use __str__ to control how thier printed 
                    row["category_title"],               # Assign category from CSV
                    row["topup_title"],                  # Assign title from CSV
                    row["topup_description"],            # Assign description from CSV
                    float(row["topup_price_in_pence"])   # Convert price to float (still in pence)
                )
                # Add the TopUp object to the list
                topups.append(topup)

    except FileNotFoundError:
        # Handle case where CSV file is missing
        print("Top-Up CSV file not found.")

    # Return the full list of TopUp objects
    return topups


# Function to display all top-ups for the specific category user slected and allow user selection
def view_topups_for_category(category_title, basket):
    # Load all top-ups from CSV
    topups = load_topups()

    # t = topup object
    matching = [t for t in topups if t.category_title == category_title]#creates list matching TopUp objects who's category_title mtaches the category_title where looking for 

    if not matching:
        print("No top-ups available for this category yet.")
        return None

    print(f"\n-- Top-Ups for {category_title} --")

    # Display top-ups ONCE (prices shown in pounds)
    for index, topup in enumerate(matching):#loops through macthing list 
        price_in_pounds = topup.price / 100#convert to pound
        print(f"{index + 1}. {topup.title} - £{price_in_pounds:.2f}")
        print(f"    {topup.description}")

    # Loop only for user input
    while True: #loop indefinetly unless something inside the loop breakes or reatun
        print("\nEnter a number to add a ticket to your basket")
        print("Press 'q' to return to the main menu")

        choice = input("Your choice: ").lower()

        # Exit back to main menu
        if choice == "q":
            return None

        try:
            choice = int(choice)
            if 1 <= choice <= len(matching):#ensures chouce numebr matches tikct shown
                selected_topup = matching[choice - 1]#list index star at 0 user input start at 1

                basket_entry = f"{selected_topup.title} - £{selected_topup.price / 100:.2f}" #creates a string for the basket
                basket.append(basket_entry)#add it to basket list

                print(f"\n'{basket_entry}' has been added to your basket.")
            else:
                print("Invalid choice.")

        except ValueError:
            print("Invalid input. Please enter a number or 'q'.")

