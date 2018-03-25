i. Parts of assignment that were completed: all parts were completed.

ii. Any bugs that were encountered: no bugs were encountered.

iii. To run this program, do the following on a terminal:
     -To delete executables and object files, type:
        make clean
     -To compile everything, type:
        make all
     -To compile a program individually, type:
        make query_tree
	    -or-
	make test_tree
     -To run the executable normally, type:
        ./query_tree <databasefilename> <tree-type>
	    -or-
	./test_tree <databasefilename> <queryfilename> <tree-type>
	    where databasefilename can be rebase210.txt, queryfilename can be
	    sequences.txt, and tree-type is either AVL or BST. Both files are
	    assumed to be of the correct format.
     ***There are 3 instances where the program query_tree requires user input;
        the inputs are meant to be recognition sequence strings***
     -The query_tree executable can be run with a valid input file; e.g.:
        ./query_tree < input_part2a.txt

iv. Input files: input_part2a.txt
                 rebase210.txt
		 sequences.txt
    Output files: None
