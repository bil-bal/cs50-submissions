import csv
import cs50
from sys import argv, exit


def main():

    db = cs50.SQL("sqlite:///students.db")

    if len(argv) != 2:
        print("Incorrect number of arguments.")
        exit(1)

    with open(argv[1], "r") as file:
        reader = csv.DictReader(file)

        for row in reader:
            name = row["name"].split(" ")

            if len(name) == 3:
                first = name[0]
                middle = name[1]
                last = name[2]
            elif len(name) == 2:
                first = name[0]
                middle = None
                last = name[1]

            house = row["house"]
            birth = row["birth"]

            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       first, middle, last, house, birth)


main()
exit(0)