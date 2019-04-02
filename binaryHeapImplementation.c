#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


//binary heap w/ kleiner

typedef struct binaryHeap{
    int *array;
    size_t tail;
    size_t capacity;
}BinaryHeap;

void push(BinaryHeap *BH, char val);
int pop(BinaryHeap *BH);
void print(BinaryHeap *BH);
void resizeIfFull(BinaryHeap *BH);
size_t parent(size_t c);
size_t leftChild(size_t p);
size_t rightChild(size_t p);
size_t largestChild(BinaryHeap *BH, size_t p);
void bubble(BinaryHeap *BH, size_t index);
void sift(BinaryHeap *BH, size_t index);
BinaryHeap *createBH();
void destroy(BinaryHeap *BH);

int main(void){
    BinaryHeap *bh= createBH();
    for(char c = 'a'; c<= 'z'; ++c){
        push(bh, c);
    }
    for(size_t i = 0; i<5; ++i){
        printf("%c\n", pop(bh));
    }
    print(bh);
    destroy(bh);

    return 0;
}

BinaryHeap *createBH(){
    BinaryHeap *out = malloc(sizeof(BinaryHeap));
    out->tail = 0;
    out->capacity = 8;
    out->array = malloc(sizeof(char)*out->capacity);
    return;
}

void destroy(BinaryHeap *BH){
    free(BH->array);
    free(BH);
}



size_t parent(size_t c){
    return (c-1)/2;
}

size_t leftChild(size_t p){
    return (2*p)+1;
}

size_t rigtChild(size_t p){
    return (2*p)+2;
}

void bubble(BinaryHeap *BH, size_t index){
    size_t p = parent(index);
    char tmp=  BH->array[index];
    if(index==0 || BH->array[index] <= BH->array[parent(p)]){
        return;
    }
    BH->array[index] = BH->array[p];
    BH->array[p] = tmp;
    bubble(BH, p);
}


void print(BinaryHeap *BH){
    //want to print it out based on highest not printing first, then consecutive rows of values from subsequent levels
    //i is the level
    //index is which index of the arraylist to print
    //j is how many letters to print in each level
    for(size_t i = 0, index = 0; i < BH->tail; ++i){
        for(size_t s = 0; s< index; ++s){
            printf(" ");
        }
        for(size_t j = 0; j< (size_t) pow(2,i) && index < BH->tail; ++j, ++index){
            printf("%c", BH->array[index]);
        }
        puts("");
    }

}

void push(BinaryHeap *BH, char val){
    resizeIfFull(BH);
    BH->array[(BH->tail)++]=val;
    bubble(BH, (BH->tail)++);
}

int pop(BinaryHeap *BH){
    int out = BH->array[0];
    BH->array[0]=BH->array[--BH->tail];
    sift(BH, 0);
    return out;
    }

void resizeIfFull(BinaryHeap *BH){
    if(BH->capacity == BH->tail){
        BH->capacity*=2;
        BH->array = realloc(BH->array,BH->capacity*sizeof(char));
    }
}

size_t largestChild(BinaryHeap *BH, size_t p){
    size_t left = leftChild(p); //returns index
    size_t right = rightChild(p);
    if(right<BH->tail){
        return BH->array[right] > BH->array[left] ? right:left;
        }
    if(left<BH->tail){
        return left;
        }
    return p;
    }

void sift(BinaryHeap *BH, size_t index){
    size_t largestChild = largestChild(BH, p);
    char tmp = BH->array[largestChild];
    if(BH->array[index]>=tmp){
        return;
        }
    BH->array[largestChild] = BH->array[index];
    //BH->array[index]->tmp; //this line has a problem
    BH->array[index] = tmp;
    sift(BH, largestChild);
    }
