#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


typedef struct node{
    size_t priority;
    char value;
}Node;

typedef struct binaryHeap{
    Node* *array;
    size_t tail;
    size_t capacity;
}BinaryHeap;

void push(BinaryHeap *BH, Node* n);
char pop(BinaryHeap *BH);
void print(BinaryHeap *BH);
void resizeIfFull(BinaryHeap *BH);
size_t parent(BinaryHeap* BH, size_t c);
size_t leftChild(size_t p);
size_t rightChild(size_t p);
size_t largestChild(BinaryHeap *BH, size_t p);
void bubble(BinaryHeap *BH, size_t index);
void sift(BinaryHeap *BH, size_t index);
BinaryHeap *createBH();
void destroy(BinaryHeap *BH);

int main(void){
    BinaryHeap *bh= createBH();
    while (true) {
        char v='M';
        size_t p=0;
        char cmd='x';
        printf("insert command (e = exit, d= destroy, p = push, o = pop): e,c,p,o\n");
        cmd=getchar();
        if (cmd == 'x'){
            continue; 
        }
        else if(cmd =='e'){
            return 0;
        }
        else if (cmd == 'd') {
            destroy(bh);
        }
        else if (cmd == 'o'){
            pop(bh);
        }
        else if (cmd == 'p'){
            printf("enter the charecter value(DO NOT ENTER CAPTIAL LETTERS, ONLY LOWERCASE)\n");
            scanf(" %c",&v);
            printf("Enter the priority (int value)\n");
            scanf("%lu", &p);
            if(v=='M'||p==0){
                printf("Please enter valid data\n");
                continue;
            }
            printf("Inserting %c,%lu \n",v,p);
            Node* n = malloc(sizeof(Node));
            n->value = v;
            n->priority = p;
            push(bh, n);
        }
        print(bh);
    }
    return 0;
}


BinaryHeap *createBH(){
    BinaryHeap *out = malloc(sizeof(BinaryHeap));
    out->tail = 0;
    out->capacity = 8;
    out->array = malloc(sizeof(Node*)*out->capacity);
    return out;
}

size_t parent(BinaryHeap *BH,size_t c){
    if(BH->tail == 0){
        return 0;
        }
    return (c-1)/2;
}

size_t leftChild(size_t p){
    return (2*p)+1;
}

size_t rightChild(size_t p){
    return (2*p)+2;
}

void bubble(BinaryHeap *BH, size_t index){
    size_t p = parent(BH, index);
    if((index==0)){
        return;
    }
    printf("parent index: %d", p);
    size_t priority = BH->array[index]->priority;
    printf("parent priority: %d\n", BH->array[p]->priority);
    if(priority <= BH->array[p]->priority){
        return;
    }
    Node* tmp=  BH->array[p];
    BH->array[p] = BH->array[index];
    BH->array[index] = tmp;
    bubble(BH, p);
}

void push(BinaryHeap *BH, Node* n){
    resizeIfFull(BH);
    BH->array[(BH->tail)]=n;
    bubble(BH, (BH->tail));
    BH->tail++;
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
            printf("(%c,%lu) ", BH->array[index]->value, BH->array[index]->priority);
        } 
        puts("");
    }     
/*    for(size_t i = 0; i <BH->tail; i++){
       printf("(%c,%lu) \n", BH->array[i]->value, BH->array[i]->priority);
        
        }*/

}



void resizeIfFull(BinaryHeap *BH){
    if(BH->capacity == BH->tail){
        BH->capacity*=2;
        BH->array = realloc(BH->array,BH->capacity*sizeof(Node*));
    }
}

size_t largestChild(BinaryHeap *BH, size_t p){
    size_t left = leftChild(p); //returns index
    size_t right = rightChild(p);
    if(right < BH->tail){
        return BH->array[right]->priority > BH->array[left]->priority ? right:left;
        }
    if(left < BH->tail){
        return left;
        }
    return p;
    }

char pop(BinaryHeap *BH){
    Node* out = BH->array[0];
    BH->array[0]=BH->array[BH->tail-1];
    BH->tail--;
    sift(BH, 0);
    return out->value;
    }

void sift(BinaryHeap *BH, size_t index){
    size_t LC = largestChild(BH, index);
    Node* tmp = BH->array[LC];
    printf("LC=%lu, priority: %d, value:%c \n", LC, tmp->priority, tmp->value);
    printf("index=%lu, value:%c, priority: %d\n", index, BH->array[index]->value, BH->array[index]->priority);
    if((BH->array[index]->priority)>=(tmp->priority)){
        return;
        }
    BH->array[LC] = BH->array[index];
    //BH->array[index]->tmp; //this line has a problem
    BH->array[index] = tmp;
    sift(BH, LC);
    }


void destroy(BinaryHeap *BH){
    for(size_t i = 0; i < BH->tail; i++){
        free(BH->array[i]);
        }
    BH->tail = 0;
    }
