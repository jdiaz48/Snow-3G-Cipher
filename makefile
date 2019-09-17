all: program1

program1: program1.cpp
	g++ -Wall -g -o program1 program1.cpp

program1.o: program1.cpp
	g++ -c program1.cpp

clean :
	rm -f *.o program1
