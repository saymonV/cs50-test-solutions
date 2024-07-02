CREATE TABLE students (
    id INTEGER NOT NULL,
    student_name TEXT NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE houses (
    id INTEGER NOT NULL,
    house TEXT NOT NULL,
    head TEXT NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE assignments (
  students_id INTEGER NOT NULL,
  house_id INTEGER NOT NULL,
  FOREIGN KEY (students_id) REFERENCES students(id),
  FOREIGN KEY (house_id) REFERENCES houses(id),
  PRIMARY KEY (students_id, house_id)
);