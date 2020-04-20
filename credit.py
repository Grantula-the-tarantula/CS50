from cs50 import get_int
import math

# prompts user to enter credit card number
# checks for valid entry

while True:
    n = get_int("Number: ")

    if n > 9999999999999999 or n < 1000000000000:
        print("INVALID")
        exit(0)

    if n > 1000000000000 and n < 9999999999999999:
        break

m = n
c = n
b = m
i = 10
sum1 = 0
sum2 = 0

# Checksum Test
# Checking Second Digit (from right)
while n > 0:
    n = math.floor(n / i)
    num = math.floor((n % 10) * 2)
    i = 100

    if num > 9:
        num = math.floor((num % 10) + 1)

    else:
        num = num + 0

    sum1 += num

# Checking First Digits (from right)
while m > 0:
    sum2 += math.floor(m % 10)
    m = m / i

# Checksum Test
checksum = (sum1 + sum2) % 10

while c > 100:
    c = c / 10
    digits = math.floor(c % 100)

while b > 10:
    b = b / 10
    digit = math.floor(b % 10)

# Outputting the Brand of the Card
if (digits == 34 or digits == 37) and checksum == 0:
    print("AMEX")

elif digit == 4 and checksum == 0:
    print("VISA")

elif (digits == 51 or digits == 52 or digits == 53 or digits == 54 or digits == 55) and checksum == 0:
    print("MASTERCARD")

else:
    print("INVALID")