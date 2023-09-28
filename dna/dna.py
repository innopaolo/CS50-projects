import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python STR_DATABSE DNA_SEQUENCE")

    # Read database file into a variable
    STR = []
    with open(sys.argv[1]) as file:
        reader = csv.reader(file)
        STR = list(reader)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        DNA = file.read().rstrip()

    # Create list of STRs from csv header but start at index 1 to ignore "name"
    str_list = STR[0][1:]

    # Find longest match of each STR in DNA then store in new list
    new_str_list = []
    for i in str_list:
        x = longest_match(DNA, i)
        new_str_list.append(x)

    # Check database for matching profiles
    for row in STR:

        # Skip the STR header
        if row[0] == "name":
            continue

        # First element per row is the person to be printed
        name = row[0]

        # From index 1 each row, change all values to int
        str_counts = [int(x) for x in row[1:]]
        if str_counts == new_str_list:
            quitcode(name)

    # If database check ends with no no match
    print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
