Author: Hasan Abdullah
Purpose: CSCI 335 Project 4

i. Parts of assignment that were completed: all parts were completed.

ii. Any bugs that were encountered: no bugs were encountered.

iii. To run this program, do the following on a terminal:
     -To delete executables and object files, type:
        make clean
     -To compile everything, type:
        make all
     -To compile a program separately, type:
        make <program name>
        <program name> can be CreateGraphAndTest, FindPaths, or TestRandomGraph
     -To run the executables, type:
        ./CreateGraphAndTest <graph file> <query vertices file>
           e.g.: ./CreateGraphAndTest Graph1.txt AdjacencyQueries1.txt

        ./FindPaths <graph file> <start vertex>
           e.g.: ./FindPaths Graph2.txt 1

        ./TestRandomGraph <maximum number of nodes>
           e.g.: ./TestRandomGraph 100

        ***All files are assumed to be of the correct formats.***

iv. Input files: Graph1.txt
                 Graph2.txt
                 Graph3.txt
                 AdjacencyQueries1.txt
                 AdjacencyQueries2.txt
    Output files: None
