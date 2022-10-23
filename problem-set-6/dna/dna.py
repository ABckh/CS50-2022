import csv
import sys


def main():
    if len(sys.argv) < 3:
        print("Program usage: dna.py file.csv file.txt")
        sys.exit(1)

    database = {}

    try:
        with open(sys.argv[1], 'r') as csv_file:
            csvreader = csv.reader(csv_file)
            for row in csvreader:
                name = row[0]
                database[name] = row[1:]
    except FileNotFoundError:
        print("CSV file was not found")
        sys.exit(1)

    try:
        with open(sys.argv[2], 'r') as txt_file:
            dna = txt_file.readline()
    except FileNotFoundError:
        print("TXT file was not found")
        sys.exit(1)
    
    values = [str(longest_match(dna, subseq)) for subseq in database["name"]]
    
    for key in database.keys():
        if database[key] == values:
            print(key)
            sys.exit(0)
    print("No match")

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
        # qIf a match, move substring to next potential match in sequence
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
