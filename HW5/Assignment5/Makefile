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
ALL_OBJ_0=optimal_multiplications.o
PROGRAM_0=optimal_multiplications
$(PROGRAM_0): $(ALL_OBJ_0)
	g++ $(C++FLAG) -o $(EXEC_DIR)/$@ $(ALL_OBJ_0) $(INCLUDES) $(LIBS_ALL)

#Compiling all
all:
	make $(PROGRAM_0)

#Clean obj files
clean:
	rm -f *.o
	rm -f $(PROGRAM_0)

(:
