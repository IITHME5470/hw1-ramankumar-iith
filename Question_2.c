#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define EPSILON 1e-6 

void read_matrix(int n, double matrix[n][n]) {
    char filename[100];
    snprintf(filename, sizeof(filename), "inputfiles/mat_%06d.in", n);
    FILE *file = fopen(filename, "r");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%lf,", &matrix[i][j]);  // Read floating point values with commas
        }
    }
   
    fclose(file);
}

void read_vector(int n, int vecnum, double vector[n]) {
    char filename[100];
    snprintf(filename, sizeof(filename), "inputfiles/vec_%06d_%06d.in", n, vecnum);
    FILE *file = fopen(filename, "r");

    for (int i = 0; i < n; i++) {
        fscanf(file, "%lf,", &vector[i]);  // Read floating point values with commas
    }

    fclose(file);
}

int check_eigenvector(int n, double matrix[n][n], double vector[n], double *eigenvalue) {
 

    double product[n] ;
    for(int i=0;i<n;i++)product[i]=(double)0;
    double ratio = 0;
    bool ratio_set = false;

    // Matrix-vector multiplication
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            product[i] += matrix[i][j] * vector[j];
        }
    }

    // Check if the vector is an eigenvector
    for (int i = 0; i < n; i++) {
        if (fabs(vector[i]) > EPSILON) { // Avoid division by zero
            double current_ratio = product[i] / vector[i];
            if (!ratio_set) {
                ratio = current_ratio;
                ratio_set = true;
            } else if (fabs(current_ratio - ratio) > EPSILON) {
                return false; // Not an eigenvector
            }
        } else if (fabs(product[i]) > EPSILON) {
            return false; // product[i] should also be zero if vector[i] is zero
        }
    }

    *eigenvalue = ratio;
    return true;
}



void write_eigenvector_result(int vecnum, int n, int is_eigenvector, double eigenvalue) {
    char filename[100];
    snprintf(filename, sizeof(filename), "inputfiles/vec_%06d_%06d.in", n, vecnum);
    FILE *file = fopen(filename, "a");

    if (is_eigenvector) {
        fprintf(file, "Eigenvalue: %lf\n", eigenvalue);
        printf("vec_%06d_%06d.in : Yes : %lf\n", n, vecnum, eigenvalue);
    } else {
        printf("vec_%06d_%06d.in : Not an eigenvector\n", n, vecnum);
    }

    fclose(file);
}

int main() {
    // Read n from the input file 'input.in'
    FILE *input_file = fopen("inputfiles/input.in", "r");
    if (input_file == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    int n;
    fscanf(input_file, "%d", &n);
    fclose(input_file);

    // Allocate memory for the matrix and vectors
    double matrix[n][n];
    read_matrix(n, matrix);

    int vecnum = 1;
    double vector[n];

    // Read and check vectors
    while (1) {
        read_vector(n, vecnum, vector);

        char filename[100];
        snprintf(filename, sizeof(filename), "inputfiles/vec_%06d_%06d.in", n, vecnum);
        FILE *test_file = fopen(filename, "r");
        if (test_file == NULL) {
            
            break;
        }
        fclose(test_file);

        double eigenvalue;
        int is_eigenvector = check_eigenvector(n, matrix, vector, &eigenvalue);
        write_eigenvector_result(vecnum, n, is_eigenvector, eigenvalue);

        vecnum++;
    }

    return 0;
}
