from cs50 import get_string
import re
import string

text = get_string("Text: ")
t = re.sub(r"['-]", "", text)

# Counts number of words in input string
# Taken from https://www.geeksforgeeks.org/python-program-to-count-words-in-a-sentence/
words = len(re.findall(r'\w+', t))
print(f'words: {words}')

# Counts number of letter in input string
letters = len(re.findall(r'\w', t))
print(f'letters: {letters}')

# Counts number of sentences in input string
sentences = len(re.findall(r'[.!?]', t))
print(f'sentences: {sentences}')

# Calculates Coleman-Liau Index
l = (letters / words) * 100
s = (sentences / words) * 100
index = round(0.0588 * l - 0.296 * s - 15.8)

# Output Grade Level
if index < 1:
    print('Before Grade 1')

elif index >= 1 and index <= 16:
    print(f'Grade {index}')

else:
    print('Grade 16+')