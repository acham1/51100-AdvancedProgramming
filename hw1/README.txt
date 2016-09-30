Name: Alan Cham
Assignment:	1

Shortcomings:
p1.c : 

p2.c : I got the idea of bitwise casting the float to an unsigned int from this 
	thread:
	https://stackoverflow.com/questions/12342926/casting-float-to-int-bitwise-in-c
	It compiles with -ansi -pedantic -Wall options without any warnings or errors.
	However, one very big flaw in this is that I assume floats are 32-bits and I 
	assume ints are also 32-bits, which may work in this case, but I'm not sure
	that is a generally valid assumption.

p3.c : My heapify function seems to be producing valid heaps, based on sample 
	tests. However, I haven't been able to replicate the example output from the
	instructions.

p4.c :

p5.c :

p6.c :

p7.c : When I tried raising the size of array (e.g. 2000 x 2000) I get seg fault.
	I think maybe it's because I'm exhausting my memory, but I'm not sure. Could
	you maybe check it out and let me know what you think? Thanks!
	Otherwise, it seems to work fine for the given parameters of 1000x1000.
	Also I used this thread to learn how to measure time in finer resolution
	than seconds:
	https://stackoverflow.com/questions/8558625/how-to-get-the-current-time-in-milliseconds-in-c-programming

p8.c : 