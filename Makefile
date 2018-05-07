
all: list.o
	gcc -shared -o liblist.so list.o

list.o: list.h list.c
	gcc -c -Wall -fpic list.c

clean: 
	rm -f *.o

superClean: clean
	rm -f *.so
