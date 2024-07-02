import os
import datetime


from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if request.method == "GET":
        current_user = session["user_id"]
        # Selecting cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?;", current_user)[0].get(
            "cash"
        )
        # Selecting portoflio
        portfolio = db.execute(
            "SELECT * FROM portfolios WHERE user_id=?;", current_user
        )

        sum = 0
        # Looking up current stock value of users stocks
        for entry in portfolio:
            entry["price"] = lookup(entry["symbol"])["price"]
            entry["total"] = entry["shares"] * entry["price"]
            sum += entry["total"]
        # Value of owned stocks added to users cash
        sum += cash
        # Display homepage with users information
        return render_template("index.html", cash=cash, portfolio=portfolio, sum=sum)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        # Ensures input from a user is valid and in range
        if not request.form.get("symbol") or not lookup(request.form.get("symbol")):
            return apology("Invalid stock symbol")

        elif not request.form.get("shares"):
            return apology("Invalid number of shares")
        # If input is valid proceed with the transaction
        try:
            # Get all data
            symbol = request.form.get("symbol").upper()
            shares = int(request.form.get("shares"))
            current_user = session["user_id"]
            cash = float(
                db.execute("SELECT cash FROM users WHERE id=?", current_user)[0].get(
                    "cash"
                )
            )
            # Look up current stock price
            price = float(lookup(symbol).get("price"))
            # Ensures user is giving valid input and has enough cash
            if shares < 1:
                return apology("Input a possitive number")

            elif shares * price > cash:
                return apology("Not enough money")

            else:
                # Time of transaction
                date = datetime.datetime.now()
                # Updates all tables in database
                db.execute(
                    "UPDATE users SET cash=? WHERE id=?;",
                    (cash - float(shares) * price),
                    current_user,
                )
                db.execute(
                    "INSERT INTO purchases (user_id, symbol, shares, price, time) VALUES(?, ?, ?, ?, ?);",
                    current_user,
                    symbol,
                    shares,
                    price,
                    date,
                )
                portfolio = db.execute(
                    "SELECT symbol, shares FROM portfolios WHERE user_id=? AND symbol=?;",
                    current_user,
                    symbol,
                )
                # If such a portfolio exists it is updated
                if portfolio:
                    user_shares = db.execute(
                        "SELECT shares FROM portfolios WHERE user_id=? AND symbol=?;",
                        current_user,
                        symbol,
                    )[0].get("shares")
                    db.execute(
                        "UPDATE portfolios SET shares=? WHERE user_id=? AND symbol=?;",
                        (user_shares + shares),
                        current_user,
                        symbol,
                    )
                # If it doesn't it is created
                else:
                    db.execute(
                        "INSERT INTO portfolios (user_id, symbol, shares) VALUES (? , ? , ?);",
                        current_user,
                        symbol,
                        shares,
                    )

                return redirect("/")
        # Render apology in case of invalid input
        except ValueError as e:
            return apology("Input a number")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    if request.method == "GET":
        # Selecting current users transaction history
        history = db.execute(
            "SELECT * FROM purchases WHERE user_id=? ORDER BY time DESC;",
            session["user_id"],
        )
        # If there was any it is displayed
        if history:
            return render_template("history.html", history=history)

        return render_template("history.html")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?;", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Checking user input
        if not request.form.get("symbol"):
            return apology("Please enter valid stock Symbol", 400)
        else:
            if not lookup(request.form.get("symbol")):
                return apology("Stock symbol not in our database")
            else:
                # Rendering lookup result to a user
                result = [lookup(request.form.get("symbol"))]
                print(result)
                return render_template("quoted.html", result=result)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # User must input in to username field
        if not request.form.get("username"):
            return apology("Enter new username", 400)
        # Check data base if same username already exists
        elif db.execute(
            "SELECT * FROM users WHERE username=?", request.form.get("username")
        ):
            return apology("Username taken")
        # Password
        elif not request.form.get("password"):
            return apology("Enter new password")
        # Password confirmation
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("You must re-enter same password")

        # Store username and hashed password in to database
        else:
            username = request.form.get("username")
            # Storing hashed password in data base
            password = generate_password_hash(
                request.form.get("password"), method="pbkdf2", salt_length=16
            )
            db.execute(
                "INSERT INTO users (username, hash) VALUES (?, ?)", username, password
            )
            return render_template("login.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        # Renders a page with drop down selection menu
        # Giving option to sell only owned stocks
        options = db.execute(
            "SELECT symbol FROM portfolios WHERE user_id=?", session["user_id"]
        )

        return render_template("sell.html", options=options)

    else:
        symbol = request.form.get("symbol")
        current_user = session["user_id"]
        # Selecting user portfolio
        portfolio = db.execute(
            "SELECT * FROM portfolios WHERE user_id=? AND symbol=?;",
            current_user,
            symbol,
        )
        # Double checking for shares
        if not portfolio:
            return apology("No shares on your portfolio")
        else:
            date = datetime.datetime.now()
            shares = float(request.form.get("shares"))
            portfolio_shares = portfolio[0]["shares"]
            # Ensures user can sell only owned amount
            if portfolio_shares >= shares:
                price = lookup(symbol).get("price")
                db.execute(
                    "UPDATE portfolios SET shares=? WHERE user_id=? AND symbol=?;",
                    (portfolio_shares - shares),
                    current_user,
                    symbol,
                )
                # Cash made from sales at current price
                cash = (
                    db.execute("SELECT cash FROM users WHERE id=?;", current_user)[
                        0
                    ].get("cash")
                ) + (price * shares)
                # Updating users cash
                db.execute("UPDATE users SET cash=? WHERE id=?", cash, current_user)
                # Adding transaction to purchases database for history
                db.execute(
                    "INSERT INTO purchases (user_id, symbol, shares, price, time) VALUES (?, ? , ?, ?, ?);",
                    current_user,
                    symbol,
                    -abs(shares),
                    price,
                    date,
                )
                # Delete input from porfolios if remaining number of shares is 0
                if portfolio_shares == shares:
                    db.execute(
                        "DELETE FROM portfolios WHERE user_id=? AND symbol=?;",
                        current_user,
                        symbol,
                    )

                return redirect("/")
            else:
                return apology("Not enough shares")


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Add funds"""
    if request.method == "GET":
        return render_template("add_funds.html")

    else:
        funds = request.form.get("funds")
        # Allow user to add up to $10,000 at the time to his account
        if funds.isnumeric() and float(funds) <= 10000 and float(funds) > 0:
            cash = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])[
                0
            ].get("cash")
            db.execute(
                "UPDATE users SET cash=? WHERE id=?",
                cash + float(funds),
                session["user_id"],
            )
            return redirect("/")
        else:
            return apology("Input a valid number")


@app.route("/reset", methods=["GET", "POST"])
@login_required
def reset():
    """Reset password"""
    if request.method == "GET":
        return render_template("pw_reset.html")

    else:
        current_user = session["user_id"]
        # Ask user for old password
        if not check_password_hash(
            db.execute("SELECT hash FROM users WHERE id=?", current_user)[0].get(
                "hash"
            ),
            request.form.get("password"),
        ):
            return apology("Incorrect Old Password")
        # Requestion new password to be repeated two times
        elif not request.form.get("new_password"):
            return apology("Enter New Password")
        elif request.form.get("new_password") != request.form.get("confirmation"):
            return apology("New passwords must match")
        else:
            # Updates users password
            db.execute(
                "UPDATE users SET hash=? WHERE id=?",
                generate_password_hash(request.form.get("new_password")),
                current_user,
            )
            return logout()


@app.route("/delete", methods=["GET", "POST"])
@login_required
def delete():
    """Delete warning"""
    if request.method == "GET":
        return render_template("delete.html")
    else:
        return render_template("form.html")


@app.route("/form", methods=["GET", "POST"])
@login_required
def form():
    """Delete form"""
    if request.method == "POST":
        current_user = session["user_id"]
        # Asking for old password and remove user from database
        if not check_password_hash(
            db.execute("SELECT hash FROM users WHERE id=?;", current_user)[0].get(
                "hash"
            ),
            request.form.get("password"),
        ):
            return apology("Incorrect password")
        else:
            db.execute("DELETE FROM portfolios WHERE user_id=?;", current_user)
            db.execute("DELETE FROM purchases WHERE user_id=?;", current_user)
            db.execute("DELETE FROM users WHERE id=?;", current_user)
            return logout()
