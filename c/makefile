c_hilos: main.o funciones.o
	gcc -o c_hilos main.o funciones.o -ljson-c -lm

c_hilos.o: main.c
	gcc -c main.c

funciones.o: funciones.c
	gcc -c funciones.c

clean:
	rm -f *.o c_hilos
