from sys import argv, exit
from csv import reader
from collections import deque
import re


def main():
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    l = []

    k = []
    with open(argv[1], "r") as f:
        db = reader(f)
        with open(argv[2], "r") as s:
            seq = s.read()

            for row in db:
                l.append(row)

            for i in l[0]:
                k.append(i)

            result = ['name']

            for _ in range(1, len(k)):
                result.append(0)

            for m in range(1, len(k)):
                n = 1
                while k[m]*n in seq:
                    n += 1

                if (n - 1) > result[m]:
                    result[m] = n - 1

    check = [" "]
    for ch in range(1, len(result)):
        check.append(False)

    for r in range(1, len(l)):
        for res in range(1, len(result)):
            if result[res] == int(l[r][res]):
                check[res] = True
            else:
                check[res] = False
        if not False in check:
            print(l[r][0])
            exit(0)
    print("No match")
    exit(1)


main()
