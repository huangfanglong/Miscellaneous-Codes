"""
Whereas most countries use a 24-hour clock, the United States tends to use a 12-hour clock. Accordingly, instead of “09:00 to 17:00”, 
many Americans would say they work “9:00 AM to 5:00 PM” (or “9 AM to 5 PM”), wherein “AM” is an abbreviation for “ante meridiem” and “PM” is an abbreviation for “post meridiem”,
 wherein “meridiem” means midday (i.e., noon).

In a file called working.py, implement a function called convert that expects a str in any of the 12-hour formats below and returns the corresponding str in 24-hour format 
(i.e., 9:00 to 17:00). Expect that AM and PM will be capitalized (with no periods therein) and that there will be a space before each. 
Assume that these times are representative of actual times, not necessarily 9:00 AM and 5:00 PM specifically.

9:00 AM to 5:00 PM
9 AM to 5 PM
9:00 AM to 5 PM
9 AM to 5:00 PM
Raise a ValueError instead if the input to convert is not in either of those formats or if either time is invalid (e.g., 12:60 AM, 13:00 PM, etc.). 
But do not assume that someone’s hours will start ante meridiem and end post meridiem; someone might work late and even long hours (e.g., 5:00 PM to 9:00 AM).

Structure working.py as follows, wherein you’re welcome to modify main and/or implement other functions as you see fit, but you may not import any other libraries. 
You’re welcome, but not required, to use re and/or sys.
"""
import re
import sys


def main():
    print(convert(input("Hours: ").strip()))


def convert(s):
    # ([1-9]|1[0-2])    = 1 - 12
    # 02d               = prefix 0 if number of digits is less than 2
    try:
        if match := re.search(r"^([1-9]|1[0-2])\:?([0-5][0-9])?\s?(AM|PM) to ([1-9]|1[0-2])\:?([0-5][0-9])?\s?(AM|PM)$", s):
            if match.group(3) == "AM":
                hour1 = int(match.group(1))
            else:
                hour1 = int(match.group(1)) + 12
            if match.group(6) == "AM":
                hour2 = int(match.group(4))
            else:
                hour2 = int(match.group(4)) + 12

            minute1 = match.group(2)
            minute2 = match.group(5)

            if minute1 == None:
                minute1 = "00"
            if minute2 == None:
                minute2 = "00"
            return f"{hour1:02d}:{minute1} to {hour2:02d}:{minute2}"
        else:
            raise ValueError
    except ValueError:
        sys.exit("ValueError: incorrect values entered")


...


if __name__ == "__main__":
    main()