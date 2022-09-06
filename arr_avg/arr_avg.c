#include <likwid-marker.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void clear_cache() {

	const long size = 1 * 1024 * 1024;		// 1MB (local L1d is 128kb)
	long* c = (long* ) malloc(size * sizeof(long));

	for (size_t i = 0; i < 0xff; ++i) {
		for (size_t j = 0; j < size; ++j) {
			
			c[j] = rand();
	
		}
	}

	free(c);

}


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

void print_arr_2d_row(double** arr, size_t x_dim, size_t y_dim) {

    double tot = 0.0;
    for (size_t i = 0; i < y_dim; ++i) {
        for (size_t j = 0; j < x_dim; ++j) {

            tot += arr[i][j];
            printf("%lf ", arr[i][j]);

        }

        printf("\n");
    }

    printf("%lf\n", tot);

}

void print_arr_2d_col(double** arr, size_t x_dim, size_t y_dim) {

    double tot = 0.0;
    for (size_t i = 0; i < x_dim; ++i) {
        for (size_t j = 0; j < y_dim; ++j) {

            tot += arr[j][i];
            printf("%lf ", arr[j][i]);

        }

        printf("\n");
    }

    printf("%lf\n", tot);

}

void print_arr_pointers(double** arr, size_t y_dim) {

    for (size_t i = 0; i < y_dim; ++i)
        printf("%p\n", arr[i]);

}

double avg_1d(double* arr, size_t x_dim, size_t ntimes) {

    double tot = 0.0;
    
    for (size_t n = 0; n < ntimes; ++n) {
        for (size_t i = 0; i < x_dim; ++i)
            tot += arr[i];
    }

    return tot / x_dim;

}

double avg_2d_row(double** arr, size_t x_dim, size_t y_dim, size_t ntimes) {

    double row_avg = 0.0;
    double tot_avg = 0.0;

    for (size_t n = 0; n < ntimes; ++n) {
        for (size_t i = 0; i < y_dim; ++i) {
            for (size_t j = 0; j < x_dim; ++j) {

                row_avg += arr[i][j];

            }

            tot_avg += (row_avg / x_dim);
            row_avg = 0.0;

        }
    }

    return tot_avg / y_dim;

}

double avg_2d_col(double** arr, size_t x_dim, size_t y_dim, size_t ntimes) {

    double col_avg = 0.0;
    double tot_avg = 0.0;

    for (size_t n = 0; n < ntimes; ++n) {
        for (size_t j = 0; j < x_dim; ++j) {
            for (size_t i = 0; i < y_dim; ++i) {

                col_avg += arr[i][j];

            }
            
            tot_avg += (col_avg / y_dim);
            col_avg = 0.0;

        }
    }

    return tot_avg / x_dim;

}

int main(int argc, char** argv) {

	LIKWID_MARKER_INIT;

    double** arr = read_arr("./arr.dat", MAX_DIM, MAX_DIM);
	double row_2d, col_2d, row_1d;

	LIKWID_MARKER_REGISTER("row2d");
	LIKWID_MARKER_REGISTER("col2d");
	LIKWID_MARKER_REGISTER("row1d");	

	clear_cache();

	LIKWID_MARKER_START("row2d");
	row_2d = avg_2d_row(arr, MAX_DIM, MAX_DIM, 1);
	LIKWID_MARKER_STOP("row2d");

	clear_cache();

	LIKWID_MARKER_START("col2d");
	col_2d = avg_2d_col(arr, MAX_DIM, MAX_DIM, 1);
	LIKWID_MARKER_STOP("col2d");

	clear_cache();

	LIKWID_MARKER_START("row1d");
	row_1d = avg_1d(arr[0], MAX_DIM * MAX_DIM, 1);
	LIKWID_MARKER_STOP("row1d");

	LIKWID_MARKER_CLOSE;

	printf("%lf\n", row_2d);
    printf("%lf\n", col_2d);
    printf("%lf\n", row_1d);

    free(arr);

    return 0;
}

