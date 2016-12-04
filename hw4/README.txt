Alan Cham
MPCS 51100
November 31, 2016
HW 4 README

  I.    P1 Serial All-Pairs

*******************************************************************************

 II.    P2 Parallelization Outside Dijkstra

*******************************************************************************

III.    P3 Parallelization Inside Dijkstra

*******************************************************************************

 IV.    P4 Periodicity
        https://en.wikipedia.org/wiki/Aperiodic_graph
        - Perform a depth-first search of G. 
        - For each e in G that connects a vertex on level i of the depth-
        - first search tree to a vertex on level j, let ke = j - i - 1.
        - Compute greatest common divisor of the set of numbers ke.

*******************************************************************************

  V.    P5 Irreducibility
        https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm
        For each vertex u of the graph, mark u as unvisited. Let L be empty.
        For each vertex u of the graph do Visit(u), where Visit(u) is the 
            recursive subroutine:
            If u is unvisited then:
                Mark u as visited.
                For each out-neighbour v of u, do Visit(v).
                Prepend u to L.
            Otherwise do nothing.
        For each element u of L in order, do Assign(u,u) where Assign(u,root) 
            is the recursive  subroutine:
            If u has not been assigned to a component then:
                Assign u as belonging to the component whose root is root.
                For each in-neighbour v of u, do Assign(v,root).
            Otherwise do nothing.

*******************************************************************************

 VI.    P6 Stationary Probabilities
        Start with first vertex and randomly move to next one.
