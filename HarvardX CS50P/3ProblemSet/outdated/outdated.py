"""
In the United States, dates are typically formatted in month-day-year order (MM/DD/YYYY), otherwise known as middle-endian order, which is arguably bad design. 
Dates in that format can’t be easily sorted because the date’s year comes last instead of first. 
Try sorting, for instance, 2/2/1800, 3/3/1900, and 1/1/2000 chronologically in any program (e.g., a spreadsheet). 
Dates in that format are also ambiguous. Harvard was founded on September 8, 1636, but 9/8/1636 could also be interpreted as August 9, 1636!

Fortunately, computers tend to use ISO 8601, an international standard that prescribes that dates should be formatted in year-month-day (YYYY-MM-DD) order, 
no matter the country, formatting years with four digits, months with two digits, and days with two digits, “padding” each with leading zeroes as needed.

In a file called outdated.py, implement a program that prompts the user for a date, anno Domini, in month-day-year order, formatted like 9/8/1636 or September 8, 1636, 
wherein the month in the latter might be any of the values in the list below:
"""

def main():
    alphabetical_month_list = [
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
    ]

    try:
        user_input = input("Date: ").strip().capitalize()

        if user_input[0].isdigit():
            month, day, year = user_input.split("/")

            # If invalid month or date
            while int(month) > 12 or int(day) > 31:
                user_input = input("Date: ").strip().capitalize()
                month, day, year = user_input.split("/")

            print(f"{year}-{int(month):02}-{int(day):02}")

        else:
            non_numeric_month, day, year = user_input.split()
            day = day.strip(",")

            if non_numeric_month in alphabetical_month_list:
                month = alphabetical_month_list.index(non_numeric_month) + 1
                print(f"{year}-{int(month):02}-{int(day):02}")

    except ValueError:
        print("ValueError: Invalid input value")
    except KeyboardInterrupt:
        print("Exitting")
        exit()

if __name__ == "__main__":
    main()