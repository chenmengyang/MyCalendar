CC=tutg++

all:	Assignment3.o Mydate.o
	$(CC) Assignment3.o Mydate.o -o Assignment3

Assignment3.o:	Assignment3.cpp
	$(CC) -c Assignment3.cpp

Mydate.o:	Mydate.cc Mydate.hh
	$(CC) -c Mydate.cc

clean:
	rm -rf *.o
