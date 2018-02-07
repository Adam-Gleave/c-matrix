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
struct matrices {
    int[DIMENSION][DIMENSION] a;
    int[DIMENSION][DIMENSION] b;
    int[DIMENSION][DIMENSION] result;
}

// Return a random number between 0 and 10
int random() {
    return rand() % 10;
}

// Initialise a matrix, either random or zeroes
int** init(int isRandom) {
    int i;
    int** matrix = (int**) malloc(DIMENSION * sizeof(int));

    for (i = 0; i < DIMENSION; i++) {
        matrix[i] = (int*) malloc(DIMENSION * sizeof(int));
        int j;
        
        for (j = 0; j < DIMENSION; j++) {
            if (isRandom == 1) {
                matrix[i][j] = random();
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }
    
    return matrix;
}

// Free matrix memory
void free_matrix(int** matrix) {
    int i;

    for (i = 0; i < DIMENSION; i++) {
        free(matrix[i]);
    }

    free(matrix);
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
        int sum;

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

void multiply_multi(int** a, int** b, result_matrix) {
    pthread_t* threads;
    threads = malloc(NUM_THREADS * sizeof(pthread_t));
}

int main() {
    // Random number seed
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
    free_matrix(result_matrix);
    result_matrix = init(0);
    print_matrix(result_matrix);
    multiply_multi(matrixA, matrixB, result_matrix)

    // Free matrix memory
    free_matrix(matrixA);
    free_matrix(matrixB);
    free_matrix(result_matrix);

    return 0;
}
