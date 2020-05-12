pex1: main.o task.o
	g++ main.o task.o -o pex1

main.o: main.cpp task.h queue.h
	g++ -c main.cpp

task.o: task.cpp task.h
	g++ -c task.cpp

clean:
	rm *.o pex1

