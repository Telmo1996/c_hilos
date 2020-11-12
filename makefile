c_hilos: main.o
	gcc -o c_hilos main.o

c_hilos.o: main.c
	gcc -c main.c

clean:
	rm -f *.o c_hilos
