#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

int** makeCube();
void printCube(int** cube);
void u(int** cube);
void d(int** cube);
void f(int** cube);
void l(int** cube);
void r(int** cube);

int main(void){
    int** cube = makeCube();
    printCube(cube);
    cube[1][2] = 1;
    printCube(cube);

    return 0;
}

int** makeCube(){
    int **out = malloc(9 *sizeof(double*));
    for(size_t i = 0; i<9; ++i){
        out[i] = calloc(12, sizeof(int));
        }
    return out;
}

void printCube(int** cube){
    for(size_t r = 0; r < 9; r++){
        for(size_t c = 0; c <12; c++){
            printf("%d,", cube[r][c]);
        }
        puts("");
    }
    puts(" ");
}
