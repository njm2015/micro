#include <stdio.h>
#include <stdlib.h>

#ifndef INLINE
char __attribute__ ((noinline)) cmp(int a, int b) {

	return (a > b);	

}
#else
static inline char cmp(int a, int b) {

	return (a > b);

}
#endif

int main(int argc, char** argv) {
	
	size_t cnt= 0;
	for (size_t i = 0; i < 1000000000; ++i)
		cnt+= cmp(i, 0);

	printf("cnt: %lu\n", cnt);
	return 0;

}
