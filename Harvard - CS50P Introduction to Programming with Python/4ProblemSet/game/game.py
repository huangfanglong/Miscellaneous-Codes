"""
I’m thinking of a number between 1 and 100…

What is it?
It’s 50! But what if it were more random?

In a file called game.py, implement a program that:

Prompts the user for a level, n. If the user does not input a positive integer, the program should prompt again.
Randomly generates an integer between 1 and n, inclusive, using the random module.
Prompts the user to guess that integer. If the guess is not a positive integer, the program should prompt the user again.
If the guess is smaller than that integer, the program should output Too small! and prompt the user again.
If the guess is larger than that integer, the program should output Too large! and prompt the user again.
If the guess is the same as that integer, the program should output Just right! and exit.
"""
from random import choice

def main():
    try:
        user_input = int(input("Level: "))
        while user_input < 0:
            user_input = int(input("Level: "))

        random_integer = choice(range(1, user_input + 1))

        user_input = int(input("Guess: "))

        while user_input < random_integer:
            print("Too small!")
            user_input = int(input("Guess: "))
        while user_input > random_integer:
            print("Too large!")
            user_input = int(input("Guess: "))
        if user_input == random_integer:
            print("Just right!")
            exit()

    except ValueError:
        print("ValueError: Not a valid number")
    except IndexError:
        print("IndexError: Invalid index range of sequence (negative number?)")
    except KeyboardInterrupt:
        exit()
    except EOFError:
        exit()

if __name__ == "__main__":
    main()

