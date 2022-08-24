#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VALUE_MAX 10.0
#define VALUE_MIN -10.0

double randfrom(double min, double max) {

    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);

}

void gen_array_contiguous() {

    double** arr = malloc(sizeof(double) * (MAX_DIM * MAX_DIM) + sizeof(double*) * MAX_DIM);
    double* arr_start = (double*) arr + MAX_DIM;

    for (size_t i = 0; i < MAX_DIM; ++i)
        *(arr + i) = arr_start + i;

    
    srand(time(NULL));
    double* idx = (double*) arr + MAX_DIM;
    double* end_idx = idx + (MAX_DIM * MAX_DIM);
    
    for (; idx < end_idx; ++idx) {
       *idx = randfrom(VALUE_MIN, VALUE_MAX);

    }

    FILE *f = fopen("arr.dat", "wb");
    fwrite(arr_start, sizeof(double), MAX_DIM * MAX_DIM, f);

    fclose(f);
    free(arr);

}

int main() {

    gen_array_contiguous();

    return 0;

}


