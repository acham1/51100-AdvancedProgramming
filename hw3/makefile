all: p1 p2 p3

CFLAGS = -std=c99 -pedantic -Wall
LFLAGS =

p1: p1/p1
p1/p1: p1/linkedlist.o p1/hashmap.o p1/p1.o
	gcc $(CFLAGS) p1/linkedlist.o p1/hashmap.o p1/p1.o -o p1/p1
	rm p1/*.o
p1/linkedlist.o: p1/linkedlist.c p1/linkedlist.h
	gcc $(CFLAGS) -c p1/linkedlist.c -o p1/linkedlist.o
p1/hashmap.o: p1/hashmap.c p1/hashmap.h p1/linkedlist.h
	gcc $(CFLAGS) -c p1/hashmap.c -o p1/hashmap.o
p1/p1.o: p1/p1.c p1/hashmap.h p1/linkedlist.h
	gcc $(CFLAGS) -c p1/p1.c -o p1/p1.o

p2: p2/p2
p2/p2: p2/linkedlist.o p2/hashmap.o p2/unique.o p2/p2.o
	gcc $(CFLAGS) p2/linkedlist.o p2/hashmap.o p2/unique.o p2/p2.o -o p2/p2
	rm p2/*.o
p2/linkedlist.o: p2/linkedlist.c p2/linkedlist.h
	gcc $(CFLAGS) -c p2/linkedlist.c -o p2/linkedlist.o
p2/hashmap.o: p2/hashmap.c p2/hashmap.h p2/linkedlist.h
	gcc $(CFLAGS) -c p2/hashmap.c -o p2/hashmap.o
p2/unique.o: p2/unique.c p2/unique.h p2/hashmap.h p2/linkedlist.h
	gcc $(CFLAGS) -c p2/unique.c -o p2/unique.o
p2/p2.o: p2/p2.c p2/hashmap.h p2/linkedlist.h p2/unique.h
	gcc $(CFLAGS) -c p2/p2.c -o p2/p2.o

p3: p3/p3
p3/p3: p3/p3.o
	gcc $(CFLAGS) p3/p3.o -o p3/p3
	rm p3/*.o
p3/p3.o: p3/p3.c
	gcc $(CFLAGS) -c p3/p3.c -o p3/p3.o

clean:
	rm p1/p1 p2/p2 p3/p3
