CFLAGS=-c -std=c++0x -O2 -p -pg

all: arj

arj: main.o huffmancoder.o streamreader.o streamwriter.o tree.o bufwriter.o treewalker.o huffmandecoder.o
	g++ main.o huffmancoder.o streamreader.o streamwriter.o tree.o bufwriter.o treewalker.o huffmandecoder.o -p -pg -o arj

main.o: main.cpp
	g++ $(CFLAGS)  main.cpp

huffmancoder.o: huffmancoder.cpp
	g++ $(CFLAGS) huffmancoder.cpp

streamreader.o: streamreader.cpp
	g++ $(CFLAGS) streamreader.cpp

streamwriter.o: streamwriter.cpp
	g++ $(CFLAGS) streamwriter.cpp

tree.o: tree.cpp
	g++ $(CFLAGS) tree.cpp

bufwriter.o: bufwriter.cpp
	g++ $(CFLAGS) bufwriter.cpp

treewalker.o: treewalker.cpp
	g++ $(CFLAGS) treewalker.cpp

huffmandecoder.o: huffmandecoder.cpp
	g++ $(CFLAGS) huffmandecoder.cpp
clean:
	rm -rf *.o arj


