CFLAGS= -c -std=c++0x -Wall -O2 -p -pg

all: pp

pp: parser.o main.o lexer.o interpreter.o evaluator.o    
	g++  parser.o main.o lexer.o interpreter.o evaluator.o  -p -pg -o pp

parser.o: parser.cpp
	g++ $(CFLAGS) parser.cpp

main.o: main.cpp
	g++ $(CFLAGS)  main.cpp

lexer.o: lexer.cpp
	g++ $(CFLAGS) lexer.cpp

interpreter.o: interpreter.cpp
	g++ $(CFLAGS) interpreter.cpp

evaluator.o: evaluator.cpp
	g++ $(CFLAGS) evaluator.cpp

clean:
	rm -rf *.o pp


