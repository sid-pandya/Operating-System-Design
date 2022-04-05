#ifndef malloc2_h
#define malloc2_h

#include<sys/types.h>		
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void memcheck2(void *ptr, size_t size);
void free2(void *ptr);
void *realloc2(void *ptr, size_t size); 
void *malloc2(size_t size);

#endif
