"""
Scourgify
“Ah, well,” said Tonks, slamming the trunk’s lid shut, “at least it’s all in. That could do with a bit of cleaning, too.” She pointed her wand at Hedwig’s cage. “Scourgify.” A few feathers and droppings vanished.

— Harry Potter and the Order of the Phoenix

Data, too, often needs to be “cleaned,” as by reformatting it, so that values are in a consistent, if not more convenient, format. Consider, for instance, this CSV file of students, before.csv.
Source: en.wikipedia.org/wiki/List_of_Harry_Potter_characters

Even though each “row” in the file has three values (last name, first name, and house), the first two are combined into one “column” (name), escaped with double quotes, with last name and first name separated by a comma and space. 
Not ideal if Hogwarts wants to send a form letter to each student, as via mail merge, since it’d be strange to start a letter with:

Dear Potter, Harry,

Rather than with, for instance:

Dear Harry,

In a file called scourgify.py, implement a program that:

Expects the user to provide two command-line arguments:
the name of an existing CSV file to read as input, whose columns are assumed to be, in order, name and house, and
the name of a new CSV to write as output, whose columns should be, in order, first, last, and house.
Converts that input to that output, splitting each name into a first name and last name. Assume that each student will have both a first name and last name.
If the user does not provide exactly two command-line arguments, or if the first cannot be read, the program should exit via sys.exit with an error message.
"""
import csv
import sys

def main():
    # if not len(sys.argv) == 3:
    #     sys.exit("Too few arguments: python scourgify.py [CSV FILE PATH TO OPEN] [CSV FILE PATH TO WRITE TO]")
    if len(sys.argv) > 3:
        sys.exit("Too many command-line arguments")
    elif len(sys.argv) < 3:
        sys.exit("Too few command-line arguments")

    read_csv_file_path  = sys.argv[1]
    write_csv_file_path = sys.argv[2]

    if not read_csv_file_path.endswith(".csv") and not write_csv_file_path.endswith(".csv"):
        sys.exit("Not a CSV file")

    try:
        with open(read_csv_file_path) as read_csv_file:
            reader = csv.DictReader(read_csv_file, fieldnames=["name", "house"])

            # "DictReader() produces a sequence of dictionaries, not just one dictionary." - Martijn Pieters, StackOverflow
            # So can't iterate for "keys, values" pair via reader directly
            for row in reader:
                if row["name"] != "name":                               # Ignore the first row of field names
                    last_name, first_name = row["name"].split(",")
                    house = row["house"]

                    with open(write_csv_file_path, "a", newline='') as write_csv_file:
                        writer = csv.DictWriter(write_csv_file, fieldnames=["first", "last", "house"])
                        writer.writerow({"first": first_name, "last": last_name, "house": house})

    except FileNotFoundError:
        sys.exit(f"FileNotFoundError: Could not read {read_csv_file_path}")

if __name__ == "__main__":
    main()