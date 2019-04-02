#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define INIT_CAPACITY 8
#define INIT_SIZE 

typedef struct node{
    size_t priority;
    int val;
}Node;

typedef struct arrayList {
    size_t capacity;
    size_t size;
    Node* *data;
}PQ;


PQ* create(void);
void insert(PQ* pqPtr, Node* n, size_t index);
bool remoove(PQ* pqPtr, int val);//deletes first instidance of val
bool delete(PQ* pqPtr, size_t index);
void print(PQ* pqPtr);
int get(PQ* pqPtr, size_t index);
size_t find(PQ* pqPtr, int val);  //first instance
bool isEmpty(PQ* pqPtr);
void resizeIfNeeded(PQ* pqPtr);
size_t binarySearch(Node* data, size_t size, int val);
int pop(PQ *pqPtr);
void push(PQ *pqPtr, int val, size_t priority);
void shiftByOne(PQ* pqPtr, size_t index);
void clear(PQ* pqPtr);   

int main(void){
    PQ* ptr = create();

    while (true) {
        int v=-1;
        size_t p=0;
        char cmd='x';
        printf("insert command (e = exit, c= clear, p = push, o = pop): e,c,p,o\n");
        cmd=getchar();
        if (cmd == 'x'){
            continue; 
        }
        else if(cmd =='e'){
            return 0;
        }
        else if (cmd == 'c') {
            clear(ptr);
        }
        else if (cmd == 'o'){
            pop(ptr);
        }
        else if (cmd == 'p'){
            printf("Insert value and its priority (greater than 0) with comma in middle: 1,3 (value:1 priority:3)\n");
            scanf("%d,%lu", &v, &p);
            if(v==-1 ||  p==0){
                printf("Please enter valid data\n");
                continue;
            }
            printf("Inserting %d,%lu \n",v,p);
            push(ptr, v, p);
        }
        print(ptr);
    }
    return 0;
}

void clear(PQ* pqPtr){
    for(unsigned int i = 0; i < pqPtr->size; ++i){
        free(pqPtr->data[i]);
    }
    pqPtr->size = 0;
    return;    
}   

int pop(PQ *pqPtr){
    Node * tmp = pqPtr->data[0];
    pqPtr->size--;
    for(unsigned int i = 0;i<=pqPtr->size; ++i){
        pqPtr->data[i] = pqPtr->data[i+1];
    }

    return tmp->val;
}

void shiftByOne(PQ* pqPtr, size_t index){
    resizeIfNeeded(pqPtr);
    for(unsigned int i = pqPtr->size; i > index; --i){
        pqPtr->data[i] = pqPtr->data[i-1];
    }
}

void push(PQ *pqPtr, int val, size_t priority){
    Node* tmp = malloc(sizeof(Node*));
    tmp->val = val;
    tmp->priority = priority;
    //if PQ is empty
    if(pqPtr->size == 0){
        pqPtr->data[pqPtr->size] = tmp;
        pqPtr->size++;
        return;
    }
    //simple case where priority was the lowest value of the array list
    if(pqPtr->data[pqPtr->size-1]->priority > priority){
        pqPtr->data[pqPtr->size] = tmp;
        pqPtr->size++;
        return;
    }
    //simple case where node has highest priority
    if(pqPtr->data[0]->priority< priority){
        shiftByOne(pqPtr, 0);
        pqPtr->data[0] = tmp;
        pqPtr->size++;
        return;
    }
    //Complex case where we need to insert it in middle based on priority
    for(unsigned int i =pqPtr->size; i>0; --i){
        if(pqPtr->data[i-1]->priority>=priority){
            shiftByOne(pqPtr, i);
            pqPtr->data[i] = tmp;
            pqPtr->size++;
            break;
        }
    }
}

PQ* create(void){
    PQ* new = malloc(sizeof(PQ));
    new->capacity = INIT_CAPACITY;
    new->size = 0;
    new->data = calloc(INIT_CAPACITY, sizeof(Node*));
    return new;
}

void print(PQ* pqPtr){
    //if(isEmpty(pqPtr)){
    //  return;
    //}
    printf("--This is the fully printed PQ--\n");
    for(size_t i = 0; i < pqPtr->size; ++i){
        Node * tmp=pqPtr->data[i];
        printf("value:%d, Priority:%lu \n", tmp->val, tmp->priority);
    }
}



void resizeIfNeeded(PQ* pqPtr){
    if(pqPtr->size == pqPtr->capacity){
        pqPtr->capacity *= 2;
        pqPtr->data = realloc(pqPtr->data, pqPtr->capacity*sizeof(Node*));
    }
    return;
}

bool isEmpty(PQ* pqPtr){
    return pqPtr == NULL || pqPtr->size == 0;
}

int get(PQ* pqPtr, size_t index){
    if(pqPtr->size <= index){
        fprintf(stderr,"Index out of bounds\n" );
        return 0; 
    }
    Node* tmp = pqPtr->data[index];
    return tmp->val;
}

size_t find(PQ* pqPtr, int val){
    for(size_t i = 0; i<pqPtr->size; ++i){
        if(pqPtr->data[i]->val==val){
            return i;
        }

    }
    fprintf(stderr, "Value %d not found\n", val);
    return (size_t)-1;
}

bool remoove(PQ* pqPtr, int val){
    size_t index = find(pqPtr, val);
    return delete(pqPtr, index);
}

bool delete(PQ* pqPtr, size_t index){
    if(index >=pqPtr->size){
        return false;
    }
    for (size_t i = index; i < pqPtr->size-1; ++i){
        pqPtr->data[i] = pqPtr->data[i+1];
    }
    pqPtr->size--;
    return true;
}
