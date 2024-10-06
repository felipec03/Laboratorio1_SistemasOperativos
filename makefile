FLAGS = -g
#FLAGS = -O2
all: archivos.c archivos.h

archivos: archivos.c archivos.h
	gcc $(FLAGS) archivos.c -o archivos

testQueue: State.o Queue.o testQueue.cpp
	g++ $(FLAGS) State.o Queue.o testQueue.cpp -o testQueue

test_State: State.o testQueue.cpp
	g++ $(FLAGS) State.o test_State.cpp -o test_State

testJug: State.o testJug.cpp
	g++ $(FLAGS) State.o testJug.cpp -o testJug

State.o: State.h State.cpp
	g++ $(FLAGS) -c State.cpp

Queue.o: Queue.h Queue.cpp
	g++ $(FLAGS) -c Queue.cpp

Jug.o: Jug.h Jug.cpp
	g++ $(FLAGS) -c Jug.cpp

clean:
	rm $(FLAGS) -f *.o testQueue test_State
