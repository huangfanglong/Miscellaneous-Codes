"""
Suppose that you’re in a country where it’s customary to eat breakfast between 7:00 and 8:00, lunch between 12:00 and 13:00, and dinner between 18:00 and 19:00. 
Wouldn’t it be nice if you had a program that could tell you what to eat when?

In meal.py, implement a program that prompts the user for a time and outputs whether it’s breakfast time, lunch time, or dinner time. 
If it’s not time for a meal, don’t output anything at all. Assume that the user’s input will be formatted in 24-hour time as #:## or ##:##. And assume that each meal’s time range is inclusive. 
For instance, whether it’s 7:00, 7:01, 7:59, or 8:00, or anytime in between, it’s time for breakfast.

Structure your program per the below, wherein convert is a function (that can be called by main) that converts time, a str in 24-hour format, to the corresponding number of hours as a float. 
For instance, given a time like "7:30" (i.e., 7 hours and 30 minutes), convert should return 7.5 (i.e., 7.5 hours).
"""
def main():
    # Prompt for input, lowercase all letters for 12 hours format specific to lessen uppercase/lowercase checks
    userInput = input("What time is it? ").casefold()
    ## Check if 12 hours format
    if userInput.endswith("a.m") or userInput.endswith("p.m") or userInput.endswith("am") or userInput.endswith("pm"):
        # Remove 'am' and 'pm' from the userInput string without having to account for space or no space between ##:## and the meridiem
        if "am" or "a.m" in userInput:
            meridiem = "am"
            userInput = userInput.replace(".", "")
            userInput = userInput.replace("am", "")
        elif "pm" or "p.m" in userInput:
            meridiem = "pm"
            userInput = userInput.replace(".", "")
            userInput = userInput.replace("am", "")

        convertedTime = convert(userInput)
        if meridiem == "am":
            if convertedTime >= 7.00 and convertedTime <= 8.00:
                print("breakfast time")
            else:
                pass
        else:
            if convertedTime >= 12.00 and convertedTime <= 13.00:
                print("lunch time")
            elif convertedTime >= 6.00 and convertedTime <= 7.00:
                print("dinner time")

    ## Otherwise 24 hours format
    else:
        convertedTime = convert(userInput)
        if convertedTime >= 7.00 and convertedTime <= 8.00:
            print("breakfast time")
        elif convertedTime >= 12.00 and convertedTime <= 13.00:
            print("lunch time")
        elif convertedTime >= 18.00 and convertedTime <= 19.00:
            print("dinner time")

def convert(time):
    hour, minute = time.split(":")
    return float(hour) + (float(minute) / 60 * 1)

if __name__ == "__main__":
    main()