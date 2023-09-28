# Determine if credit card number is valid

import re

# Prompt user for credit card number
# Ensure only digits are accepted
while True:
    number = input("Number: ")
    if number.isnumeric() == False:
        continue
    else:
        break

# Create a list of ints from user input
ccnumber = [int(i) for i in number]


# Calculate checksum

# Separate digits by their parity position
# Start slice from reverse
odd = ccnumber[-1::-2]
even = ccnumber[-2::-2]

# Luhn's algorithm
index = 0
for i in even:
    even[index] = i * 2
    if len(str(even[index])) > 1:
        even[index] = int(even[index] / 10) + int(even[index] % 10)  # Cast to int so no decimal values
    index += 1
checksum = (sum(odd) + sum(even)) % 10

# Determine credit card brand using regex
if checksum == 0 and len(number) > 12:
    if re.search("3[47]", number) and len(number) == 15:
        print("AMEX")
    elif re.search("^5[1-5]", number) and len(number) == 16:
        print("MASTERCARD")
    elif re.search("^4[0-9]", number) and len(number) == 13 or len(number) == 16:
        print("VISA")
else:
    print("INVALID")
