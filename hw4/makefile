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
p2/p2: p2/p2.o p2/graph.o p2/heap.o p2/linkedlist.o p2/dijkstra.o
	gcc -std=c99 -pedantic -Wall -fopenmp p2/p2.o p2/graph.o p2/heap.o p2/linkedlist.o p2/dijkstra.o -o p2/p2
	rm p2/*.o
p2/p2.o: p2/p2.c p2/graph.h p2/heap.h p2/linkedlist.h p2/dijkstra.h
	gcc -std=c99 -pedantic -Wall -c -fopenmp p2/p2.c -o p2/p2.o
p2/dijkstra.o: p2/dijkstra.c p2/dijkstra.h p2/graph.h p2/heap.h p2/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p2/dijkstra.c -o p2/dijkstra.o
p2/graph.o: p2/graph.c p2/graph.h p2/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p2/graph.c -o p2/graph.o
p2/linkedlist.o: p2/linkedlist.c p2/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p2/linkedlist.c -o p2/linkedlist.o
p2/heap.o: p2/heap.c p2/heap.h
	gcc -std=c99 -pedantic -Wall -c p2/heap.c -o p2/heap.o

p3: p3/p3
p3/p3: p3/p3.o p3/graph.o p3/heap.o p3/linkedlist.o p3/dijkstra.o
	gcc -std=c99 -pedantic -Wall -fopenmp p3/p3.o p3/graph.o p3/heap.o p3/linkedlist.o p3/dijkstra.o -o p3/p3
	rm p3/*.o
p3/p3.o: p3/p3.c p3/graph.h p3/heap.h p3/linkedlist.h p3/dijkstra.h
	gcc -std=c99 -pedantic -Wall -c -fopenmp p3/p3.c -o p3/p3.o
p3/dijkstra.o: p3/dijkstra.c p3/dijkstra.h p3/graph.h p3/heap.h p3/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c -fopenmp p3/dijkstra.c -o p3/dijkstra.o
p3/graph.o: p3/graph.c p3/graph.h p3/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p3/graph.c -o p3/graph.o
p3/linkedlist.o: p3/linkedlist.c p3/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p3/linkedlist.c -o p3/linkedlist.o
p3/heap.o: p3/heap.c p3/heap.h
	gcc -std=c99 -pedantic -Wall -c p3/heap.c -o p3/heap.o

p4: p4/p4
p4/p4: p4/p4.o p4/graph.o p4/linkedlist.o p4/bfs.o
	gcc -std=c99 -pedantic -Wall p4/p4.o p4/graph.o p4/linkedlist.o p4/bfs.o -o p4/p4
	rm p4/*.o
p4/p4.o: p4/p4.c p4/graph.h p4/bfs.h p4/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p4/p4.c -o p4/p4.o
p4/graph.o: p4/graph.c p4/graph.h p4/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p4/graph.c -o p4/graph.o
p4/linkedlist.o: p4/linkedlist.c p4/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p4/linkedlist.c -o p4/linkedlist.o
p4/bfs.o: p4/bfs.c p4/bfs.h
	gcc -std=c99 -pedantic -Wall -c p4/bfs.c -o p4/bfs.o

p5: p5/p5
p5/p5: p5/p5.o p5/graph.o p5/linkedlist.o p5/dfs.o p5/scc.o
	gcc -std=c99 -pedantic -Wall p5/p5.o p5/graph.o p5/linkedlist.o p5/dfs.o p5/scc.o -o p5/p5
	rm p5/*.o
p5/p5.o: p5/p5.c p5/graph.h p5/dfs.h p5/linkedlist.h p5/scc.h
	gcc -std=c99 -pedantic -Wall -c p5/p5.c -o p5/p5.o
p5/graph.o: p5/graph.c p5/graph.h p5/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p5/graph.c -o p5/graph.o
p5/linkedlist.o: p5/linkedlist.c p5/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p5/linkedlist.c -o p5/linkedlist.o
p5/scc.o: p5/scc.c p5/scc.h p5/dfs.h p5/graph.h p5/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p5/scc.c -o p5/scc.o
p5/dfs.o: p5/dfs.c p5/dfs.h
	gcc -std=c99 -pedantic -Wall -c p5/dfs.c -o p5/dfs.o

p6: p6/p6
p6/p6: p6/p6.o p6/graph.o p6/linkedlist.o
	gcc -std=c99 -pedantic -Wall p6/p6.o p6/graph.o p6/linkedlist.o -o p6/p6
	rm p6/*.o
p6/p6.o: p6/p6.c p6/graph.h p6/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p6/p6.c -o p6/p6.o
p6/graph.o: p6/graph.c p6/graph.h p6/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p6/graph.c -o p6/graph.o
p6/linkedlist.o: p6/linkedlist.c p6/linkedlist.h
	gcc -std=c99 -pedantic -Wall -c p6/linkedlist.c -o p6/linkedlist.o

clean:
	rm p1/*.o p2/*.o p3/*.o p4/*.o p5/*.o p6/*.o p1/p1 p2/p2 p3/p3 p4/p4 p5/p5 p6/p6