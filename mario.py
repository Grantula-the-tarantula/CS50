from cs50 import get_int

while True:
    # prompts user for pyramid height
    h = get_int("Height: ")
    # checks that input height is in range
    if h > 0 and h <= 8:
        break

m = h - 1
b = 1

# outer loop for rows
# inner loop for columns
for i in range(h):

    for j in range(m):
        print(" ", end="")

    m -= 1

    for k in range(b):
        print("#", end="")

    for q in range(2):
        print(" ", end="")

    for z in range(b):
        print("#", end="")

    b += 1

    print("")