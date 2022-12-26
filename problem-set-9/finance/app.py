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
    user_id = session.get("user_id")
    transactions = db.execute("SELECT * FROM transactions WHERE user_id=?", user_id)
    cash = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]['cash'] 
    total = cash
    for transaction in transactions:
        total += transaction['total']
    return render_template("index.html", transactions=transactions, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        user_id = session.get("user_id")
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        result = lookup(symbol)

        if not symbol or not result:
            return apology("The stock is not found")

        
        if not shares or not shares.isdigit or int(shares) <= 0:
            return apology("Shares should be positive integer")

        balance = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]
        shares = int(shares)
        total_price = result['price'] * shares

        if total_price > balance['cash']:
            return apology("Insufficient funds")

        already_bougth = set([ x['symbol'] for x in db.execute("SELECT symbol FROM transactions WHERE user_id=?", user_id)])
        if symbol.upper() in already_bougth:
            amount_and_price = db.execute('SELECT amount, total FROM transactions WHERE symbol=?', symbol.upper())[0]
            db.execute("UPDATE transactions SET amount=?, total=? WHERE symbol=?", amount_and_price['amount'] + shares, amount_and_price['total'] + total_price, symbol.upper())
        else:
            db.execute("INSERT INTO transactions (user_id, amount, price, total, symbol, company_name, transaction_type) VALUES (?, ?, ?, ?, ?, ?, ?)", 
                                                user_id, shares, result["price"], total_price, result['symbol'], result['name'], "Purchase")
        db.execute('UPDATE users SET "cash"=? WHERE id=?', balance['cash']-total_price, user_id)
        db.execute("INSERT INTO transactions_history (user_id, amount, price, symbol, transaction_type) VALUES (?, ?, ?, ?, ?)", 
                                                user_id, shares, result["price"], result['symbol'], "Purchase")
        return redirect("/")
    else: 
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session.get("user_id")
    history = db.execute("SELECT * FROM transactions_history WHERE user_id=?", user_id)
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
    if request.method == "POST":

        symbol = request.form.get("symbol")
        result = lookup(symbol)
        if not symbol or not result: 
            return apology("Not found")
        return render_template("quoted.html", result=result, price=result['price'])
    else: 
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        
        usernames = db.execute("SELECT * FROM users WHERE username=?", username)
        
        if not username or len(usernames) > 0:
            return apology("Invalid username")
        
        elif not password or password != confirmation:
            return apology("Invalid password or confirmation")

        db.execute('INSERT INTO users (username, hash) VALUES(?, ?)', username, generate_password_hash(password))
        return redirect("/")
    else: 
        return render_template('register.html')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    
    user_id = session.get("user_id")
    user_symbols = set([x['symbol'] for x in db.execute("SELECT symbol FROM transactions WHERE user_id=?", user_id)])

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        result = lookup(symbol)
        
        if not symbol or symbol.upper() not in user_symbols:
            return apology("Symbols are incorrect")

        if not shares or not shares.isdigit or int(shares) <= 0:
            return apology("Shares are incorrect")

        shares = int(shares) 
        amount_and_price = db.execute("SELECT amount, total FROM transactions WHERE user_id=? AND symbol=?", user_id, symbol.upper())[0]
        if amount_and_price['amount'] >= shares:
            total_price = result['price'] * shares
            balance = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]
            db.execute("UPDATE transactions SET amount=?, total=? WHERE symbol=?", amount_and_price['amount'] - shares, amount_and_price['total'] - total_price, symbol.upper())
            db.execute('UPDATE users SET cash=? WHERE id=?', balance['cash']+total_price, user_id)
            
            db.execute("INSERT INTO transactions_history (user_id, amount, price, symbol, transaction_type) VALUES (?, ?, ?, ?, ?)", 
                                                user_id, shares, result["price"], result['symbol'], "Sale")
            
            amount_after_sale = db.execute("SELECT amount FROM transactions WHERE user_id=? AND symbol=?", user_id, symbol.upper())[0]
            if amount_after_sale['amount'] == 0:
                db.execute("DELETE FROM transactions WHERE user_id=? AND symbol=?", user_id, symbol.upper())
            return redirect('/')
        else:
            return apology("You don't have this amount of shares")
    else:
        return render_template("sell.html", symbols=user_symbols)


@app.route("/addCash", methods=["GET", "POST"])
@login_required
def add_cash():
    if request.method == 'POST':
        user_id = session.get("user_id")        
        amount = request.form.get("amount")        

        if not amount or not amount.isdigit or int(amount) <= 0:
            return apology("Amount should be positive")
        
        balance = db.execute("SELECT cash FROM users WHERE id=?", user_id)[0]
        db.execute('UPDATE users SET cash=? WHERE id=?', balance['cash']+int(amount), user_id)

        return redirect("/")
    else:
        return render_template("addCash.html")