import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import requests
from helpers import apology, login_required, lookup, usd
import datetime

#API key pk_d97138b37517413fa8ac18df9b621c93
# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


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

    # Get list of stocks
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    orders = db.execute(
        "SELECT symbol, sum(shares) as sumshares, price FROM transactions WHERE user_id = ? GROUP BY symbol",
        session["user_id"],
    )
    account = cash[0]["cash"]
    for order in orders:
        total = order["sumshares"] * order["price"]
        order["total"] = total
        order["price"] = order["price"]
        account += total
    return render_template(
        "index.html", orders=orders, cash=cash[0]["cash"], account=account
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    else:

        symbol = request.form.get("symbol")
        symbol.upper
        if not symbol:
            return apology("symbol not found")

        quote = lookup(symbol)
        if not quote:
            return apology("Invalid Symbol")

        shares = float(request.form.get("shares"))
        if not shares or not float.is_integer(shares) or shares <= 0:
            return apology("Invalid number")

        user_id = session["user_id"]
        user_portfolio = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"] )
        cash = user_portfolio[0]["cash"]

        buy_price = cash - shares * quote["price"]

        if buy_price < 0:
            return apology("insufficient balance")


        update = cash - buy_price

        db.execute("UPDATE users SET cash = ? WHERE id = ?",buy_price, session["user_id"])
        DT = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id,symbol,shares,price,date) VALUES (?, ?, ?, ?, ?)",session["user_id"], symbol, shares, quote["price"], DT)

        flash ("Transaction Complete!")
        return redirect("/")


@app.route("/history")
@login_required
def history():
    # Retrieve the history of transactions for the current user
    history = db.execute("SELECT symbol, shares, price, date FROM transactions WHERE user_id = ?",
                         session["user_id"])

    if not history:
        return apology("No history", 403)
    else:
        return render_template("history.html", history=history)

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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    if request.method == "GET":
        return render_template("quotes.html")

    else:
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        if not symbol:
            return apology("symbol not found")

        if not quote:
            return apology("invalid symbol")

        return render_template("quoted.html", quote=quote)

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirm =  request.form.get("confirmation")


        if not username or not password or not confirm:
            return apology("please provide username and password!")

        if password != confirm:
            return apology("password and confirm don't match")


        hash = generate_password_hash(password)

        try:
            user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except:
            return apology("account already exists")

        session["user_id"] = user

        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    """Sell shares of stock"""
    if request.method == "GET":
        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol",session["user_id"],)
        return render_template("sell.html", symbol=symbols)
    else:
        # Get the symbol and shares to sell from the form
        symbol = request.form.get("symbol")

        if not symbol:
            return apology("symbol not found")

        shares = float(request.form.get("shares"))

        if not shares or not float.is_integer(shares) or shares <= 0:
            return apology("Invalid number")

        total = db.execute("SELECT symbol, price, SUM(shares) as sumshares FROM transactions WHERE user_id = ? AND symbol = ?",session["user_id"],symbol,)

        if shares > total[0]["sumshares"]:
            return apology("You don't have shares")

        # Look up the current price of the stock
        quote = lookup(symbol)
        if not quote:
            return apology("Invalid Symbol")



        # Get the current balance of the user's account from the database
        user_portfolio = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = user_portfolio[0]["cash"]



        sell_price = quote["price"] * shares
        new_balance = cash + sell_price

        # Update the balance in the database
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])

        # Insert the transaction into the transactions table
        DT = datetime.datetime.now()
        db.execute("INSERT INTO transactions (user_id, symbol, shares, date) VALUES (?, ?, ?, ?)",session["user_id"],symbol,-shares,DT,)



        cash = db.execute("select cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]




        return redirect("/")

