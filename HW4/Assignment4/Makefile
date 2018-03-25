################################
##                            ##
##          Makefile          ##
##      LINUX compilation     ##
##                            ##
##   Author: Hasan Abdullah   ##
##                            ##
################################

#FLAGS
C++FLAG=-g -std=c++11 -Wall

#Math Library
MATH_LIBS=-lm
EXEC_DIR=.

#Rule for .cpp files
# .SUFFIXES : .cpp.o

.cpp.o:
	g++ $(C++FLAG) $(INCLUDES) -c $< -o $@

#Including
INCLUDES=-I.
LIBS_ALL=-L/usr/lib -L/usr/local/lib $(MATH_LIBS)

#ZEROTH PROGRAM
ALL_OBJ_0=CreateGraphAndTest.o
PROGRAM_0=CreateGraphAndTest
$(PROGRAM_0): $(ALL_OBJ_0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ_0) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ_1=FindPaths.o
PROGRAM_1=FindPaths
$(PROGRAM_1): $(ALL_OBJ_1)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ_1) $(INCLUDES) $(LIBS_ALL)

ALL_OBJ_2=DisjSets.o TestRandomGraph.o
PROGRAM_2=TestRandomGraph
$(PROGRAM_2): $(ALL_OBJ_2)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ_2) $(INCLUDES) $(LIBS_ALL)

#Compiling all
all:
	make $(PROGRAM_0)
	make $(PROGRAM_1)
	make $(PROGRAM_2)

#Clean obj files
clean:
	rm -f *.o
	rm -f $(PROGRAM_0)
	rm -f $(PROGRAM_1)
	rm -f $(PROGRAM_2)

(:
