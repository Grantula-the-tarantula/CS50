# TODO
from cs50 import SQL
import csv
from sys import argv

# check command line arguments
if len(argv) != 2:
    print('Usage: python roster.py House')
    exit()

# Establish database connection
db = SQL("sqlite:///students.db")

# Query Database for all students in house
query = db.execute('SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first', argv[1])

# Print out each student's full name and birth year (sorted alphabetically by last name and then first name)
for row in query:
    if row['middle'] == None:
        print(f'{row["first"]} {row["last"]}, born {row["birth"]}')

    else:
        print(f'{row["first"]} {row["middle"]} {row["last"]}, born {row["birth"]}')