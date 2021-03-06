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
bool checkCube(int** cube, int row, int col);
bool checkWhiteCross(int** cube);
bool checkWhiteCornors(int** cube);
void swap(int** cube, int r1, int c1, int r2, int c2);
void makeWhiteX(int** cube);
void fillStdCube(int** cube);
void makeWhiteCornors(int**cube);
bool checkMiddle(int** cube);
void makeMiddle(int** cube);
void yellowL(int** cube);       //Acutally a yellow cross func
void yellowCornorPlace(int** cube); //puts yellow cornors in correct place before they can be oriented
bool checkYellowCornorPlace(int**cube);
bool checkYellowCornorUp(int** cube);
void yellowCornorUp(int** cube);
void fixYellowEdges(int** cube);


void standardScramble(int** cube){
    size_t i;
    srand(time(NULL));
    for(i = 0; i<50; i ++){
        int n = rand() %6;
        if(n==0)
            u(cube);
        if(n==1)
            d(cube);
        if(n==2)
            r(cube);
        if(n==3)
            l(cube);
        if(n==4)
            f(cube);
        if(n==5)
            b(cube);
        }
}


int main(void){
    size_t i,j;
    int** cube = makeCube();
    fillStdCube(cube);
    printCube(cube);     
    standardScramble(cube);
    makeWhiteX(cube);
    makeWhiteCornors(cube);
    makeMiddle(cube);
    yellowL(cube);
    yellowCornorPlace(cube);
    yellowCornorUp(cube);
    fixYellowEdges(cube);
    printCube(cube);     
    
    /*    while (true) {
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
            u(cube);
            printCube(cube);
            return 0;
            }   */
}

void fixYellowEdges(int** cube){
    size_t i,j;
   while(!((cube[4][8]==2)&&(cube[0][4]==5)&&(cube[4][0]==3)&&(cube[8][4]==4))){
        for(i=0;i<2;i++){
            if((cube[4][8]==2)&&(cube[0][4]==5)&&(cube[4][0]==3)&&(cube[8][4]==4))
                return;
           /* if(cube[0][4]==5)  {
                printf("cont\n");
                continue;
            }*/
            for(j=0;j<2;j++)
                l(cube);
            d(cube);
            f(cube);
            b(cube);
            for(j=0;j<2;j++)
                l(cube);
            for(j=0;j<3;j++)
                f(cube);
            for(j=0;j<3;j++)
                b(cube);
            d(cube);
            for(j=0;j<2;j++)
               l(cube);
            printCube(cube);
        }
       // if(cube[0][4]==5){
            for(i =0; i<2;i++){
                if((cube[4][8]==2)&&(cube[0][4]==5)&&(cube[4][0]==3)&&(cube[8][4]==4))
                    return;
                if(cube[4][8]==2){
                    printf("cont because orange is good\n");
                    break;
                }
                //do this if green is in right position
                for(j=0;j<2;j++)
                    f(cube);
                d(cube);
                for(j=0;j<3;j++)
                    r(cube);
                for(j=0;j<3;j++)
                    l(cube);
                for(j=0;j<2;j++)
                    f(cube);
                r(cube);
                l(cube);
                d(cube);
                for(j=0;j<2;j++)
                    f(cube);  
                printCube(cube);
            }          
      //  }
   /*     if(cube[8][4] ==2){
            for(i =0; i<3;i++){
                if((cube[8][8]==2)&&(cube[0][4]==5)&&(cube[4][0]==3)&&(cube[8][4]==4))
                    return;
                //if blue is correct pos
                for(j=0;j<2;j++)
                    b(cube);
                d(cube);    
                l(cube);
                r(cube);
                for(j=0;j<2;j++)
                    b(cube);
                for(j=0;j<3;j++)
                    l(cube);
                for(j=0;j<3;j++)
                    r(cube);
                d(cube);
                for(j=0;j<2;j++)
                    b(cube);
                printCube(cube);
            }
        } 
        if(cube[4][0]==3){
            for(i =0; i<3;i++){
                if((cube[4][8]==2)&&(cube[0][4]==5)&&(cube[4][0]==3)&&(cube[8][4]==4))
                    return;
                //if red is in correct spot
                for(j=0;j<2;j++)
                    r(cube);
                d(cube);
                for(j=0;j<3;j++)
                    b(cube);
                for(j=0;j<3;j++)
                    f(cube);
                for(j=0;j<2;j++)
                    r(cube);
                b(cube);
                f(cube);
                d(cube);
                for(j=0;j<2;j++)
                    r(cube);

                printCube(cube);
            }
        }     */
        //else do this    
   } 
    return;
}

int** makeCube(){    
    int **out = malloc(9 *sizeof(double*));
    for(size_t i = 0; i<9; ++i){
        out[i] = calloc(12, sizeof(int));
    }
    return out;
}

void fillStdCube(int** cube){
    for(int r = 0; r < 3; ++r){
        for(int c = 3; c <6; ++c){
            cube[r][c] = 5; //this face is green
        }
    }
    for(int r = 3; r < 6; ++r){
        for(int c = 0; c <3; ++c)
            cube[r][c] = 3; //this face is red
        for(int c = 3; c <6; ++c)
            cube[r][c] = 1; //this face is white
        for(int c = 6; c <9; ++c)
            cube[r][c] = 2; //this face is orange
        for(int c = 9; c <12; ++c)
            cube[r][c] = 6; //this face is yellow
    }
    for(int r = 6; r < 9; ++r){
        for(int c = 3; c <6; ++c){
            cube[r][c] = 4; //this face is blue
        }
    }
}

bool checkYellowCornorUp(int** cube){
    if(cube[3][8]==2 && cube[0][5]==5){
        if(cube[3][0]==3 && cube[0][3]==5){
            if(cube[5][0]==3 && cube[8][3]==4){
                if(cube[5][8]==2 && cube[8][5]==4){
                    return true;
                }

            }

        }

    }
    return false;
}

void yellowCornorUp(int** cube){
    int i, j;
    while(!(checkYellowCornorUp(cube))){
        if((cube[5][11]==6)){
            d(cube);
        }
        if(!(cube[5][11]==6)){
            for(i = 0; i<3;i++)
                l(cube);
            for(i = 0; i<3;i++)
                u(cube);
            l(cube);
            u(cube);
        }
    }
    return;
}

bool checkYellowCornorPlace(int**cube){
    if(((cube[3][8]==2)||(cube[3][9]==2)||(cube[0][5]==2))&&((cube[3][8]==5)||(cube[3][9]==5) ||(cube[0][5]==5))){
        if((cube[3][8]+cube[3][9]+cube[0][5])==13){
            if((cube[3][11]==3|| cube[3][0]==3 ||cube[0][3]==3)&&(cube[3][11]==5|| cube[3][0]==5 ||cube[0][3]==5)){
                if((cube[3][11]+cube[3][0]+cube[0][3])==14){
                    if((cube[5][11]==3|| cube[5][0]==3 ||cube[8][3]==3)&&(cube[5][11]==4|| cube[5][0]==4 ||cube[8][3]==4)){
                        if((cube[5][11]+cube[5][0]+cube[8][3])==13){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void yellowCornorPlace(int** cube){
    int i,j;
    while(!checkYellowCornorPlace(cube)){
        for(i=0; i<3; i++){
            if(checkYellowCornorPlace(cube))
                return;
            for(j=0; j<3; j++)
                r(cube);
            for(j=0; j<3; j++)
                d(cube);
            for(j=0; j<3; j++)
                l(cube);
            d(cube);
            r(cube);
            for(j=0; j<3; j++)
                d(cube);
            l(cube);
            d(cube);
            if(checkYellowCornorPlace(cube))
                return;
            for(j=0; j<3; j++){
                d(cube);
                if(checkYellowCornorPlace(cube))
                    return;
            }
        }
        d(cube);
    }
    return;
}

void yellowL(int** cube){      //whill actulally make a yellow cross
    int i, j;
    while(!((cube[4][9]==6)&& (cube[3][10]==6)&& (cube[4][11]==6)&&(cube[5][10]==6))){
        for(i=0; i<4; i++){
            if((cube[4][9]==6)&& (cube[3][10]==6)&& (cube[4][11]==6)&&(cube[5][10]==6))
                return;
            f(cube);
            l(cube);
            d(cube);
            for(j=0;j<3; j++)
                l(cube);
            for(j=0;j<3; j++)
                d(cube);
            for(j=0;j<3; j++)
                f(cube);
                
        }
        d(cube);
    }
    return;
}

void makeMiddle(int** cube){
    int i, j;
    while(!checkMiddle(cube)){
        //blue and orange 
        for(i = 0; i<4; ++i){
            if((cube[7][5]==4)&&(cube[5][7]==2))     {
                continue;                             }
            for(j=0;j<3;j++)
                d(cube);
            r(cube);
            d(cube);
            for(j=0;j<3;j++)
                r(cube);
            d(cube);
            f(cube);
            for(j=0;j<3;j++)
                d(cube);
            for(j=0;j<3;j++)
                f(cube);
            printf("blue and orange\n");
        }
        for(i = 0; i<1; ++i){
            if((cube[7][5]==4)&&(cube[5][7]==2))     {
                continue;                             }
            r(cube);
            d(cube);
            for(j=0;j<3;j++)
                r(cube);
            d(cube);
            f(cube);
            for(j=0;j<3;j++)
                d(cube);
            for(j=0;j<3;j++)
                f(cube);
            printf("blue and orange\n");
        }
        for(i = 0; i<3; ++i){
            if((cube[7][5]==4)&&(cube[5][7]==2))     {
                continue;                             }
            for(j=0;j<3;j++)
                d(cube);
            r(cube);
            d(cube);
            for(j=0;j<3;j++)
                r(cube);
            d(cube);
            f(cube);
            for(j=0;j<3;j++)
                d(cube);
            for(j=0;j<3;j++)
                f(cube);
            printf("blue and orange\n");
        }
        //blue and red 
        for(i = 0; i<4; ++i){
            if((cube[7][3]==4)&&(cube[5][1]==3))    {
                continue;                          }
            for(j=0;j<3;j++)
                d(cube);
            for(j=0;j<3;j++)
                f(cube);
            d(cube);
            f(cube);
            d(cube);
            l(cube);
            for(j=0;j<3;j++)
                d(cube);
            for(j=0;j<3;j++)
                l(cube);
            printf("blue and red\n");
        }
        for(i = 0; i<1; ++i){
            if((cube[7][3]==4)&&(cube[5][1]==3))    {
                continue;                          }
            for(j=0;j<3;j++)
                f(cube);
            d(cube);
            f(cube);
            d(cube);
            l(cube);
            for(j=0;j<3;j++)
                d(cube);
            for(j=0;j<3;j++)
                l(cube);
            printf("blue and red\n");
        }
        for(i = 0; i<3; ++i){
            if((cube[7][3]==4)&&(cube[5][1]==3))    {
                continue;                          }
            for(j=0;j<3;j++)
                d(cube);
            for(j=0;j<3;j++)
                f(cube);
            d(cube);
            f(cube);
            d(cube);
            l(cube);
            for(j=0;j<3;j++)
                d(cube);
            for(j=0;j<3;j++)
                l(cube);
            printf("blue and red\n");
        }
        //red and green
        for(i = 0; i<4; ++i){
            if((cube[3][1]==3)&&(cube[1][3]==5))  {
                continue;                         }
            for(j=0;j<3;j++)
                d(cube);
            for(j=0;j<3;j++)
                l(cube);
            d(cube);
            l(cube);
            d(cube);
            for(j=0;j<3;j++)
                b(cube);
            for(j=0;j<3;j++)
                d(cube);
            b(cube);
            printf("red and green\n");
        }
        for(i = 0; i<1; ++i){
            if((cube[3][1]==3)&&(cube[1][3]==5))  {
                continue;                         }
            for(j=0;j<3;j++)
                l(cube);
            d(cube);
            l(cube);
            d(cube);
            for(j=0;j<3;j++)
                b(cube);
            for(j=0;j<3;j++)
                d(cube);
            b(cube);
            printf("red and green\n");
        }
        for(i = 0; i<3; ++i){
            if((cube[3][1]==3)&&(cube[1][3]==5))  {
                continue;                         }
            for(j=0;j<3;j++)
                d(cube);
            for(j=0;j<3;j++)
                l(cube);
            d(cube);
            l(cube);
            d(cube);
            for(j=0;j<3;j++)
                b(cube);
            for(j=0;j<3;j++)
                d(cube);
            b(cube);
            printf("red and green\n");
        }
        //green and orange       
        for(i = 0; i<4; ++i){
            if((cube[1][5]==5)&&(cube[3][7]==2)){
                continue;}
            for(j=0;j<3;j++)
                d(cube);
            b(cube);
            d(cube);
            for(j=0;j<3;j++)
                b(cube);
            d(cube);
            for(j=0;j<3;j++)
                r(cube);
            for(j=0;j<3;j++)
                d(cube);
            r(cube);
            printf("green and orange\n");
        }
        for(i = 0; i<1; ++i){
            if((cube[1][5]==5)&&(cube[3][7]==2)){
                continue;}
            b(cube);
            d(cube);
            for(j=0;j<3;j++)
                b(cube);
            d(cube);
            for(j=0;j<3;j++)
                r(cube);
            for(j=0;j<3;j++)
                d(cube);
            r(cube);
            printf("green and orange\n");
        }
        for(i = 0; i<3; ++i){
            if((cube[1][5]==5)&&(cube[3][7]==2)){
                continue;}
            for(j=0;j<3;j++)
                d(cube);
            b(cube);
            d(cube);
            for(j=0;j<3;j++)
                b(cube);
            d(cube);
            for(j=0;j<3;j++)
                r(cube);
            for(j=0;j<3;j++)
                d(cube);
            r(cube);
            printf("green and orange\n");
        }
    }
    return;
}

bool checkMiddle(int** cube){
    int rb = checkCube(cube, 5,1);
    int br = checkCube(cube, 7,3);
    int bo = checkCube(cube, 7,5);
    int ob = checkCube(cube, 5,7);
    int rg= checkCube(cube, 3,1);
    int gr = checkCube(cube, 1,3);
    int ro = checkCube(cube, 1,5);
    int or = checkCube(cube, 3,7);
    if(rb && br && bo && ob && rg && gr && ro && or){
        return true;
    }
    else
        return false;

}

void makeWhiteX(int** cube){
    size_t i,j;       
    while(!checkWhiteCross(cube)){               
        //blue
        for(i=0; i<4; i++){
            if( (cube[5][4]==4) && (cube[6][4]==1)){ //check for inverse side peices
                for(j=0; j<3; j++)
                    f(cube);
                l(cube);
                d(cube);
                for(j=0; j<3; j++)
                    l(cube);
                for(j=0; j<2; j++)
                    f(cube);
                d(cube);
                printf("white x");
                continue;
            }
            else if (!((cube[5][4] ==1)&& (cube[6][4] ==4))){
                for(j=0; j<3; j++)                       //switch edge piece
                    f(cube);
                d(cube);    
                printf("blue\n");
            }
            else{
                //          printCube(cube);
                continue;
            }
        }
        if(cube[4][2]==3 && cube[4][3]==1 && cube[3][4]==1 && cube[2][4]==5 ){ //red and green L
            for(i=0; i<3; i++)
                b(cube);
            d(cube);
            b(cube);
            d(cube);
        }
        //red
        for(i=0; i<4; i++){
            if( (cube[4][2]==1) && (cube[4][3]==3)){ //check for inverse side peices
                for(j=0; j<3; j++)
                    l(cube);
                for(j=0; j<3; j++)
                    b(cube);
                d(cube);
                b(cube);
                for(j=0; j<2; j++)
                    l(cube);
                d(cube);
                continue;
            }
            else if (!((cube[4][2] ==3)&& (cube[4][3] ==1))){
                for(j=0; j<3; j++)
                    l(cube);
                d(cube);    
                printf("red\n");
            }
            else{
                //        printCube(cube);
                continue;
            }
        }
        if(cube[4][5]==1 && cube[4][6]==2 && cube[3][4]==1 && cube[2][4]==5){ //orange and green l
            for(i=0; i<3; i++)
                r(cube);
            d(cube);
            b(cube);
            d(cube);                                
        }
        //green 
        for(j=0; j<4;j++){
            if( (cube[2][4]==1) && (cube[3][4]==5)){ //check for inverse side peices
                b(cube);
                for(i=0; i<3; i++)
                    r(cube);
                d(cube);
                r(cube);
                for(i=0; i<2; i++)
                    b(cube);
                d(cube);
                continue;
            }
            else if (!((cube[3][4] ==1)&& (cube[2][4] ==5))){
                //switch edge piece
                b(cube); 
                d(cube);        
                printf("green\n");
            }
            else{
                //  printCube(cube);
                continue;
            }
        }
        if(cube[4][5]==1 && cube[4][6]==2 && cube[5][4]==1 && cube[6][4]==4){ //orange and blue L
            f(cube);
            d(cube);
            for(i=0; i<3; i++)
                f(cube);
            d(cube);                                
        }
        //orange  
        for(j=0; j<4; j++){
            if( (cube[4][5]==2) && (cube[4][6]==1)){ //check for inverse side peices
                r(cube);
                f(cube);
                d(cube);
                for(i=0; i<3; i++)
                    f(cube);
                for(i=0; i<2; i++)
                    r(cube);
                d(cube);
                continue;
            }
            else if (!((cube[4][5] ==1)&& (cube[4][6] ==2))){
                r(cube);
                d(cube);    
                printf("orange\n");
            }
            else{
                // printCube(cube);
                continue;
            }
        }
        if(cube[4][2]==3 && cube[4][3]==1 && cube[5][4]==1 && cube[6][4]==4){ //blue and red L
            l(cube);
            d(cube);
            for(i=0; i<3; i++)
                l(cube);
            d(cube);                                
        }

    }
    return;
}


bool checkWhiteCross(int** cube){
    int up = checkCube(cube, 3,4);
    int upbelow = checkCube(cube, 2,4);                            
    int down = checkCube(cube, 5,4);
    int downbelow = checkCube(cube, 6,4);
    int right = checkCube(cube, 4,3);
    int rightbelow = checkCube(cube, 4,2);
    int left = checkCube(cube, 4,5);
    int leftbelow = checkCube(cube, 4,6);
    if(up && down && right && left && upbelow && downbelow && rightbelow && leftbelow){
        return true;
    }
    return false;
}

void makeWhiteCornors(int**cube){
    size_t i,j,k;

    while(!checkWhiteCornors(cube)){
        //bottom right
        //   d(cube);
        for(j = 0; j < 3; j++)
            d(cube);
        for(i = 0; i < 3; i++){
            if((cube[5][5]==1) && (cube[6][5]==4) &&(cube[5][6]==2)){
                continue;
            }
            r(cube);
            for(j = 0; j < 3; j++)
                d(cube);
            for(j = 0; j < 3; j++)
                r(cube);
            //     d(cube);
            printf("br chenge\n");
            for(k=0; k < 2; k++){
                if(!((cube[5][5]==1) && (cube[6][5]==4) && (cube[5][6]==2))){
                    r(cube);
                    for(j = 0; j < 3; j++)
                        d(cube);
                    for(j = 0; j < 3; j++)
                        r(cube);
                    d(cube);
                    r(cube);
                    for(j = 0; j < 3; j++)
                        d(cube);
                    for(j = 0; j < 3; j++)
                        r(cube);
                    printf("br orient\n");
                }                                                      
                else{
                    continue;
                }
            }
        }
        //bottom left
        for(i = 0; i < 3; i++){
            if((cube[5][3]==1) && (cube[6][3]==4) && (cube[5][2]==3)){
                continue;
            }
            for(j = 0; j < 3; j++)
                f(cube);
            for(j = 0; j < 3; j++)
                d(cube);
            f(cube);         
            //   d(cube);
            printf("fl chenge\n");

            for(k=0; k < 2; k++){
                if(!((cube[5][3]==1) && (cube[6][3]==4) && (cube[5][2]==3))){
                    for(j = 0; j < 3; j++)
                        f(cube);
                    for(j = 0; j < 3; j++)
                        d(cube);
                    f(cube);
                    d(cube);
                    for(j = 0; j < 3; j++)
                        f(cube);
                    for(j = 0; j < 3; j++)
                        d(cube);
                    f(cube);

                    printf("fl orient\n");

                }
                else{
                    continue;
                }
            }

        }
        //back left  
        for(i = 0; i < 3; i++){
            if((cube[3][3]==1) && (cube[2][3]==5) && (cube[3][2]==3)){
                continue;                          
            }
            for(j = 0; j < 3; j++)
                l(cube);
            for(j = 0; j < 3; j++)
                d(cube);
            l(cube);           
            printf("bl orient\n");
            // d(cube);
            for(k=0; k < 2; k++){
                if(!((cube[3][3]==1) && (cube[2][3]==5) && (cube[3][2]==3))){
                    for(j = 0; j < 3; j++)
                        l(cube);
                    for(j = 0; j < 3; j++)
                        d(cube);
                    l(cube);
                    d(cube);
                    for(j = 0; j < 3; j++)
                        l(cube);
                    for(j = 0; j < 3; j++)
                        d(cube);
                    l(cube);
                    printf("bl orient\n");
                }
                else{
                    continue;
                }
            }
        }

        //back right
        for(i = 0; i < 3; i++){
            if((cube[3][5]==1) && (cube[2][5]==5) && (cube[3][6]==2)){
                continue;
            }
            b(cube);
            for(j = 0; j < 3; j++)
                d(cube);
            for(j = 0; j < 3; j++)
                b(cube);
            //  d(cube);
            //switched cornor    
            printf("back right switched cornor\n");
            for(k=0; k < 2; k++){
                if(!((cube[3][5]==1) && (cube[2][5]==5) && (cube[3][6]==2))){
                    b(cube);
                    for(j = 0; j < 3; j++)
                        d(cube);
                    for(j = 0; j < 3; j++)
                        b(cube);
                    d(cube);
                    b(cube);
                    for(j = 0; j < 3; j++)
                        d(cube);
                    for(j = 0; j < 3; j++)
                        b(cube);
                    //switched orientation        
                    printf("back right switched orientation\n");
                }
                else{
                    continue;
                }
            }
        }
    }
    return;
}

bool checkWhiteCornors(int** cube){
    int r = checkCube(cube,5,5);
    int rb= checkCube(cube, 6,5);
    int l = checkCube(cube, 5,3);
    int lb = checkCube(cube, 6,3);
    int bl = checkCube(cube, 3,3);
    int blb = checkCube(cube, 2,3);
    int br = checkCube(cube, 3,5);
    int brb = checkCube(cube, 2,5);
    int a = checkCube(cube, 5,6);
    int b = checkCube(cube, 5,2);
    int c = checkCube(cube, 3,2);
    int d = checkCube(cube, 3,6);
    if(r && rb && l && lb &&  bl && blb && br && brb && a && b && c && d){
        return true;
    }
    return false;
}

bool checkCube(int** cube, int row, int col){  //TODO verify this func works
    int** checker = makeCube();
    fillStdCube(checker);
    int checkerColor = checker[row][col];
    int cubeColor = cube[row][col];
    if(checkerColor == cubeColor){
        return true;
    }
    else{
        return false;
    }
}

void printCube(int** cube){
    for(size_t r = 0; r < 9; r++){
        for(size_t c = 0; c <12; c++){
            if(cube[r][c] == 0){
                printf("__");
            }
            else{
                printf("%d,", cube[r][c]);
            }
        }
        puts("");
    }
    puts(" ");
}

void swap(int** cube, int r1, int c1, int r2, int c2){
    int tmp = cube[r1][c1];
    cube[r1][c1] = cube[r2][c2];
    cube[r2][c2] = tmp;
}

//"up" - top layer twisted clock-wise
void u(int** cube){
    swap(cube, 3,4,4,5);
    swap(cube, 3,4,5,4);
    swap(cube, 3,4,4,3);
    swap(cube, 3,3,3,5);
    swap(cube, 3,3,5,5);
    swap(cube, 3,3,5,3);
    swap(cube, 2,4,4,6);
    swap(cube, 2,4,6,4);
    swap(cube, 2,4,4,2);
    swap(cube, 2,3,3,6);
    swap(cube, 2,3,6,5);
    swap(cube, 2,3,5,2);
    swap(cube, 2,5,5,6);
    swap(cube, 2,5,6,3);
    swap(cube, 2,5,3,2);
    printf("Step: U\n");
}

//"down" - botton layer twisted counter clock-wise
void d(int** cube){
    swap(cube,3,10,4,11);
    swap(cube,3,10,5,10);
    swap(cube,3,10,4,9);
    swap(cube,3,9,3,11);
    swap(cube,3,9,5,11);
    swap(cube,3,9,5,9);
    swap(cube,0,5,3,0);
    swap(cube,0,5,8,3);
    swap(cube,0,5,5,8);
    swap(cube,0,4,4,0);
    swap(cube,0,4,8,4);
    swap(cube,0,4,4,8);
    swap(cube,0,3,5,0);
    swap(cube,0,3,8,5);
    swap(cube,0,3,3,8);
    printf("Step: D\n");
}

//"right" - turn right side towards you
void r(int** cube){
    swap(cube, 3,7,4,6);
    swap(cube, 3,7,5,7);
    swap(cube, 3,7,4,8);
    swap(cube, 3,8,3,6);
    swap(cube, 3,8,5,6);
    swap(cube, 3,8,5,8);
    swap(cube, 0,5,3,5);
    swap(cube, 0,5,6,5);
    swap(cube, 0,5,5,9);
    swap(cube, 1,5,4,5);
    swap(cube, 1,5,7,5);
    swap(cube, 1,5,4,9);
    swap(cube, 2,5,5,5);
    swap(cube, 2,5,8,5);
    swap(cube, 2,5,3,9);
    printf("Step: R\n");
}

//"left" - turn left side towards you    
void l(int** cube){
    swap(cube, 3,1,4,2);
    swap(cube, 3,1,5,1);
    swap(cube, 3,1,4,0);
    swap(cube, 3,0,3,2);
    swap(cube, 3,0,5,2);
    swap(cube, 3,0,5,0);
    swap(cube, 0,3,3,3);
    swap(cube, 0,3,6,3);
    swap(cube, 0,3,5,11);
    swap(cube, 1,3,4,3);
    swap(cube, 1,3,7,3);
    swap(cube, 1,3,4,11);
    swap(cube, 2,3,5,3);
    swap(cube, 2,3,8,3);
    swap(cube, 2,3,3,11);
    printf("Step: L\n");
}

//"front" - twist front face clockwise
void f(int** cube){
    swap(cube,6,4,7,5);
    swap(cube,6,4,8,4);
    swap(cube,6,4,7,3);

    swap(cube,5,4,5,7);
    swap(cube,5,4,5,10);
    swap(cube,5,4,5,1);

    swap(cube,6,3,6,5);
    swap(cube,6,3,8,5);
    swap(cube,6,3,8,3);

    swap(cube,5,5,5,8);
    swap(cube,5,5,5,11);
    swap(cube,5,5,5,2);

    swap(cube,5,3,5,6);
    swap(cube,5,3,5,9);
    swap(cube,5,3,5,0);
    printf("Step: F\n");
}

//"back" - twist back face clockwise -relative to the human's perception of clockwise
void b(int** cube){
    swap(cube, 2,4,1,5);
    swap(cube, 2,4,0,4);
    swap(cube, 2,4,1,3);
    swap(cube, 2,3,2,5);
    swap(cube, 2,3,0,5);
    swap(cube, 2,3,0,3);
    swap(cube, 3,3,3,6);
    swap(cube, 3,3,3,9);
    swap(cube, 3,3,3,0);
    swap(cube, 3,4,3,7);
    swap(cube, 3,4,3,10);
    swap(cube, 3,4,3,1);
    swap(cube, 3,5,3,8);
    swap(cube, 3,5,3,11);
    swap(cube, 3,5,3,2);
    printf("Step: B\n");
}
