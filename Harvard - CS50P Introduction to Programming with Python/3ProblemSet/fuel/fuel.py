"""
Fuel Gauge
Fuel gauges indicate, often with fractions, just how much fuel is in a tank. For instance 1/4 indicates that a tank is 25% full, 1/2 indicates that a tank is 50% full, and 3/4 indicates that a tank is 75% full.

In a file called fuel.py, implement a program that prompts the user for a fraction, formatted as X/Y, wherein each of X and Y is an integer, and then outputs, as a percentage rounded to the nearest integer, how much fuel is in the tank. If, though, 1% or less remains, output E instead to indicate that the tank is essentially empty. And if 99% or more remains, output F instead to indicate that the tank is essentially full.

If, though, X or Y is not an integer, X is greater than Y, or Y is 0, instead prompt the user again. (It is not necessary for Y to be 4.) Be sure to catch any exceptions like ValueError or ZeroDivisionError.
"""
def main():
    while True:
        try:
            user_input = input("Fraction: ")
            x, y = user_input.split("/")

            # Remove whitespaces if user input 'x / y' instead of 'x/y' and convert to int data types
            x = int(x.strip())
            y = int(y.strip())

            xy = round(x / y * 100)  # Here is converted to float due to division, using round() to turn back to integer
        except ValueError:
            print("ValueError: Not a valid integer fraction")
        except ZeroDivisionError:
            print("ZeroDivisionError: Zero division")
        else:
            if xy < 0 or xy > 100:
                main()              # Calls main() again and re-start if the inputted x is bigger than y which results in value beyond 100
                break
            elif xy <= 1:
                print("E")
            elif xy >= 99:
                print("F")
            else:
                print(f"{xy}%")
            break

if __name__ == "__main__":
    main()