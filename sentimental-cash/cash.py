# Use a greedy algorithm to calculate change owed.

# Function to check if user input is float.
def is_float(c):
    try:
        float(c)
        return True
    except ValueError:
        return False


# Prompt user at least once.
# Re-prompt if input is negative or string.
while True:
    c = input("Change owed: ")
    if is_float(c) == False:
        continue
    cents = float(c)
    if cents < 0:
        continue
    break

# Each coin equation takes a bite out of the problem.
# Update coins after every bite taken.
# Round function used for floating point imprecision.
Quarters = 0
while cents >= 0.25:
    cents = round(cents - 0.25, 2)
    Quarters += 1
Dimes = 0
while cents >= 0.10:
    cents = round(cents - 0.10, 2)
    Dimes += 1
Nickels = 0
while cents >= 0.05:
    cents = round(cents - 0.05, 2)
    Nickels += 1
Pennies = 0
while cents >= 0.01:
    cents = round(cents - 0.01, 2)
    Pennies += 1

# Add all coins to find change owed then print
coins = Quarters + Dimes + Nickels + Pennies
print(coins)
