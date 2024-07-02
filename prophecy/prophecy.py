from cs50 import SQL
import csv

data_base = SQL("sqlite:///roster.db")

with open("students.csv", "r") as file:
    reader = csv.DictReader(file)
    for i in reader:
        data_base.execute("INSERT INTO students (student_name) VALUES(?)", i["student_name"])

        data_base.execute("INSERT INTO houses (house, head) VALUES(?, ?)", i["house"], i["head"])

        student_id = data_base.execute("SELECT id AS n FROM students WHERE student_name = ?", i["student_name"])[0]['n']
        house_id = data_base.execute("SELECT id AS n FROM houses WHERE house = ?", i["house"])[0]['n']

        data_base.execute("INSERT INTO assignments (students_id, house_id) VALUES(?, ?)", student_id, house_id)