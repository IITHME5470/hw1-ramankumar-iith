#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to write the array to a file
void print_to_file(int n, double **A, int format_flag) {
  
    // Creating a file with req name

   

    char filename[50];
    if (format_flag == 0) {
        snprintf(filename, sizeof(filename), "array_%06d_asc.out", n);
    } else if (format_flag == 1) {
        snprintf(filename, sizeof(filename), "array_%06d_bin.out", n);
    } else {
        fprintf(stderr, "Invalid format flag!\n");
        return;
    }

    
    // Opening a file
    FILE *file = fopen(filename, (format_flag == 0) ? "w" : "wb");

    // array as per format_flag
    if (format_flag == 0) {
        // ASCII format
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fprintf(file, "%.15f ", A[i][j]);
            }
            fprintf(file, "\n");
        }
    } else if (format_flag == 1) {
        // binary format
        for (int i = 0; i < n; i++) {
            fwrite(A[i], sizeof(double), n, file);
        }
    }

    fclose(file);
    printf("Data written to %s\n", filename);
}

int main() {
    // Read n from the input file
    FILE *input_file = fopen("q1_input.in", "r");

    int n;
    fscanf(input_file, "%d", &n);
    fclose(input_file);
    printf("%d",n);

    //  2D array
    double **A = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        
    }

    // A[i][j] = i + j
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = i + j;
        }
    }

    // print_to _file function with format flag as 0 or 1.
    print_to_file(n, A, 0); //  ASCII format
    print_to_file(n, A, 1); //  binary format

    // Free the dynamically allocated memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);

    return 0;
}
