Shape: main.o Shape.o
	g++ -o Shape main.o Shape.o
main.o: main.cpp Shape.h
	g++ -c main.cpp
Shape.o: Shape.cpp Shape.h
	g++ -c Shape.cpp
clean:
	rm *.o Shape
