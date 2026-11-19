# Bus ticket Python Project
## Use case 5: Administrator - Viewing Categories 
### Actors 
- Administrator
### Preconditions
- Admin password is entered correctly.
### Trigger 
- Admin selects "View Categories" in admin menu.
### Main Flow
- System loads all categories from mobile_products.csv.
- System displays each category with description.
### Postconditions
- Admin can see all existing categories.

## Use Case 6: Administrator - Adding Category
### Actors 
- Administrator
### Preconditions 
- Admin is logged in.
### Trigger
- Admin selects "Add Category".
### Main Flow
- Admin inputs category title and description.
- System generates 3–5 default top-ups with random titles, descriptions, and prices.
- System saves new category and top-ups to CSV.
### Postconditions
- New category is added with default tickets.
- Confirmation message displayed.

## Use Case 7: Administrator - Removing Category
### Actors 
- Administrator
### Preconditions 
- Admin is logged in.
### Trigger
- Admin selects "Remove Category".
### Main Flow
- System displays all categories.
- Admin inputs category title to remove.
- System deletes category and associated top-ups from CSV.
### Postconditions
- Category and all related tickets removed.
- Confirmation message displayed.

## Use Case 8: Administrator – Editing Ticket Price

### Actors 
- Administrator
### Preconditions
- Admin is logged in and categories exist.
### Trigger: 
- Admin selects "Edit Ticket Price".
### Main Flow:
- System displays all tickets with current prices.
- Admin selects a ticket by number.
- Admin enters new price in pence.
- System updates price in CSV.
### Postconditions
- Ticket price updated.
- Confirmation message displayed.

## Use Case 9: Administrator – Viewing Purchases
### Actors 
- Administrator
### Preconditions
- Purchases exist in purchases.csv.
### Trigger
- Admin selects "View Purchases".
### Main Flow
- System reads all purchases from CSV.
- System displays each purchase.
- System calculates total revenue and total tickets sold.
- System counts tickets sold per type.
### Postconditions
- Admin sees
-- Total tickets sold
-- Tickets sold per type
-- Total purchase amount 
