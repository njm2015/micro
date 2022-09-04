#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    double** arr = read_arr("./arr.dat", MAX_DIM, MAX_DIM);
    
	double row_2d, col_2d, row_1d;
	clock_t begin[3], end[3];

	begin[0] = clock();
	row_2d = avg_2d_row(arr, MAX_DIM, MAX_DIM, 100);
	end[0] = clock();

	begin[1] = clock();
	col_2d = avg_2d_col(arr, MAX_DIM, MAX_DIM, 100);
	end[1] = clock();

	begin[2] = clock();
	row_1d = avg_1d(arr[0], MAX_DIM * MAX_DIM, 100);
	end[2] = clock();

	printf("%lf\n", row_2d);
    printf("%lf\n", col_2d);
    printf("%lf\n", row_1d);

	for (size_t i = 0; i < 3; ++i)
		printf("%lf sec\n", ((double) (end[i] - begin[i])) / CLOCKS_PER_SEC);

    free(arr);

    return 0;
}

