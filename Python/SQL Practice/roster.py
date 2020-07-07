import cs50
from sys import argv, exit


def main():
    if len(argv) != 2:
        print("Incorrect number of arguments.")
        exit(1)

    db = cs50.SQL("sqlite:///students.db")

    data = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

    for i in data:
        first = i["first"]
        middle = i["middle"]
        last = i["last"]

        birth = i["birth"]

        if middle is not None:
            print(f"{first} {middle} {last}, born {birth}")
        else:
            print(f"{first} {last}, born {birth}")


main()
exit(0)