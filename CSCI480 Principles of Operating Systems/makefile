# /********************************************************
#  * CSCI 480 MidOS Project
#  * 
#  * Julia Finegan
#  * Long Huang
#  * Brandon Romito
#  * David Ostman
#  * Gurpreet Girn
# **********************************************************/



CXXFLAGS = -g -ansi -Wall -Werror -Wextra -std=c++14

OS: main.o MMU.o CPU.o PCB.o
	g++ $(CXXFLAGS) -o OS main.o MMU.o CPU.o PCB.o 

main.o: main.cpp
	g++ $(CXXFLAGS) -c -o main.o main.cpp

MMU.o: MMU.cpp
	g++ $(CXXFLAGS) -c -o MMU.o MMU.cpp

CPU.o: CPU.cpp
	g++ $(CXXFLAGS) -c -o CPU.o CPU.cpp

PCB.o: PCB.cpp
	g++ $(CXXFLAGS) -c -o PCB.o PCB.cpp


clean:
	rm -f *.o OS main.o CPU.o MMU.o PCB.o