"""
Little Professor
One of David’s first toys as a child, funny enough, was Little Professor, a “calculator” that would generate ten different math problems for David to solve. 
For instance, if the toy were to display 4 + 0 = , David would (hopefully) answer with 4. If the toy were to display 4 + 1 = , David would (hopefully) answer with 5. 
If David were to answer incorrectly, the toy would display EEE. And after three incorrect answers for the same problem, the toy would simply display the correct answer (e.g., 4 + 0 = 4 or 4 + 1 = 5).

In a file called professor.py, implement a program that:

Prompts the user for a level, n. If the user does not input 1, 2, or 3, the program should prompt again.
Randomly generates ten (10) math problems formatted as X + Y = , wherein each of X and Y is a non-negative integer with n digits. No need to support operations other than addition (+).
Prompts the user to solve each of those problems. If an answer is not correct (or not even a number), the program should output EEE and prompt the user again, allowing the user up to three tries in total for that problem. 
If the user has still not answered correctly after three tries, the program should output the correct answer.
The program should ultimately output the user’s score: the number of correct answers out of 10.
Structure your program as follows, wherein get_level prompts (and, if need be, re-prompts) the user for a level and returns 1, 2, or 3, 
and generate_integer returns a randomly generated non-negative integer with n level digits or raises a ValueError if level is not 1, 2, or 3:
"""
import random

def main():
    try:
        problems = 0
        correct_answers = 0
        level = get_level()

        while problems != 10:
            problems += 1
            tries = 0
            integer_one = generate_integer(level)
            integer_two = generate_integer(level)
            result = integer_one + integer_two

            user_answer = int(input(f"{integer_one} + {integer_two} = "))
            tries += 1
            while user_answer != result and tries != 3:
                print("EEE")
                tries += 1
                user_answer = int(input(f"{integer_one} + {integer_two} = "))

            if tries == 3:
                print("EEE")
                print(f"{integer_one} + {integer_two} = {result}")
            elif user_answer == result:
                correct_answers += 1

        print(f"Score: {correct_answers}")

    except ValueError:
        print("ValueError: Not a valid integer")

def get_level():
    try:
        user_input = int(input("Level: "))

        while user_input < 1 and user_input > 3:
            user_input = int(input("Level: "))

        return user_input
    
    except ValueError:
        print("ValueError: Not a valid integer")


def generate_integer(level):
    if level == 1:
        random_integer = random.randint(0, 9)
    elif level == 2:
        random_integer = random.randint(10, 99)
    elif level == 3:
        random_integer = random.randint(100, 999)
    else:
        raise ValueError("Not 1, 2 or 3")
    return random_integer


if __name__ == "__main__":
    main()