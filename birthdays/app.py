import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        # TODO: Add the user's entry into the database

        # Get data from a user
        name = request.form.get("name")
        day = request.form.get("day")
        month = request.form.get("month")

        # Name must be a string  and month and day integers
        if name.isalpha() and day.isnumeric() and month.isnumeric():
           # Adding new birthday to database
           db.execute("INSERT INTO birthdays (name, month, day) VALUES(?, ?, ?);", name, month, day)
           return redirect("/")

        else:
           return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html

        # Selecting entire data base to list it on homepage
        all_birthdays = db.execute("SELECT * FROM birthdays;")

        # Inserting list of birthdays to index.html
        return render_template("index.html", birthdays=all_birthdays)

# Added route to remove a birthday from data base and list
@app.route("/remove", methods=["GET", "POST"])
def remove():
    # Takes a name from a user and removes a person from Data base
    remove_name = request.form.get("remove_name")
    print(db.execute("SELECT * FROM birthdays WHERE name=?;", remove_name))
    # Ensures user gave correct name
    if remove_name and remove_name.isalpha():
        # Checks if there is a given name in our data base
        if not db.execute("SELECT * FROM birthdays WHERE name=?;", remove_name):
            return redirect("/")
        else:
            # Delete name from data base and redirects to homepage
            db.execute("DELETE FROM birthdays WHERE name=?;", remove_name)
            return redirect("/")
    else:
        return redirect("/")
