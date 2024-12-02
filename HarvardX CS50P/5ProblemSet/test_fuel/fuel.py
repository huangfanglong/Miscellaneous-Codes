"""
Fuel Gauge
Fuel gauges indicate, often with fractions, just how much fuel is in a tank. For instance 1/4 indicates that a tank is 25% full, 1/2 indicates that a tank is 50% full, and 3/4 indicates that a tank is 75% full.

In a file called fuel.py, implement a program that prompts the user for a fraction, formatted as X/Y, wherein each of X and Y is an integer, and then outputs, as a percentage rounded to the nearest integer, how much fuel is in the tank. If, though, 1% or less remains, output E instead to indicate that the tank is essentially empty. And if 99% or more remains, output F instead to indicate that the tank is essentially full.

If, though, X or Y is not an integer, X is greater than Y, or Y is 0, instead prompt the user again. (It is not necessary for Y to be 4.) Be sure to catch any exceptions like ValueError or ZeroDivisionError.
"""
def main():
    user_input = input("Fraction: ")
    output = gauge(convert(user_input))
    if (output != None):
        print(output)
    else:
        pass


def convert(fraction):
    try:
        x, y = fraction.split("/")
        # Remove whitespaces if user input 'x / y' instead of 'x/y' and convert to int data types
        x = int(x.strip())
        y = int(y.strip())
        xy = round(x / y * 100)  # Here is converted to float due to division, using round() to turn back to integer
        return xy
    except ValueError:          # Let gauge(percentage) function handle the invalid value input
        return None
    except ZeroDivisionError:   # Let gauge(percentage) function handle the zero division error
        return None


def gauge(percentage):
    try:
        # Handle invalid input and zero division
        if percentage < 0 or percentage > 100:
            main()              # Calls main() again and re-start if the inputted x is bigger than y which results in value beyond 100
            return None
        elif percentage <= 1:
            return("E")
        elif percentage >= 99:
            return("F")
        else:
            return(f"{percentage}%")
    except TypeError:           # Calls main() again and re-start if the user input is not a valid integer
        main()
        return None

if __name__ == "__main__":
    main()