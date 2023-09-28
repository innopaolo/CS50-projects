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

        # Grab info from user input
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Add user's entry into the database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
        return redirect("/")

    else:

        # Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", birthdays=birthdays)

# Delete entry from the database
@app.route("/delete", methods=["POST"])
def delete():
    id = request.form.get("id")
    if id:

        # Pass in id from html into database
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")

@app.route("/update", methods=["POST"])
def update():

    # TODO: Update database by sending new HTML data to SQL
    return redirect("/")

