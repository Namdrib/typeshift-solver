# Makefile for typeshift-solver

CFLAGS = -std=gnu++11 -O2 -Wall

main: main.cpp typeshift_solver.o
	g++ -o main main.cpp typeshift_solver.o $(CFLAGS)

typeshift_solver.o: typeshift_solver.h typeshift_solver.cpp
	g++ -c typeshift_solver.cpp $(CFLAGS)

clean:
	rm -rf *.o *.exe* main
