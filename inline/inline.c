#include <stdio.h>
#include <stdlib.h>

double** read_arr(char* filename, size_t x_size, size_t y_size) {

    double** arr = (double**) malloc(sizeof(double*) * y_size + sizeof(double) * x_size * y_size);


    if (arr == NULL)
       return NULL;

    double* arr_start = (double*) (arr + y_size);
    for (size_t i = 0; i < y_size; ++i)
       arr[i] = arr_start + (i * x_size);


    FILE* f = fopen(filename, "rb");
    if (f == NULL)
       return NULL;

    size_t idx = 0;
    while (fread(arr[idx++], sizeof(double), x_size, f) > 0) {}

    fclose(f);
    return arr;

}

char __attribute__ ((noinline)) cmp_noinline(double a, double b) {

	return (a > b);	

}

static inline char cmp_inline(double a, double b) {

	return (a > b);

}

int main(int argc, char** argv) {
	
	size_t cnt_noinline = 0;
	size_t cnt_inline = 0;
	double** arr = read_arr("arr.dat", MAX_DIM, MAX_DIM);

	/*
	for (size_t i = 0; i < MAX_DIM; ++i) {
		for (size_t j = 0; j < MAX_DIM; ++j) {

			if (cmp_noinline(arr[i][j], 0.0))
				++cnt_noinline;

			if (cmp_inline(arr[i][j], 0.0))
				++cnt_inline;

		}
	}
	*/

	for (size_t i = 0; i < 1000000000; ++i) {
		
		cmp_inline(3.0, 0.0);
		cmp_noinline(3.0, 0.0);

	}

	free(arr);

	printf("cnt_noinline: %lu\n", cnt_noinline);
	printf("cnt_inline: %lu\n", cnt_inline);

	return 0;

}
