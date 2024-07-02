from flask import Flask, render_template, request

app = Flask(__name__)

REGISTRANTS = {}

SPORTS = [
   "Basketball",
   "Soccer",
   "Ultimate Frisbee"
]


@app.route("/")
def index():
  return render_template("index.html", sports=SPORTS)


@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    if not name:
       return render_template("failure.html")
    sport = request.form.get("sport")
    if sport not in SPORTS:
        return render_template("failure.html")

    #DB save
    db.execute("INSTER INTO registrants (name, sport) VALUES(?, ?)", name, sport)


    REGISTRANTS[name] = sport
    return render_template("success.html")



#@app.route("/registrants")
#def registrants():
#   return render_template("registrants.html", registrants=REGISTRANTS)




@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html", registrants=registrants)