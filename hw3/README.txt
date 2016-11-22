Alan Cham
November 21, 2016
MPCS 51100
HW3 README

The executable for each part of the assignment will be located inside its
respective subdirectory of hw3 (e.g. the p3 executable will be located at 
hw3/p3/p3). In order to produce the executables for p1, p2, and p3, simply 
type "make" into the terminal from the hw3 directory and press return. Simply 
enter "make clean" from the hw3 directory to remove executables when finished.

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

I.  p1
        For p1, three hash functions were implemened. To specify which hash 
    function to use, enter an integer between 1-3 as a command-line argument 
    to the p1 executable. 

        This dictionary supports resizing, which is done at least once for any
    input size greater than 1 word, since the initial size of the map is only
    one bucket. The resizing occurs whenever the number of keys exceeds the
    default load factor of 0.7.

    Hash function 1: the string is prehashed and then the resulting integer is 
        simply modded over the number of buckets in the hash table.
    Hash function 2: the string is prehashed and then the resulting integer is 
        mapped to a bucket by the middle-square method.
    Hash function 3: the string is prehashed and then the resulting integer is 
        modded over the largest prime number not greater than the number of 
        buckets in the hash table.
    Prehashing: borrows from the Java string hash, which has the expression
        h(s) = s[0]*31^(n-1) + s[1]*31^(n-2) ... + s[n-1] for a string s with 
        length n.

        The following summarize results comparing the three hash methods'
    performances on the given test inputs, "dict.txt" and "dict2.txt":

        "dict.txt"
        Number of words:            200
        Total insertion time (ms):
        Max occupancy:  

        "dict2.txt"
        Number of words:            996
        Total insertion time (ms):
        Max occupancy:  

        "dict.txt" AND "dict2.txt"
        Number of words:            1196
        Total insertion time (ms):
        Max occupancy:

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

II. p2
        The uniq function is implemented to use the hash library from p1. The
    object whose uniqueness is in question is used as the key. The test driver 
    works by generating a random number between two bounds (by default 5,000 
    and 10,000). Suppose that number is X. Then another random number is 
    generated, called Y. An array of size X+Y is allocated. The first X entries 
    are the X unique integers from 0 to X-1. The subsequent Y entries are 
    filled by randomly selecting elements from the first X. Then the entire 
    array is scrambled randomly, and the array still holds exactly X unique 
    elements afterward. 

        This array is passed into uniq to determine the number of uniques, to 
    be compared against the known number. Since uniq should also put the uniq 
    elements into the beginning of the array, the first X elements of the 
    resulting array are traversed to verify that all integer values between 0 
    and X-1 have been placed into the resulting smaller array, stripped of 
    repetitions.

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

III.p3
        Using the data provided in the previous assignment, a study was 
    performed to determine the optimal number of bins and compare the new 
    method with the third method from the previous assignment.

        The results from the study are reproduced below:
    -------------------------------------------------------------------------
        Alan Cham
        HW3 P3
    -------------------------------------------------------------------------
    Making raw performance analysis results:
        Top    : total runtime (ms)
        Bottom : average runtime per iteration (ms)
    -------------------------------------------------------------------------
       Num Searches            Old     New(1 bin)    New(10 bin)   New(100 bin)  New(1000 bin) New(10000 bin)
           1.00e+00        82.1830        15.9470        15.9740        16.2210        19.0050        41.3060
                           82.1830        15.9470        15.9740        16.2210        19.0050        41.3060    

           1.00e+01        86.9750        16.2680        15.9650        16.1080        18.9520        40.5350
                            8.6975         1.6268         1.5965         1.6108         1.8952         4.0535    

           1.00e+02        56.6840        17.3680        16.4710        16.4280        19.0790        38.7310
                            0.5668         0.1737         0.1647         0.1643         0.1908         0.3873    

           1.00e+03        57.6460        30.7710        21.5860        19.8790        22.0910        41.3890
                            0.0576         0.0308         0.0216         0.0199         0.0221         0.0414    

           1.00e+04        85.9950       164.8500        70.0690        54.2280        50.0550        68.8590
                            0.0086         0.0165         0.0070         0.0054         0.0050         0.0069    

           1.00e+05       370.8380      1506.2060       560.5330       396.4160       335.1950       340.0600
                            0.0037         0.0151         0.0056         0.0040         0.0034         0.0034    

           1.00e+06      3212.3240     14885.0390      5465.1760      3822.3880      3163.4210      3033.3250
                            0.0032         0.0149         0.0055         0.0038         0.0032         0.0030    

    -------------------------------------------------------------------------
        Note   : Old refers to 3rd method in Hw2 P6; New refers to this hw's hash-like method
    -------------------------------------------------------------------------

        From this study we see that the new method is approximately on par with 
    the third method from the previous assignment when the number of bins is 
    least on the order of 1,000, increasing the bins to 10,000 gives the new 
    method a slightly greater advantage over the old method, but not by much. 
    Even with 10,000 bins, the old method takes 0.0032 ms per search, and the 
    new method takes 0.0030 ms per search. With fewer than 1000 bins, the old 
    method has a clear advantage.

        Based on these results, the optimal bin number is somewhere between 
    1,000 and 10,000, for the provided test input. Although increasing the
    bin number to 10,000 does yield a modest improvement in time per search,
    from 0.0032 to 0.003 ms, this is not significant in light of the the
    memory requirement increasing ten-fold. Improvements in time per iteration
    have begun to plateau by the time the number of bins has reached 1,000.

>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
