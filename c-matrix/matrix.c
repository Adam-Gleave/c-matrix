#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

// Matrix x/y dimension
#define DIMENSION 4
// Number of threads to spawn
#define NUM_THREADS 4

// Structure to pass to threads
struct Matrices {
	int id;
    int** a;
    int** b;    
    int** result;
};

// Return a random number between 0 and 10
int random_num() {
    return rand() % 10;
}

// Initialise a matrix, either random or zeroes
int** init(int is_random) {
    int i;
    int** matrix = malloc(DIMENSION * sizeof(int));

    for (i = 0; i < DIMENSION; i++) {
        matrix[i] = malloc(DIMENSION * sizeof(int));
        int j;
        
        for (j = 0; j < DIMENSION; j++) {
            if (is_random == 1) {
                matrix[i][j] = random_num();
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }
    
    return matrix;
}

// Debug: Print matrix values
void print_matrix(int** matrix) {
    printf("Matrix values:");
    int i;

    for (i = 0; i < DIMENSION; i++) {
        printf("\n");
        int j;

        for (j = 0; j < DIMENSION; j++) {
            printf("%i, ", matrix[i][j]);
        }
    }

    printf("\n\n");
}

// Single-threaded O(n^3) multiplication algorithm
void multiply_single(int** a, int** b, int** result) {
    int i;

    for (i = 0; i < DIMENSION; i++) {
        int j;
        int sum = 0;

        for (j = 0; j < DIMENSION; j++) {
            int k;

            for (k = 0; k < DIMENSION; k++) {
                sum += a[i][k] * b[k][j];
            }

            result[i][j] = sum;
            sum = 0;
        }
    }
}

// Thread function 
void* runner(void* args) {
	struct Matrices* thread_data = (struct Matrices*) args;
	int id = (*thread_data).id;
	int i;
	int sum = 0;

	for (i = 0; i < DIMENSION; i++) {
		int j;

		for (j = 0; j < DIMENSION; j++) {
			sum += (*thread_data).a[id][j] * (*thread_data).b[j][i];
		}

		(*thread_data).result[id][i] = sum;
		sum = 0;
	}
}

// Multithreaded multiplication algorithm
void multiply_multi(int** a, int** b, int** result) {
    pthread_t* threads;
    threads = malloc(NUM_THREADS * sizeof(pthread_t));
    struct Matrices thread_data[NUM_THREADS];
    int i;

    for (i = 0; i < NUM_THREADS; i++) {
		thread_data[i].id = i;
    	thread_data[i].a = a;
    	thread_data[i].b = b;
    	thread_data[i].result = result;

    	pthread_create(&threads[i], NULL, runner, &thread_data[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
    	pthread_join(threads[i], NULL);
    }
}

int main() {
    // random number seed
    srand(time(NULL));

    // Initialise matrices
    int** matrixA = init(1);
    int** matrixB = init(1);
    int** result_matrix = init(0);

    // Debug and print values
    print_matrix(matrixA);
    print_matrix(matrixB);

    // Single-thread multiply and print result
    multiply_single(matrixA, matrixB, result_matrix);
    printf("Single threaded multiplication\n");
    printf("------------------------------\n");
    print_matrix(result_matrix);

    // Multi-threaded multiply and print result
    result_matrix = init(0);
    multiply_multi(matrixA, matrixB, result_matrix);
    printf("\nMulti threaded multiplication\n");
    printf("------------------------------\n");
    print_matrix(result_matrix);

    return 0;
}
