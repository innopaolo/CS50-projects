# Print height number of blocks to create a pyramid

# Ensure only values 1 - 8 are accepted
# User is prompted again if input is wrong value
while True:
    h = input("Height: ")
    if h.isnumeric() == False:
        continue
    height = int(h)
    if height < 100 and height > 0:
        break

for row in range(1, height + 1):
    empty = height - row
    for i in range(empty):
        print(" ", end="")
    blocks = height - empty
    for j in range(blocks):
        print("#", end="")
    print("  ", end="")
    for k in range(blocks):
        print("#", end="")
    print("")
