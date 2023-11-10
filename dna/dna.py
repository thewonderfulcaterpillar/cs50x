import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py FILENAME SEQUENCENAME")
    # TODO: Read database file into a variable
    database={}
    subsequenceList=[]
    with open(sys.argv[1]) as databaseFile:
        databaseReader=csv.DictReader(databaseFile)
        for row in databaseReader:
            list=[]
            for k,v in row.items():
                if k!="name":
                    if len(subsequenceList)!=len(row.keys())-1:
                        subsequenceList.append(k)
                    list.append(int(v))
            database[row["name"]]=list
    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as sequenceFile:
        sequence = sequenceFile.read()
    # TODO: Find longest match of each STR in DNA sequence
    subsequenceFreq=[]
    for subsequence in subsequenceList:
        subsequenceFreq.append(longest_match(sequence,subsequence))
    found=False

    # TODO: Check database for matching profiles
    for key,value in database.items():
        if value==subsequenceFreq:
            print(key)
            found=True
    if not found: print("No match")

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
