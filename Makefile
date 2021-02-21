CCC = g++
CFLAGS = -std=c++17 -g -Wall -Wextra -pedantic 
#If using windows, Mingw-w64 and compiling the catch.hpp (test option), 
#you might need to use the flag for big objects: -Wa,-mbig-obj

main: MyCalc.o Calculator.o Operation.o Register.o
	$(CCC) $(CFLAGS) MyCalc.o Calculator.o Operation.o Register.o -o Calculator

valgrind: MyCalc.o Calculator.o Operation.o Register.o
	$(CCC) $(CFLAGS)  MyCalc.o Calculator.o Operation.o Register.o
	valgrind --tool=memcheck --leak-check=yes ./Calculator

test: test.o Operation.o Register.o
	$(CCC) $(CFLAGS) test.o Operation.o Register.o -o CalculatorTest

MyCalc.o: MyCalc.cc
	$(CCC) $(CFLAGS) -c MyCalc.cc

test.o: test.cc
	$(CCC) $(CFLAGS) -c test.cc

Calculator.o: Calculator.cc
	$(CCC) $(CFLAGS) -c Calculator.cc

Register.o: Register.cc
	$(CCC) $(CFLAGS) -c Register.cc

Operation.o: Operation.cc
	$(CCC) $(CFLAGS) -c Operation.cc

cleanL:
	rm -f *.o && rm -f Calculator && rm -f CalculatorTest

cleanW:
	del *.o Calculator.exe CalculatorTest.exe

