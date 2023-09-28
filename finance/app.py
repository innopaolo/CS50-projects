import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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
    """Show portfolio of stocks"""

    # Get the user id for current session
    user_id = session["user_id"]

    # Get user's info from database
    portfolio = db.execute("SELECT symbol, name, shares, price FROM transactions WHERE user_id = ? ORDER BY symbol", user_id)
    remaining_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    # Iteratively convert numbers in portfolio to float and pass in lookup function to price
    for stock in portfolio:
        float(stock["shares"])
        float(stock["price"])
        stock["price"] = lookup(stock["symbol"])["price"]

    # Get grand total by adding each stock's total value to the remaining_cash
    total = remaining_cash
    for stock in portfolio:
        total += stock["price"] * stock["shares"]
        print(total)

    return render_template("index.html", pf=portfolio, rc=remaining_cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        # Get user input and determine if es no valido, hombre
        symbol = request.form.get("symbol")
        stock = lookup(symbol)

        # If input field left blank
        if not symbol:
            return apology("missing symbol", 400)

        # No es valido
        if stock == None:
            return apology("ayy symbol no es valido, tonto!", 400)

        # Missing shares input (done before creating the shares variable to not trigger an invalid string literal error)
        if not request.form.get("shares"):
            return apology("missing shares", 400)

        shares = request.form.get("shares")

        # Missing shares
        if not shares:
            return apology("missing shares", 400)

        # Render an apology if user inputs integer less than 1
        if shares.isdigit() == False or int(shares) < 1:
            return apology("shares gotta be a positive integer, dumbo!", 400)

        # Get amount of stock bought by the user
        amount = float(stock["price"]) * float(shares)

        # Find out user's remaining cash money
        user_id = session["user_id"]
        total_bread = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

        if total_bread < amount:
            return apology("sir you cannot afford it", 400)
        else:
            # Update user's remaining cash in the SQL table
            db.execute("UPDATE users SET cash = ? WHERE id = ?", total_bread - amount, user_id)

            # If bought stock aready exists in table, only add to its shares, otherwise, insert a new row
            exists = db.execute("SELECT symbol FROM transactions WHERE symbol = ?", symbol)

            if len(exists) > 0:
                previous_shares = float(db.execute("SELECT shares FROM transactions WHERE symbol = ?", symbol)[0]["shares"])
                db.execute("UPDATE transactions SET shares = ? WHERE symbol = ?", previous_shares + int(shares), symbol)
            else:
                db.execute("INSERT INTO transactions (user_id, name, shares, symbol, price) VALUES (?, ?, ?, ?, ?)",
                           user_id, stock["name"], shares, symbol, stock["price"])

        # Record every sale in the history table
        db.execute("INSERT INTO history (user_id, shares, symbol, trade, price) VALUES (?, ?, ?, ?, ?)",
                   user_id, shares, symbol, "Buy", stock["price"])

        # Flash confirmation to user on redirect
        flash("Bought!")
        return redirect("/")

    # User reaches route via GET
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Query user info for history
    portfolio = db.execute("SELECT symbol, trade, shares, price, date FROM history ORDER BY date DESC")
    return render_template("history.html", pf=portfolio)


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

    if request.method == "POST":

        symbol = request.form.get("symbol")

        # No input gets an "apology"
        if not symbol:
            return apology("put a quote ya flaming stoat!", 400)

        # Find symbol through API and show stock price
        stock = lookup(symbol)

        # Non-existent symbol summons her
        if stock == None:
            return apology("invalid symbol", 400)

        return render_template("quoted.html", stock=stock)

    # User acces via GET
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":

        registrant = request.form.get("username")

        # Blank username gets an "apology"
        if not registrant:
            return apology("freakin give me a username man", 400)

        # Unavailable username gets an "apology"
        row = db.execute("SELECT * FROM users WHERE username = ?", registrant)
        if len(row) != 0:
            return apology("some goat-spawned toad already got that alias", 400)

        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Require a password
        if not password or not confirmation:
            return apology("go back and fill in the password ya woolhead", 400)

        # Passwords should match
        if password != confirmation:
            return apology("passy no matchy!", 400)

        # Run the password through the scrambulator
        hash = generate_password_hash(password)

        # Insert the new finance bro into the database
        bro = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", registrant, hash)

        # Remember user as logged in
        session["user_id"] = bro

        # Alert user on redirect
        flash("Registered!")
        return redirect("/")

    # If user sends by GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":

        symbol = request.form.get("symbol")

        # Ensure user fills in all information
        if not symbol:
            return apology("missing symbol", 400)

        inputted_shares = int(request.form.get("shares"))
        if not inputted_shares or inputted_shares < 1:
            return apology("missing shares", 400)

        lookup_sym = lookup(symbol)
        if lookup_sym == None:
            return apology("invalid symbol", 400)

        # Ensure shares sold are less than or equal to available shares
        user_id = session["user_id"]
        holdings = db.execute("SELECT shares FROM transactions WHERE user_id = ? AND symbol = ?", user_id, symbol)[0]["shares"]

        if inputted_shares > holdings:
            return apology("too many shares", 400)
        else:

            # Update database with new share amount and user cash
            new_shares = int(holdings) - inputted_shares
            total_bread = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
            amount = float(lookup_sym["price"]) * inputted_shares

            db.execute("UPDATE transactions SET shares = ? WHERE user_id = ? AND symbol = ?", new_shares, user_id, symbol)
            db.execute("UPDATE users SET cash = ? WHERE id = ?", total_bread + amount, user_id)

            # Delete row if
            if new_shares == 0:
                db.execute("DELETE FROM transactions WHERE shares = ?", new_shares)

        # Record every sale in the history table
        db.execute("INSERT INTO history (user_id, shares, symbol, trade, price) VALUES (?, ?, ?, ?, ?)",
                   user_id, inputted_shares, symbol, "Sell", lookup_sym["price"])

        # Flash confirmation to user on redirect
        flash("Sold!")
        return redirect("/")

    # If user arrives at route with GET
    else:

        # Grab shares info from database and pass into the html page
        user_id = session["user_id"]
        bought = db.execute("SELECT symbol FROM transactions where user_id = ?", user_id)

        return render_template("sell.html", bought=bought)


@app.route("/account", methods=["GET", "POST"])
@login_required
def account():

    if request.method == "POST":

        # Ensure fields are not left blank
        old = request.form.get("old")
        new = request.form.get("new")
        confirm = request.form.get("confirm")

        if not old or not new or not confirm:
            return apology("one or more of your fields are blank", 400)

        # Query database for logged in user
        user_id = session["user_id"]
        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        # Ensure old password is correct
        if not check_password_hash(rows[0]["hash"], old):
            return apology("invalid username and/or password", 403)
        else:

            # Passwords should match
            if new != confirm:
                return apology("passy no matchy!", 400)

            # Run the new password through the scrambulator
            hash = generate_password_hash(new)

            # Update database with new password
            db.execute("UPDATE users SET hash = ? WHERE id = ?", hash, user_id)

        flash("Password changed!")
        return redirect("/")

    # User access via GET
    else:
        return render_template("account.html")


@app.route("/delete", methods=["POST"])
@login_required
def delete():

    if request.method == "POST":

        # Ensure fields are not left blank
        username = request.form.get("username")
        password = request.form.get("password")

        if not username or not password:
            return apology("one or more of your fields are blank", 400)

        # Query database for logged in user
        user_id = session["user_id"]
        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        # Ensure username and password is correct
        if rows[0]["username"] != username:
            return apology("invalid username", 403)

        if not check_password_hash(rows[0]["hash"], password):
            return apology("invalid password", 403)

        # Delete user from database if all conditions are met
        db.execute("DELETE FROM history WHERE id = ?", user_id)
        db.execute("DELETE FROM transactions WHERE id = ?", user_id)
        db.execute("DELETE FROM users WHERE username = ?", username)

        return redirect("/logout")

    else:
        return redirect("/account")

