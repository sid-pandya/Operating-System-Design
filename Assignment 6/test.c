#include <stdio.h>
#include "malloc2.h"

int main(void) 
{
	
	size_t size = 20;
	int *ptr =(int *)malloc2(size);
	memcheck2(ptr,size);
	free2(ptr);
	realloc2(ptr,25);
	
	float *ptr2 = (float*)malloc2(30);
	memcheck2(ptr2,30);
	free2(ptr2);

	return 0;
}