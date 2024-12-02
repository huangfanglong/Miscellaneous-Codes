"""
Vanity Plates
In Massachusetts, home to Harvard University, it’s possible to request a vanity license plate for your car, with your choice of letters and numbers instead of random ones. 
Among the requirements, though, are:

“All vanity plates must start with at least two letters.”
“… vanity plates may contain a maximum of 6 characters (letters or numbers) and a minimum of 2 characters.”
“Numbers cannot be used in the middle of a plate; they must come at the end. For example, AAA222 would be an acceptable … vanity plate; AAA22A would not be acceptable. 
The first number used cannot be a ‘0’.”
“No periods, spaces, or punctuation marks are allowed.”
In plates.py, implement a program that prompts the user for a vanity plate and then output Valid if meets all of the requirements or Invalid if it does not. 
Assume that any letters in the user’s input will be uppercase. Structure your program per the below, 
wherein is_valid returns True if s meets all requirements and False if it does not. Assume that s will be a str. 
You’re welcome to implement additional functions for is_valid to call (e.g., one function per requirement).
"""

def main():
    plate = input("Plate: ")
    if is_valid(plate):
        print("Valid")
    else:
        print("Invalid")


### TO DO
def is_valid(s):
    if len(s) < 2:
        return False
    
    elif s[0].isdigit() or s[1].isdigit():
        return False

    elif len(s) <= 6:
        if is_minimum_two_characters(s) == False:
            return False
        elif is_first_number_a_zero(s) == True:
            return False
        elif is_number_in_middle(s) == True:
            return False
        elif is_special_character(s) == True:
            return False
        else:
            return True
        
    else:
        return False
            
### SELF-ADDED (LONG FANG HUANG/LONG PHUONG HUYNH) ###
def is_minimum_two_characters(s):
    # letters = 0                   # Seems it is not necessary for 2 min chars to be numbers unless I read it incorrectly - LFH
    # for index in s:
    #     if not index.isdigit():
    #         letters += 1
    
    # if letters < 2:
    #     return False
    # else:
    #     return True
    if len(s) < 2:
        return False
    else:
        return True

def is_first_number_a_zero(s):
    for index in s:
        if index.isdigit():
            first_number = index
            break
        else:
            continue
    
    if(first_number):
        if first_number == "0":
            return True
        else:
            return False
    else:
        return False

def is_number_in_middle(s):
    last_character = len(s) - 1
    if not s[last_character].isdigit():
        return True
    else:
        return False
    

def is_special_character(s):
    for index in s:
        if not index.isalnum():
            return True
    return False

if __name__ == "__main__":
    main()