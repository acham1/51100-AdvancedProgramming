all: p1 p2 p3 p4 p5 p6

p1: p1/p1
p1/p1: p1/p1.o p1/graph.o p1/heap.o p1/linkedlist.o p1/dijkstra.o
	gcc -std=c99 -pedantic -Wall p1/p1.o p1/graph.o p1/heap.o p1/linkedlist.o p1/dijkstra.o -o p1/p1
	rm p1/*.o
p1/p1.o: p1/p1.c p1/graph.h p1/heap.h p1/linkedlist.h p1/dijkstra.h
	gcc -std=c99 -pedantic -Wall -c p1/p1.c -o p1/p1.o
p1/dijkstra.o: p1/dijkstra.c p1/dijkstra.h p1/graph.h p1/heap.h p1/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p1/dijkstra.c -o p1/dijkstra.o
p1/graph.o: p1/graph.c p1/graph.h p1/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p1/graph.c -o p1/graph.o
p1/linkedlist.o: p1/linkedlist.c p1/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p1/linkedlist.c -o p1/linkedlist.o
p1/heap.o: p1/heap.c p1/heap.h
	gcc -std=c99 -pedantic -Wall -c p1/heap.c -o p1/heap.o

p2: p2/p2
p2/p2: p2/p2.o

p3: p3/p3
p3/p3: p3/p3.o

p4: p4/p4
p4/p4: p4/p4.o

p5: p5/p5
p5/p5: p5/p5.o

p6: p6/p6
p6/p6: p6/p6.o

clean:
	rm p1/*.o p2/*.o p3/*.o p4/*.o p5/*.o p6/*.o p1/p1 p2/p2/ p3/p3 p4/p4 p5/p5 p6/p6