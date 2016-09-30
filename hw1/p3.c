/* ==============================================================================

	3 - Heap - p3.c	

	A "heap" is defined as a one-dimensional array with the following property:	

	a[j/2] >= a[j]   for  1 <= j/2 < j <= N	

	where N/2 means "integer divide" -- that is, the result is
	truncated to the nearest integer. So for example:	

	a[1] >= a[2]; a[1] >= a[3];
	a[2] >= a[4]; a[2] >= a[5];
			  .
			  .
	This makes more sense if we think of it as a tree with a[1] at the root:	

	           a[1]
	          /    \
	        a[2]  a[3]
	        /  \     
	      a[4] a[5]	
	

	Then each "parent" must be greater than or equal to its two
	"children". In any case, this turns out to be a very convenient
	arrangement for performing further work very efficiently, such as
	sorting the array.	

	Write a function heapify as	

	void heapify(int *f, int n);	

	that arranges an arbitrary list of integers
	into a heap. For simplicity you should take the integers as input from argv and
	copy them to a separate array after converting with atoi() - this should be done
	in the following function:	

	int * allocate_array( int argc, char * argv[]);	

	NOTE - You are NOT allowed to call the C standard library quicksort or any other sorting
	function from within your heapify() function.	

	NOTE - You must implement an efficient heapify algorithm. Doing a full sort on the
	list (via an insertion sort or a quicksort algorithm, etc) will not count for credit, since
	these are less efficient than simply creating a heap.	

	Once you have implemented your heapify function, use it in a program that
	accepts an arbitrary length list of integers from the command line via argv, calls
	heapify() on this list, and then outputs the resulting list to stdout.	

	Here is the starting point for your file (You should only alter the
	heapify() function and the allocate_array() function. Do not alter test_heap
	or main.):	

	//See below	

	An example run might look like:	

	PROMPT>> ./p3 3 1 2 7 4 0 2
	7 4 3 2 0 2 1 
	Heap test success!
	(program ends)

============================================================================== */

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
  
/* return the index of a node's parent */
int get_parent(int pos) {
	return pos % 2 ? pos/2 : pos/2 - 1;
}

/* recursively raise a value's position in the heap until heap rules are obeyed */
void ascend_tree(int *f, int node_pos) {
	int temp;
	int parent_pos = get_parent(node_pos);

	if (node_pos != 0 && f[node_pos] > f[parent_pos]) {
		temp = f[parent_pos];
		f[parent_pos] = f[node_pos];
		f[node_pos] = temp;
		ascend_tree(f, parent_pos);
	}
}

void heapify(int *f, int n) {
	int parent_pos, array_pos = 0;

	while (++array_pos < n) {
		parent_pos = get_parent(array_pos);
		if (f[array_pos] > f[parent_pos]) {
			ascend_tree(f, array_pos);
		}
	}
}

int * allocate_array( int argc, char * argv[]) {
	int * array = calloc(argc - 1, sizeof(int));
	while (--argc > 0) {
		array[argc - 1] = atoi(argv[argc]);
	}
	return array;
}

int test_heap( int * f, int n)
{
	int i;
	int child_A, child_B;

	for( i = 0; i < n; i++ )
	{
		child_A = ( 2 * i ) + 1;
		child_B = ( 2 * i ) + 2;

		if( child_A < n )
			if( f[i] < f[child_A] )
				return -1;
		
		if( child_B < n )
			if( f[i] < f[child_B] )
				return -1;
	}

	return 1;
}

int main(int argc, char * argv[])
{
	int result;
	int i;
	int n = argc - 1;
	int * arr = allocate_array( argc, argv );

	heapify( arr, n );
	result = test_heap( arr, n );

	for( i = 0; i < n; i++ )
		printf("%d ", arr[i]);
	printf("\n");

	if( result == 1 )
		printf("Heap test success!\n");
	else
		printf("Heap test failed.\n");

	free(arr);

	return 0;
}
