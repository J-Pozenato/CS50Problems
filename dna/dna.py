import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # TODO: Read database file into a variable
    csvFile = sys.argv[1]
    txtFile = sys.argv[2]

    database = []

    # TODO: Read DNA sequence file into a variable
    with open(csvFile) as csvf:
        reader = csv.DictReader(csvf)

        for person in reader:
            database.append(person)

    # creates a list called repeats where all STR are stored
    repeats = []
    repeats = list(database[1].keys())
    repeats.remove("name")
    # print(repeats)

    # TODO: Find longest match of each STR in DNA sequence
    with open(txtFile) as txtf:
        text = txtf.read()
    # print(text)

    # creates a list called longest where it is stored the longest repetition of STR in the txt file
    longest = []
    for i in repeats:
        longest.append(longest_match(text, i))
    # print(longest)

    # TODO: Check database for matching profiles
    # loop to all the names in the database and check if STR values  a equal to those in the longest list
    for ind in database:
        ite = 0
        for i in repeats:
            if not int(ind[i]) == longest[ite]:
                break
            ite += 1
            if ite == len(repeats):
                print(ind['name'])
                return

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
