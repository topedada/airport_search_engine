"""
Buy a Ticket Code - Guest Ticket Management

Purpose:
Provides functionality for the guest/user to select and view ticket categories,
add tickets to a basket, and manage the basket. Handles saving purchases.

Features:
- Category class:
    - Represents a ticket category with unique code, title, and description
    - Accessor methods: get_code(), get_title(), get_description()

- Guest Functions:
    - add_to_basket(item): Adds a selected ticket/top-up to the basket
    - save_purchases(basket): Saves all items in the basket to 'purchases.csv'
    - view_basket(): Displays basket contents, calculates total price, allows item removal
    - view_categories(): Loads categories from CSV and displays them
    - buy_ticket(): Allows user to select a category, returns the category title

Notes:
- Uses CSV file 'mobile_products.csv' to load category information
- Basket is a shared global list
- Prices in the basket are parsed from the string representation
"""

import csv
import sys  # Import the sys module to allow for clean exiting of the program


basket = []  # This list holds all tickets or items that the user selects to purchase


# Class Definition
# This class defines how to store and manage each ticket category's data
class Category:
    # __init__ is the constructor that runs automatically when a new object is created
    # 'self' referse to the object being created in this istance category 
    def __init__(self, code, title, desc): #parameters place holder values latter to be place with the actual value so values done have to be hard coded 
        self.code = code  # Unique ID assigned to this category
        self.title = title  # Name or title of the category
        self.description = desc  # Brief description of the category
        
    # Instant variables created to store the variables within the the category object 
    # Method to retrieve the unique category ID
    def get_code(self):
        return self.code #retrieve data stored in the object and send it to other part of the code that calls the method 

    # Method to retrieve the category title
    def get_title(self):
        return self.title

    # Method to retrieve the category description
    def get_description(self):
        return self.description


# Function to add an item to the user's basket
def add_to_basket(item):
    # Add the given item to the basket list
    basket.append(item)
    # Inform the user that the item has been successfully added
    print(f"\n'{item}' has been added to your basket.")

def save_purchases(basket):
    """
    Save the current basket to 'purchases.csv'.
    Each row contains a single purchase (ticket or top-up).
    """
    if not basket:
        print("Your basket is empty. Nothing to save.")
        return
 
    try:#error handling will run the code ina try block and if error happens will skip to ecpection code 
        # Open purchases.csv in append mode so we don't overwrite previous purchases
        with open('purchases.csv', mode='a', newline='') as file:#opens the csv and appends it
            writer = csv.writer(file)#writes into the purchases.csv opned as file and stores it rhe object into writer 
            for item in basket:#loops throught each item in the basket list
                writer.writerow([item])#calls the writer method wrrites the item on a new line in the CSV 
        print("Your purchases have been saved successfully!")
        basket.clear()
        print("Basket has been Cleared")
    except Exception as e:#catches erros within the subclass expection
        print(f"Error saving purchases: {e}")



# Function to display all items currently in the basket
def view_basket():
    print("\n-- Your Basket --")

    if not basket:
        print("Your basket is currently empty.")
        return

    total = 0.0#calculate the total price
    print("----RECEIPT----")
    
    for index, item in enumerate(basket, start=1):# enmurate loops through the basket 
        print(f"{index}. {item}")# print each item with a number 

        # Extract price from string (after £)
        if "£" in item: #checks if the item conatins a £ symbole
            price = float(item.split("£")[1]) #slpits the string at £ takes the part and turn it to a int 
            total += price #adds it to the total  
            
    print("---------------") 
    print(f"\nTotal: £{total:.2f}") #Display the total 

    choice = input("\nEnter item number to remove (or press Enter to continue): ")

    if choice == "": #function ends 
        return

    try: #error handling for input 
        index = int(choice) - 1 # subtrcts 1 to match list indexing(list start at 0 but the user starts at 1)
        if 0 <= index < len(basket):#ensures he option is not a negative and is lesser then the lenght of the basket
            removed = basket.pop(index)#remove item using pop
            print(f"\n'{removed}' removed from basket.")#display what was removed 
        else:
            print("Invalid item number.")# if input is or lesser than 0 or greater then the basket length
    except ValueError: #catches error while trying to covert to a number (subclass valueerror)
        print("Invalid input.")


# Function to load and display all ticket categories from the CSV file
def view_categories():
    print("\n--- Displaying Categories (Guest View) ---")

    # Initialize structures to store category information
    categoryList = []#stores category titles to check for duplicates 
    categoryObjectList = []# Stores actual Category objects 
    code = 0#gives each category a uniqe id  

    try:
        with open('mobile_products.csv', mode='r') as file:#with ensures file closes automatically whhen done 
            csvFile = csv.DictReader(file)#reads the CSV so each row is a dictonary, using the csv headers as keys 
            for line in csvFile:#loops through each row in the csv
                if line["category_title"] not in categoryList:#checks if the category title is already in categotylist
                    categoryList.append(line["category_title"])# Add the new category title to categorylist
                    thisCat = Category(code, line["category_title"], line["category_description"])# creates a category object with a unique ID, Title, dec
                    categoryObjectList.append(thisCat)#add object to categoryObjectList
                    code += 1#Increments code for the next category

        # Print a formatted table header for displaying category data
        header = f"| {'ID':<5} | {'Category Title':<25} | {'Category Description':<40} "
        print(header)
        # Print a separator line based on header length for clarity
        print("-" * len(header))

        # Loop through the list of Category objects and print their details
        for data in categoryObjectList:
            print(f"| {data.get_code():<5} | {data.get_title():<25} | {data.get_description():<40} ")#print the data in the table 
        # Return the list of Category objects so that selected IDs can be mapped to titles
        return categoryObjectList

    except FileNotFoundError:#error handling 
        # Handle situation where the CSV file is missing
        print("Error: 'mobile_products.csv' file not found.")
        # Return empty list to prevent the program from breaking
        return []


# Function for the guest to buy a ticket
# Handles category selection and prepares the selected category for top-up integration
def buy_ticket():
    print("\n--- Buy a Ticket ---")
    categories = view_categories()#Calls view_categiry function displays all avalbile category 
    
    # If no categories were found, exit the function early
    if not categories:
        return None

    try:
        # Prompt the user to select a category by ID
        category_id = int(input("\nEnter the category ID you want to view: "))
        # cat is the current category object in the loop 
        # Initialize variable to store the selected category title
        selected_category = None #stores category title 
        # Find the category title that matches the entered ID
        for cat in categories: # Loop through each Category object; 'cat' represents one category
            if cat.get_code() == category_id:#Retrives the ID in cat and checks if it macthes the number the user entered 
                selected_category = cat.get_title()# method used to retrieve the category from the calss and save it into selcted_category
                break #stops the loop ones the maatch is found 

        # If the category ID is invalid (not found), inform the user
        if not selected_category:
            print("Invalid category ID.")
            return None

        # Display the selected category for confirmation
        print(f"\nYou selected category: {selected_category}")

        # Return the category title to use for linking with top-ups
        return selected_category  

    except ValueError:
        # Handle the case where user input is not an integer
        print("Invalid input. Please enter a number.")
        return None
