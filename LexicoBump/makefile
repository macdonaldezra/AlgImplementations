all: reduce extension

reduce:	reduce.o poset.o
	g++ -o reduce reduce.o poset.o

extension: main.o bump.o
	g++ -o extension main.o bump.o

bump.o: bump.h bump.cpp
	g++ -c -g -Wall bump.cpp

main.o: bump.h main.cpp
	g++ -c main.cpp

testapp.o:	poset.h testapp.cpp
	g++ -c testapp.cpp

reduce.o:	poset.h reduce.cpp
	g++ -c reduce.cpp

poset.o:	poset.h poset.cpp
	g++ -c poset.cpp

clean:
	rm -f *.o reduce extension