from cs50 import get_string
import re

s = get_string("Text: ")
regex = re.compile('[^a-zA-Z]')

L = len(regex.sub("", s))

W = len(re.split(" ", s))

S = len(re.split("! |\. |\? ", s))

index = round(0.0588 * ((L / W) * 100) - 0.296 * ((S / W) * 100) - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")