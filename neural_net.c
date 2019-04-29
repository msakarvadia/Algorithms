#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

double sigmoid(double x);
double **matrixMultiply(double **a, double **b, size_t aRow, size_t ab, size_t bCol);
double *vectorByMatrix(double *a, double **b, size_t ab, size_t bCol);
void printMatrix(double **m, size_t rows, size_t cols);
double **createMatrix(size_t rows, size_t cols);

int main(void){
    printf("%f\n", sigmoid(.2));

    double **a = createMatrix(3,10);
    double **b = createMatrix(10,3);

    for(size_t i = 0; i < 3; ++i){
        for(size_t j=0; j<10; ++j){
            a[i][j] = b[j][i] = j;
        }
    }
    printMatrix(a, 3, 10);
    puts("");
    printMatrix(b, 10, 3);
    puts("");
    double **c = matrixMultiply(a, b, 3, 10, 3);
    printMatrix(c, 3, 3);
    puts("");


    return 0;
}

double sigmoid(double x){               //this is not a true sigmoid, 
    x-=0.5;
    return 1 / (1 + exp(-10*(x)));
    //return .5 + (exp(x)-exp(-x))/(exp(x)+exp(-x));
}

double **matrixMultiply(double **a, double **b, size_t aRow, size_t ab, size_t bCol){
    double **out = malloc(aRow*sizeof(double*));
    for(size_t i = 0; i< aRow; ++i){
        out[i] = calloc(bCol, sizeof(double));
    }
    for(size_t i = 0; i< aRow; ++i){
        for(size_t j = 0; j<bCol; ++j){
            for(size_t k=0; k<ab; ++k){
                out[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return out;
}

void printMatrix(double **m, size_t rows, size_t cols){
    for(size_t i = 0; i<rows; ++i){
        for(size_t j= 0; j<cols; ++j){
            printf("%.1f", m[i][j]);
            }
            puts("");
        }
    }

double **createMatrix(size_t rows, size_t cols){
    double **out = malloc(rows *sizeof(double*));
    for(size_t i = 0; i<rows; ++i){
        out[i] = malloc(cols * sizeof(double*));
        }
    return out;
}
