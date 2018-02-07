#include <stdio.h>
#include <stdlib.h>

#define DIMENSION 4

// Initialise a matrix, either random or zeroes
int** init(int isRandom) {
    int i;
    int** matrix = (int**) malloc(DIMENSION * sizeof(int));

    for (i = 0; i < DIMENSION; i++) {
        matrix[i] = (int*) malloc(DIMENSION * sizeof(int));
        int j;
        
        for (j = 0; j < DIMENSION; j++) {
            if (isRandom == 1) {
                matrix[i][j] = rand();
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

int main() {
    // Initialise matrices
    int** matrixA = init(1);
    int** matrixB = init(1);
    int** result_matrix = init(0);

    // Debug and print values
    print_matrix(matrixA);
    print_matrix(matrixB);
    print_matrix(result_matrix);

    // Free matrix memory
    free_matrix(matrixA);
    free_matrix(matrixB);
    free_matrix(result_matrix);

    return 0;
}
