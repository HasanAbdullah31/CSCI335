i. Parts of assignment that were completed: all parts were completed.

ii. Any bugs that were encountered: Since the dictionary wordsEn.txt is limited,
    some words in document1.txt are considered misspelled (e.g. "U.S", "online",
    "they're", "doesn't", people's names, ...).

iii. To run this program, do the following on a terminal:
     -To delete executables and object files, type:
        make clean
     -To compile everything, type:
        make all
     -To run the executables, type:
        ./CreateAndTestHash <words file name> <query words file name> <flag>
           where <flag> should be "quadratic" for quadratic probing, "linear"
           for linear probing, and "double" for double hashing. e.g.:
           ./CreateAndTestHash words.txt query_words.txt quadratic

        ./SpellCheck <document file> <dictionary file>
           e.g.: ./SpellCheck document1.txt wordsEn.txt

        ***All files are assumed to be of the correct formats.***
        ***The second hash function for double hashing is 509-(x mod 509)***

iv. Input files: words.txt
                 query_words.txt
                 wordsEn.txt
                 document1.txt
                 document1_short.txt
    Output files: None
