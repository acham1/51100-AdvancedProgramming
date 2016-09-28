Name: Alan Cham
Assignment:	1

Shortcomings:
p1.c : 

p2.c : I got the idea of bitwise casting the float to an unsigned int from this thread:
	https://stackoverflow.com/questions/12342926/casting-float-to-int-bitwise-in-c
	It compiles with -ansi -pedantic -Wall options without any warnings or errors. However,
	one very big flaw in this is that I assume floats are 32-bits and I assume ints are
	also 32-bits, which may work in this case, but I don't think is a generally valid 
	assumption.

