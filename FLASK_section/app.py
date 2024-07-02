from cs50 import SQL
from flask import Flask, render_template, request
from helpers import random_string
import random

app = Flask(__name__)

db = SQL("sqlite:///history.db")

app.config["TEMPLATES_AUTO_RELOAD"] = True

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        page = request.form.get("page")

        try:
            page = int(page)
        except ValueError:
            return render_template("index.html", placeholder="Enter A Number")

        if page < 0:
            return render_template("index.html", placeholder="Wrong Input, Try Again")
        random.seed(page)
    string = random_string(1000)
    request.form.get("page")
    return render_template("index.html", placeholder=string, name="Nikola")

number = 4

  db.execute("INSTER INTO history (page) VALUES (?);", number)
# Returns list of rows as Dictionaries !!!!!!!
  rows = db.execute("SELECT * FROM history;")