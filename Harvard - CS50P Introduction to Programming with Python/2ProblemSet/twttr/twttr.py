"""
Just setting up my twttr
When texting or tweeting, it’s not uncommon to shorten words to save time or space, as by omitting vowels, much like Twitter was originally called twttr. 
In a file called twttr.py, implement a program that prompts the user for a str of text and then outputs that same text but with all vowels (A, E, I, O, and U) omitted, 
whether inputted in uppercase or lowercase.
"""

def main():
    vowels = ["a", "e", "i", "o", "u"]
    user_input = input("Input: ")
    if user_input:
        for char in user_input:
            for v in vowels:
                if v == char.casefold():
                    user_input = user_input.replace(char, "")
                else:
                    continue
    else:
        print("Invalid input")

    print(f"Output: {user_input}")

if __name__ == "__main__":
    main()