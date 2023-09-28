# Determine grade level of text input

from cs50 import get_string
import re


def main():
    # Determine values for letters, words, and sentences
    text = get_string("Text: ")
    lcount = count_letters(text)
    wcount = count_words(text)
    scount = count_sentences(text)

    # Calculate Coleman-Liau index
    words = wcount / 1.0
    L = lcount / words * 100.0
    S = scount / words * 100.0
    CLindex = round(0.0588 * L - 0.296 * S - 15.8)

    # Printing conditions
    if CLindex >= 16:
        print("Grade 16+")
    elif CLindex < 1:
        print("Before Grade 1")
    else:
        print("Grade", CLindex)


def count_letters(text):
    """Identify letters using regex"""

    count = 0
    for char in text:
        if re.search("[a-zA-Z]", char):
            count += 1
    return count


def count_words(text):
    """Identify words by using regex to search for whitespace"""

    # Count starts at 1 to account for last word of text(no space after)
    count = 1
    for char in text:
        if re.search("\s", char):
            count += 1
    return count


def count_sentences(text):
    """Identify sentences with "?!." using regex"""

    count = 0
    for char in text:
        if re.search("[?!.]", char):
            count += 1
    return count


if __name__ == "__main__":
    main()