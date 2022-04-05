#include "malloc2.h"

//malloc2 function
void *malloc2(size_t size)
{
	printf("malloc2 is called. \n");
	int * ptr;
	if (size == 0)
	{	
		printf("Memory size = 0.\n");	
	}
	else
		ptr = malloc(size);  
}

//free2 function	
void free2(void *ptr)
{
	printf("free2 is called. \n");
	int *ptr1;
	if (ptr != ptr1)
	{
		printf("Pointer isn't pointing to the first node.\n");
	}
	else
	{
		free(ptr);
	}
}

//realloc2 function
void *realloc2(void *ptr, size_t size)
{
	printf("realloc2 function is called.\n");
	int * ptr2;
	
	if (ptr == NULL)
	{
		ptr = malloc2(size);
		printf("Memory allocated using malloc2.\n");
	}
	else if ( ptr != NULL && size == 0)
	{
		printf("Size is 0. Memory will be freed.\n");	
		free2(ptr);
	}
	else
	{
		ptr2=realloc(ptr,size);	
		if(ptr2==ptr)
		{
			printf("Memory reallocated using realloc() function");	
		}
	}
}

//memcheck2 function
void memcheck2(void *ptr, size_t size)
{
	printf("memcheck2 function is called.\n");
	size_t ptrsize;
	int i = 0;
	if (size == 0)
	{
		printf("Memory size = 0.\n");
		eiit(-1);  
	}
	
	ptrsize =(size_t)ptr;
	while( i <ptrsize)
	{			
		if (ptr++ == NULL)
		{
			printf("Null, Memory is not allocated properly");
			eiit(-1);  
		}
	i++;
	}
	
	if(ptr==NULL)
	{
		printf("Null Pointer");
		eiit(-1);
	}	
	
}

