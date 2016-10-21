Alan Cham
MPCS 551011 HW2 #4c

The following summarizes the results of various tests used to compare the
performance of simple v. self-balanced BST.

I.  Sequential Add Time

    For this comparison, I devised two similar tests.
    In the first test, 100 "words" were added in lexicographic order.
    In the second, 1000 "words" were added in the same manner.

    e.g.    add 001 "001"
            add 002 "002"
            add 003 "003"
            etc.
    
    The reason for this ordering is that since each successive word ranks
    higher than the previous one, this should create the most imbalanced
    BST possible, allowing us to observe something like a worst-case
    situation.

    The results show that the self-balancing BST took [0.154 ms] to complete
    the 100 adds, whereas the simple BST took [0.188 ms] to complete.
    We see that for a small number of elements, the two BST's take about
    the same amount of time.

    The results show that the self-balancing BST took [1.192 ms] to complete
    the 1000 adds, whereas the simple BST took [6.808 ms] to complete.
    From this, we observe that as the number of elements increases and the
    simple BST becomes increasingly unbalanced, it's efficiency greatly 
    diminishes. Between the 100 and 1000 element test cases, the self-
    balancing BST run-time grew by less than a factor of 10, whereas
    the simple BST run-time grew by more than a factor 30.

II. Random Add Time
    
    For this comparison I added 1000 "words" in random order.

    e.g.    add 003 "003"
            add 001 "001"
            add 225 "225"
            add 004 "004"
            etc.

    The results show that the self-balancing BST took [1.374 ms] to complete.
    The results show that the simple BST took [1.257 ms] to complete. 
    Compared to the results from Section I above, we can conclude that when
    the words are added randomly, the simple BST retains much of its efficiency.
    This is because randomly ordered insertions tend to produce a more balanced
    BST even without active re-balancing.

III.Random Find Time

    For this comparison I added 1000 "words" sequentially as in Section I.
    Then I randomly gave 1000 'find' commands.

    The results show that the self-balancing BST took [7.621 ms] to complete
    the 1000 adds and 1000 finds. The simple BST took [13.296 ms] to complete.
    Note that the 1000 adds take only a small portion of total time, based on
    Section I: [1.192 ms] and [6.808 ms] for the self-balancing and simple 
    BST's respectively. 

    If we estimate the time used just for the find portion, by subtracting
    the Section III raw times from the Section I times, we have:
    the self-balancing BST took about 6.5 ms and the simple BST took 6.5 ms
    as well. This is counter to expectations since the unbalanced simple
    BST would theoretically take more since each 'find' operation would
    take about O(n) time, whereas the balanced one should take O(log n) time.

IV. Random Delete Time
    
    Similar to Section III, in this section I added 1000 "words" sequentially.
    Then I gave 1000 random 'delete' commands.

    The results show that the self-balancing BST took [6.088 ms] and the simple
    BST took [7.678 ms]. This is also counter to expectation since one would
    expect the unbalanced BST to take O(n) time for each search and the
    self-balanced BST should take O(log n) time for each search. Although
    the simple BST took more time, the difference is not as stark as expected.

V.  Print Time

    Lastly, in this section I added 1000 "words" sequentially and then timed a
    single call to the 'print' operation.

    According to the results, the self-balancing BST took [1.403 ms] to 
    complete whereas the simple BST took [7.067 ms]. This is counter to 
    expectation as well. In previous tests it was expected that the simple 
    BST should take longer. However, when it comes to printing, both trees 
    should take the same amount of time, since all nodes have to be visited at
    least once. The operation should be O(n) in both trees.