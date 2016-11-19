all: p1 p2 p3

p1: p1/linkedlist.o p1/hashmap.o p1/p1.o
	gcc -std=c99 -pedantic -Wall p1/linkedlist.o p1/hashmap.o p1/p1.o -o p1/p1Driver

p1/linkedlist.o: p1/linkedlist.c p1/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p1/linkedlist.c -o p1/linkedlist.o

p1/hashmap.o: p1/hashmap.c p1/hashmap.h p1/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p1/hashmap.c -o p1/hashmap.o

p1/p1.o: p1/p1.c p1/hashmap.h p1/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p1/p1.c -o p1/p1.o

clean:
	rm p1/*.o p1/p1Driver p2/*.o p2/p2Driver p3/*.o p3/p3Driver
