Alan Cham
MPCS 51100
November 31, 2016
HW 4 README

  I.    P1 Serial All-Pairs
        When running serial all-pairs Dijkstra on the small graph, total time
        was 12.58 s. 

*******************************************************************************

 II.    P2 Parallelization Outside Dijkstra
        When parallelizing outside Dijkstra with different number of cores, the
        total times were:

        1  core: 12.58 s
        2  core:  8.25 s
        4  core:  4.21 s
        8  core:  2.28 s
        16 core:  1.35 s

        The 1-core time matched almost exactly with the serial time, so thread
        creation was not a significant relative cost. Scaling was not perfect,
        but surprisingly the best scaling occurred between the 2-core and 
        4-core times. For the number of cores tested in these trials, each 
        doubling of the number of cores produced a time improvement factor
        between 1.5x and 2x.

*******************************************************************************

III.    P3 Parallelization Inside Dijkstra
        For parallelization inside Dijkstra, I attempted to modify Dijkstra to
        use an unsorted array instead of a min-heap priority queue. The idea
        was that the extract-min operation would change from O(lg n) to O(n),
        but the decrease-key operation would change from O(lg n) to O(1). 
        Finding the min element of the heap entailed iterating over all 
        vertices to compare keys. Updating a vertex's distance entailed a
        O(1) lookup of its index in the array. The following were the total 
        times:

        1 core: 681.05 s
        2 core: 652.58 s
        4 core: 521.46 s
        8 core: 525.06 s

        This modification did not succeed in improving the all-pairs Dijkstra
        run time, and interestingly the 16-core time was exceptionally long,
        and was terminated before completion.
        
*******************************************************************************

 IV.    P4 Periodicity
        The periodicity of the graph was determined by implementing Shier's BFS
        based algorithm: http://cecas.clemson.edu/~shierd/Shier/markov.pdf
        The periodicity of the provided markov graph was 2.
        
*******************************************************************************

  V.    P5 Irreducibility
        Irreducibility of the graph was determined by modifying Kosaraju's
        algorithm: https://en.wikipedia.org/wiki/Kosaraju%27s_algorithm
        Instead of identifying the strongly connected components of the graph,
        we need only verify that there is exactly one strongly connected
        component. This I achieve with a single dfs from an arbitrary vertex,
        and (1) all vertices should be visited. Then I run dfs from the same
        vertex using the graph transpose, and (2) all vertices should be
        visited. If in either case there were untouched vertices, then the
        graph is not irreducible. The provided markov graph was irreducible.

*******************************************************************************

 VI.    P6 Stationary Probabilities
        The following were the stationary probabiities from the provided 
        markov graph, after 1e6 samples. After some prelimary checking, this
        graph also seems to be bipartite, which is corroborated by the found
        period of 2. Since the graph is irreducible, and edge weights are 
        positive, I know that every state should have a non-zero stationary 
        probability. Furthermore, there must exist a partition of this graph
        such that every even sample is from one partition and every odd sample
        is from the other. Thus, for an even sample, a group of vertices should
        have effectively 0% stationary probability, and all other vertices 
        would have effectively 0% stationary probabiliy for odd samples.

        >>  Sampling 1E+06 times via Markov
        State  1: stationary probability 1.012%
        State  2: stationary probability 0.937%
        State  3: stationary probability 1.084%
        State  4: stationary probability 0.880%
        State  5: stationary probability 0.955%
        State  6: stationary probability 0.947%
        State  7: stationary probability 0.853%
        State  8: stationary probability 0.963%
        State  9: stationary probability 1.139%
        State 10: stationary probability 1.143%
        State 11: stationary probability 1.078%
        State 12: stationary probability 0.970%
        State 13: stationary probability 1.045%
        State 14: stationary probability 1.068%
        State 15: stationary probability 1.008%
        State 16: stationary probability 0.950%
        State 17: stationary probability 0.955%
        State 18: stationary probability 0.960%
        State 19: stationary probability 0.991%
        State 20: stationary probability 0.978%
        State 21: stationary probability 1.010%
        State 22: stationary probability 1.200%
        State 23: stationary probability 1.119%
        State 24: stationary probability 1.022%
        State 25: stationary probability 0.903%
        State 26: stationary probability 1.107%
        State 27: stationary probability 1.022%
        State 28: stationary probability 0.967%
        State 29: stationary probability 0.957%
        State 30: stationary probability 1.075%
        State 31: stationary probability 1.049%
        State 32: stationary probability 1.045%
        State 33: stationary probability 0.749%
        State 34: stationary probability 1.021%
        State 35: stationary probability 1.016%
        State 36: stationary probability 1.077%
        State 37: stationary probability 0.979%
        State 38: stationary probability 0.993%
        State 39: stationary probability 1.033%
        State 40: stationary probability 0.842%
        State 41: stationary probability 0.912%
        State 42: stationary probability 0.934%
        State 43: stationary probability 1.033%
        State 44: stationary probability 0.911%
        State 45: stationary probability 1.101%
        State 46: stationary probability 0.934%
        State 47: stationary probability 1.091%
        State 48: stationary probability 1.116%
        State 49: stationary probability 0.976%
        State 50: stationary probability 0.820%
        State 51: stationary probability 1.080%
        State 52: stationary probability 0.901%
        State 53: stationary probability 1.083%
        State 54: stationary probability 0.918%
        State 55: stationary probability 0.932%
        State 56: stationary probability 0.870%
        State 57: stationary probability 1.053%
        State 58: stationary probability 0.941%
        State 59: stationary probability 1.105%
        State 60: stationary probability 1.111%
        State 61: stationary probability 1.023%
        State 62: stationary probability 0.884%
        State 63: stationary probability 0.946%
        State 64: stationary probability 1.025%
        State 65: stationary probability 1.008%
        State 66: stationary probability 1.052%
        State 67: stationary probability 0.897%
        State 68: stationary probability 1.067%
        State 69: stationary probability 1.003%
        State 70: stationary probability 0.885%
        State 71: stationary probability 0.976%
        State 72: stationary probability 0.954%
        State 73: stationary probability 1.130%
        State 74: stationary probability 1.057%
        State 75: stationary probability 1.030%
        State 76: stationary probability 1.018%
        State 77: stationary probability 1.029%
        State 78: stationary probability 0.997%
        State 79: stationary probability 1.131%
        State 80: stationary probability 1.089%
        State 81: stationary probability 1.015%
        State 82: stationary probability 0.893%
        State 83: stationary probability 0.946%
        State 84: stationary probability 0.949%
        State 85: stationary probability 1.095%
        State 86: stationary probability 0.973%
        State 87: stationary probability 0.930%
        State 88: stationary probability 1.004%
        State 89: stationary probability 1.073%
        State 90: stationary probability 1.024%
        State 91: stationary probability 1.064%
        State 92: stationary probability 1.099%
        State 93: stationary probability 0.982%
        State 94: stationary probability 1.042%
        State 95: stationary probability 1.076%
        State 96: stationary probability 0.905%
        State 97: stationary probability 0.942%
        State 98: stationary probability 0.961%
        State 99: stationary probability 1.039%
        State 100: stationary probability 0.866%