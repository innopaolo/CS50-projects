# Print a half-pyramid with a user-generated height

# Prompt user at least once
# Ensure only 1 - 8 is accepted
while True:
    h = input("Height: ")
    if h.isnumeric() == False:
        continue
    height = int(h)
    if height < 9 and height > 0:
        break

for row in range(1, height + 1):
    empty = height - row
    for i in range(empty):
        print(" ", end="")
    blocks = height - empty
    for j in range(blocks):
        print("#", end="")
    print("")

