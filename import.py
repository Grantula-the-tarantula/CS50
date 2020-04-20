from cs50 import SQL
import csv
from sys import argv

# Check command-line arguments
if len(argv) != 2:
    print('Usage: python import.py characters.csv')
    exit()

# Create Database
open("students.db", "w").close()
db = SQL("sqlite:///students.db")

# Create Tables
db.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth INT)")

# Open CSV file given by command-line argument
with open(argv[1], "r") as students:

    # Create DictReader
    reader = csv.DictReader(students, delimiter=",")

    # Iterate over csv file
    for row in reader:

        # parse each students name if they have a middle name
        if len(row['name'].split()) == 3:
            first = row['name'].split()[0]
            middle = row['name'].split()[1]
            last = row['name'].split()[2]

        # parse each students name with no middle name
        if len(row['name'].split()) == 2:
            first = row['name'].split()[0]
            middle = None
            last = row['name'].split()[1]

        # Insert each student into the students table of students.db
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   first, middle, last, row['house'], row['birth'])