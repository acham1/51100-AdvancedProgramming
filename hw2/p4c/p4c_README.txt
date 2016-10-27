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

    The results show that the self-balancing BST took [0.161 ms] to complete
    the 100 adds, whereas the simple BST took [0.192 ms] to complete.
    We see that for a small number of elements, the two BST's take about
    the same amount of time.

    Then when I increased the problem size by a factor of 10, comprised of 1000
    sequential adds, the results show that the self-balancing BST took [1.636 ms] 
    to complete the 1000 adds, whereas the simple BST took [6.956 ms] to complete.

    Thus when the problem size increased ten-fold, the balanced run-time only
    increased by a factor of about 10.2, whereas the simple BST run-time increased
    by a factor of 36.2.


II. Random Add Time
    
    For this comparison I added 1000 "words" in random order.

    e.g.    add 003 "003"
            add 001 "001"
            add 225 "225"
            add 004 "004"
            etc.

    The simple BST took [1.326 ms] to complete the 1000 random adds, and the 
    self-balanced BST took [1.416 ms]. Note that in both cases, less time was
    used than in the sequential add. This is because the number of collisions 
    increases as the number of random adds increases, since I am only generating
    numbers in a finite range 1..1000. When a collision occurs, the tree is still
    used to experience the collision, but balancing operations are not needed,
    since no element is added. 

    Also, it is interesting that in this case, the simple and balanced BST's 
    performed roughly the same. I believe this is due to the random nature of 
    the adds producing a naturally more balanced tree, so the simple BST
    saves a lot of time during each search, by not having to the elements in
    O(n) but more close to O(log n).

III.Random Find Time

    For this comparison I added 1000 "words" sequentially as in Section I.
    Then I randomly gave 1000 'find' commands.

    The results show that the self-balancing BST took [2.865 ms] to complete
    the 1000 adds and 1000 finds. The simple BST took [13.398 ms] to complete.
    Subtracting the results from Section I, I estimate that the self-balancing
    BST used [2.865-1.636 = 1.229 ms] for just the finding portion, whereas 
    the simple BST took [13.398-6.956 = 6.442 ms] for just the finding portion.

    In this case, even though the find commands were given randomly, the tree
    was first built using sequential adds, so the simple BST couldn't benefit
    from the random nature of the find commands, given that its shape is 
    inherently more inefficient than the balanced BST.

IV. Random Delete Time

    Similar to Section III, in this section I added 1000 "words" sequentially.
    However, this time I gave 1000 random 'delete' commands subsequently.

    THe self-balancing tree took [2.867 ms] in total, compard to the simple
    BST's [7.98 ms]. Subtracting the Section I results, I estimate that
    the self-balancing tree used [2.867-1.636 = 1.231 ms] for just the deletions
    and the simple BST used [7.98-6.956 = 1.024 ms] for the deletions. This 
    is a dramatic improvement for the simple BST when comparing against its 
    random find performance in Section III. 

    This demonstrates that although the self-balanced BST is slower to increase
    run-time for larger problem sizes, it is also slower to reduce run-time
    as the problem size decreases. The simple BST on the other hand improves
    dramatically with each delete command, as it shrinks down the very 
    imbalanced list of elements it must iterate through for subsequent deletes.

V.  Print Time

    Lastly, in this section I added 1000 "words" sequentially and then timed a
    single call to the 'print' operation.

    The simple BST took [7.125 ms] total, and the balanced took [1.818 ms].
    Subtracing the results from Section I, I estimate that the simple BST
    used [7.125-6.956 = 0.169 ms] for the printing alone, and the balanced
    BST used [1.818-1.636 = 0.182 ms] for the printing alone. They came out 
    about the same, as expected, because for both types of trees, a full traversal
    must take at least O(n), so there is no advantage from the balanced BST's
    shape in this case.
    