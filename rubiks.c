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
void b(int** cube);
void l(int** cube);
void r(int** cube);

int main(void){
    int** cube = makeCube();
    printCube(cube);
    while (true) {
        //int v=-1;
        //size_t p=0;
        printf("insert command (e = exit, f= fillCube): e,f\n");
        char cmd='x';
        cmd=getchar();
        if (cmd == 'x'){
            continue; 
        }
        else if(cmd =='e'){
            return 0;
        }
        else if(cmd =='f'){
            for(size_t r = 0; r < 3; ++r){
                for(size_t c = 3; c <6; ++c){
                    printf("for row %zu by col %zu\n enter w=1, o=2, r=3, b=4, g=5, y=6\n", r, c);
                    int n;
                    scanf("%d", &n);
                    cube[r][c] = n;
                    printCube(cube);
                }
            }
            for(size_t r = 3; r < 6; ++r){
                for(size_t c = 0; c <12; ++c){
                    printf("for row %zu by col %zu\n enter w=1, o=2, r=3, b=4, g=5, y=6\n", r, c);
                    int n;
                    scanf("%d", &n);
                    cube[r][c] = n;
                    printCube(cube);
                }
            }         
            for(size_t r = 6; r < 9; ++r){
                for(size_t c = 3; c <6; ++c){
                    printf("for row %zu by col %zu\n enter w=1, o=2, r=3, b=4, g=5, y=6\n", r, c);
                    int n;
                    scanf("%d", &n);
                    cube[r][c] = n;
                    printCube(cube);
                }
            }
        }

        return 0;
    }
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
