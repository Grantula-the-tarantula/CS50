from csv import reader, DictReader
from sys import argv

# Checks for valid command line arguments
if len(argv) != 3:
    print('Usage: python dna.py data.csv sequence.txt')
    exit()

# Import csv and text file into memory

# dictionary to store the str's
strs = {}

with open(argv[1]) as data_file:
    database = reader(data_file)
    for row in database:
        dna_str = row
        dna_str.pop(0)
        break

# Dictionary to store the str values
for item in dna_str:
    strs[item] = 1


with open(argv[2]) as dna_file:
    dna_read = reader(dna_file)
    for row in dna_read:
        dna_seq = row

# string to store the given dna sequence
dna = dna_seq[0]
# print(f'{dna}')


# Iterate through given dna sequence for each STR value
for key in strs:
    l = len(key)
    counter_MAX = 0
    counter = 0

    # Iterate through dna sequence to count max repeats
    for i in range(len(dna)):

        while counter > 0:
            counter -= 1
            continue

        if dna[i: i + l] == key:
            while dna[i - l: i] == dna[i: i + l]:
                counter += 1
                i += l
                # print(f'{counter}')

            if counter > counter_MAX:
                counter_MAX = counter

    # Adds max str values to be compared to people later
    strs[key] += counter_MAX
    # print(f'{strs[key]}')


# Compare Repeat values to database and check for matches
with open(argv[1], newline='') as file:
    people = DictReader(file)

    for person in people:
        counter = 0

        for dna in strs:
            if strs[dna] == int(person[dna]):
                counter += 1
                # print(f"{counter}")

        if counter == len(strs):
            print(person["name"])
            exit()

    print('No Match')