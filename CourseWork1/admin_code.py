"""
Admin Code - Administrator Management

Purpose:
Provides administrator functions to manage categories, tickets, and purchases.
Enables adding/removing categories, generating default top-ups,
editing ticket prices, and viewing detailed purchase statistics.

Features:
- Functions:
    - generate_default_topups(category_title, category_description, count=3):
        Creates multiple random default tickets for a new category
    - load_categories(): Loads all categories and top-ups from 'mobile_products.csv'
    - save_categories(data): Saves all category and top-up data back to the CSV
    - view_categories(): Displays all existing categories
    - add_category(): Adds a new category with multiple default tickets
    - remove_category(): Removes a category and all associated top-ups
    - view_purchases(): Shows all saved purchases, total tickets sold, revenue, and per-ticket summary
    - edit_ticket_price(): Allows admin to edit the price of a ticket
    - admin_menu(): Main loop for admin actions

Notes:
- CSV files used:
    - 'mobile_products.csv' for categories and top-ups
    - 'purchases.csv' for purchase records
- Randomization is used to generate default tickets for new categories
- Provides statistics to track ticket sales and revenue
"""

import csv  # Import CSV module to read/write CSV files
import random# used to give created category random top-up options 

def generate_default_topups(category_title, category_description, count=5):#variables that the function uses to hold values that are passed into it when it’s called.
    """
    Creates multiple randomized default top-ups for a new category.
    """
    titles = ["Standard Ticket", "Basic Pass", "Starter Ticket", "Flex Pass", "Saver Ticket"]#option of ticket titles 
    descriptions = [ #option of ticket discriptions 
        "Default ticket for this category",
        "Standard travel pass",
        "Introductory ticket option",
        "Flexible travel option",
        "Best value ticket"
    ]

    topups = []# list store all generated top-up dictionaries

    for _ in range(count):#loops 5 time to match the count value to macth the amount of ticket created 
        topups.append({#creating dic 
            'category_id': '',
            'category_title': category_title,
            'category_description': category_description,
            'topup_id': '',
            'topup_title': random.choice(titles),
            'topup_description': random.choice(descriptions),
            'topup_price_in_pence': str(random.randint(500, 2500)),  # £5–£25
            'topup_entitlement_type': '',
            'topup_entitlement_value': '',
            'topup_entitlement_unit': '',
            'topup_entitlement_quantity': '',
            'topup_entitlement_start_date': '',
            'topup_entitlement_end_date': '',
            'topup_passenger_class_id': '',
            'topup_passenger_class_name': '',
            'topup_passenger_class_quantity': ''
        })

    return topups#send top up back to function for later use 

# Load all categories and their top-ups from the CSV file
def load_categories():
    try:
        with open('mobile_products.csv', mode='r', newline='') as file:
            reader = csv.DictReader(file)
            data = [row for row in reader]# loops through each row from the reader and saves it into data
        return data #send the list of dic back to load_categories so other part of the code can use it 
    except FileNotFoundError: #error handling 
        print("CSV file not found. Starting with empty list.")
        return [] #return an empty list


def save_categories(data):
    fieldnames = [ # defines the field name for the csv so the dictwriter knows the correct order to write each piece of data 
        'category_id',
        'category_title',
        'category_description',
        'topup_id',
        'topup_title',
        'topup_description',
        'topup_price_in_pence',
        'topup_entitlement_type',
        'topup_entitlement_value',
        'topup_entitlement_unit',
        'topup_entitlement_quantity',
        'topup_entitlement_start_date',
        'topup_entitlement_end_date',
        'topup_passenger_class_id',
        'topup_passenger_class_name',
        'topup_passenger_class_quantity'
    ]

    
    with open('mobile_products.csv', mode='w', newline='') as file:#overwrites the file completely with new data
        writer = csv.DictWriter(file, fieldnames=fieldnames) # passes my veriable fieldname into the dictreader paramter fieldname 
        writer.writeheader()#Writes the column names (from fieldnames) at the top of the CSV done only onces 
        writer.writerows(data)#loop through each dictonary in data and writes each one as a row in the csv

def view_categories():
    #data hold the entire csv content 
    data = load_categories() # calls the load_categories function 
    categories_seen = set()#Creates an empty set to store category titles that have already been displayed no duplication 
    print("\n-- Existing Categories --")
    for row in data:#goes through each dictonary row in the csv data 
        if row['category_title'] not in categories_seen:#check if the category has already been displayed 
            print(f"- {row['category_title']}: {row['category_description']}")# if not in set print category title and description 
            categories_seen.add(row['category_title'])#add the title to categories_seen so it wont print again 
    if not categories_seen:
        print("No categories found.")#if csv was empty and no categories was added print

# Add a new category with a description
def add_category():
    title = input("Enter new category title: ").strip()
    description = input("Enter category description: ").strip()

    data = load_categories()#calls load_categories reads each row from the csv and stores them inside the list data

    # Generate a safe default top-up automatically
    # Generate multiple default top-ups
    new_topups = generate_default_topups(title, description, count=5) # Automatically creates 5 default tickets/top-ups for the new category
    #extend adds multiple at onces 
    data.extend(new_topups)#Adds all newly generated top-ups to the existing data list
    save_categories(data) #Writes all rows back to mobile_products.csv

    print(f"Category '{title}' added successfully with {len(new_topups)} default tickets.") #confromation message 

# Remove a category and all its associated top-ups
def remove_category():
    data = load_categories()# calls l_C reads each row from the csv and stores them inside the list data 
    view_categories() # print the current categories 

    title = input("Enter the category title to remove: ").strip()

    # Keep only rows that do NOT match the chosen category
    new_data = [row for row in data if row['category_title'] != title] # != not even 
    
    if len(new_data) == len(data):# lenght of the data stayed the same so nothing was removed  
        print(f"No category named '{title}' found.")
    else:
        save_categories(new_data)# Save updated list safely
        print(f"Category '{title}' and its top-ups removed successfully.")

def view_purchases():
    """
    Allows admin to view all saved purchases from 'purchases.csv',
    shows total tickets sold, total revenue (overall), and per-ticket breakdown.
    """
    #tracking variables 
    total_revenue = 0         # Overall revenue in pounds
    total_tickets_sold = 0    # Total number of tickets sold
    ticket_summary = {}       # Dictionary to store counts and revenue per ticket type

    try:
        with open('purchases.csv', mode='r', newline='') as file: # reads the csv line by line saving each row as a list
            reader = csv.reader(file) #read each row in the csv and save it into read 
            print("\n-- Saved Purchases --")
            empty = True # check if the file has any valid data
                 #the actual  data           
            for i, row in enumerate(reader, start=1): #goes through each row in the csv and gives them a number starting at 1 
                if row:#check csv and skip blank lines/row
                    empty = False # valid data was found 
                    entry = row[0]#takes the first item from read list and stores it has a string instead of a list 
                    print(f"{i}. {entry}")#prints each entry with a number 

                    # Extract ticket name and price
                    try:
                        ticket_name, price_str = entry.split(" - £")# splits entry into ticketname and price
                        ticket_name = ticket_name.strip() 
                        price = float(price_str.strip())
                    except ValueError:
                        # Skip malformed rows
                        continue

                    total_revenue += price #add current ticket price at the end of the loop to the total ticket price 
                    total_tickets_sold += 1 # add 1 for every ticket in the loop

                    # Count and revenue per ticket type
                    if ticket_name in ticket_summary: #check if ticket type already exist in the dictonary 
                        ticket_summary[ticket_name]['count'] += 1#if it exist increas number of ticket sold by 1
                        ticket_summary[ticket_name]['revenue'] += price# add the price to the total revenue 
                    else:
                        ticket_summary[ticket_name] = {'count': 1, 'revenue': price}# add 1 count and current price 

            if empty: #empty = true 
                print("No purchases found.")
            else:
                # Print overall stats
                print(f"\nTotal Tickets Sold: {total_tickets_sold}")
                print(f"Overall Revenue: £{total_revenue:.2f}")

                # Print per-ticket summary
                print("\n-- Tickets Sold per Type --")
                #ticket = name of ticket type
                for ticket, data in ticket_summary.items(): # loop throught every ticket type in the dictinary to get the count and revenue 
                    print(f"{ticket}: {data['count']} sold, £{data['revenue']:.2f} total")

    except FileNotFoundError:
        print("No purchases CSV found. No purchases have been saved yet.")

# Function: edit_ticket_price
# Type: Admin utility function / Procedural function
# Purpose: Allows the administrator to edit the price of a specific ticket in the categories CSV
def edit_ticket_price():
    # Load all categories and top-ups from the CSV file
    data = load_categories()

    # Check if any data was loaded; if not, exit the function
    if not data:
        print("No data found.")
        return  # Early exit

    # Display a header for the ticket & price editing section
    print("\n--- Ticket & Prices ---")

    # Enumerate through the data to show each top-up with its index number
    for i, row in enumerate(data):#loops through all the rows in dic data and gives it a number
        if row['topup_title']:#skips row that doesn't have a ticket
            price = row['topup_price_in_pence']#get the price of the ticket from the row and stores the current ticket price
            print(f"{i}. {row['topup_title']} - {price} pence") # Display index, ticket title, and price

    try:
        # Ask the admin to select the ticket number they want to edit
        index = int(input("\nEnter the number of the ticket to edit: "))

        # Check if the entered index is within the valid range
        if index < 0 or index >= len(data): #checks if the index is valid 
            print("Invalid selection.")  # Index out of range
            return  # Exit function if invalid

        # Get the selected ticket row from the data
        selected = data[index]


        if not selected['topup_title']:#checks if the row has a ticket 
            print("Selected row has no ticket.")
            return  # Exit if no ticket exists in the row

        # Prompt the admin for a new price
        new_price = input("Enter new price in pence: ").strip()

        # Validate that the new price is a number
        if not new_price.isdigit():
            print("Price must be a number.")
            return  # Exit if invalid input

        # Update the price in the selected ticket
        selected['topup_price_in_pence'] = new_price

        # Save the updated categories and tickets back to the CSV
        save_categories(data)

        # Notify the admin that the price was successfully updated
        print(f"Price updated successfully for '{selected['topup_title']}'.")

    except ValueError:
        # Handle case where input cannot be converted to an integer
        print("Invalid input.")

        
# Admin Menu Loop
def admin_menu():
    while True:
        print("\n--- Admin Menu ---")
        print("1. View Categories")
        print("2. Add Category")
        print("3. Remove Category")
        print("4. View Purchases")
        print("5. Edit Ticket Price")
        print("6. Exit Admin Menu")
        
        choice = input("Enter your choice: ")
        if choice == '1':
            view_categories()
        elif choice == '2':
            add_category()
        elif choice == '3':
            remove_category()
        elif choice == '4':
            view_purchases()
        elif choice == '5':
            edit_ticket_price()
        elif choice == '6': 
            break
        else:
            print("Invalid choice. Please enter 1-6.")
