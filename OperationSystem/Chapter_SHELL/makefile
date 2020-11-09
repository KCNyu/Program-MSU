shell: main.o shell.o
	gcc -o shell main.o shell.o
main.o: main.c shell.h
	gcc -c main.c
shell.o: shell.c shell.h
	gcc -c shell.c
clean:
	rm *.o shell

