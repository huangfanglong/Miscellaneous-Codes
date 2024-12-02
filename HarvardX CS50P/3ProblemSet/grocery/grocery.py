"""
Grocery List
Suppose that you’re in the habit of making a list of items you need from the grocery store.

In a file called grocery.py, implement a program that prompts the user for items, one per line, until the user inputs control-d 
(which is a common way of ending one’s input to a program). 
Then output the user’s grocery list in all uppercase, sorted alphabetically by item, prefixing each line with the number of times the user inputted that item. 
No need to pluralize the items. Treat the user’s input case-insensitively.
"""

def main():
    grocery_list = {}
    while True:
        try:
            user_input = input().upper()

            # Check if item entered is already in the list
            # Increment value by 1 if it is
            if user_input in grocery_list:
                grocery_list[user_input] += 1
            # Else add the user_input key to the grocery_list and assign it a value of 1
            else:
                grocery_list[user_input] = 1

        except KeyError:
            print("")
        except KeyboardInterrupt:
            for item, count in sorted(grocery_list.items()):
                print(f"{count} {item}")
            exit()


if __name__ == "__main__":
    main()