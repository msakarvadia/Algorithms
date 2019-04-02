#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

//friday assignment is using arraylist using order or priority low ---> high (thing that was added first with the higher priority closer to the head so that it will be poped before another node with the same priority added after)
    //no limit on the number of priorities
    //priroty is stored as an unsigned int
//notes for PQ:
size_t parent(size_t i);
size_t leftChild(size_t i);
size_t rightChild(size_t i);
void clear(PriorityQueue*); 
void sift(PriorityQueue*, size_t i);
    //sorts out ur heap
void bubble(PriorityQueue*, size_t i);
    //add random element to bottom and puts in the right place 
int pop(PriorityQueue*);
    //pop the first element, replace with last element (reorder - rmember u are using a heap)
    //dont delete the last element, just change the tail pointer
    //use sift meathod
size_t largestChild(PriorityQueue*, size_t i); //two children could be same (wont matter which one u pop), or there might be only 1 child; test left child to see if there are children in a row (vison a binary tree/heep)
    //only called if left child exsists
void push(PriorityQueue*, int value, unsigned int priority);
    //use bubble
    //element starts at the end of array (left most child), the number gets bubbled up until its the root, or is smaller than its parent

typedef struct priorityQueue{
    size_t capacity;
    size_t tail;  //size is how many elements are in the queue, points to the last element which is called tail
    Node* array; //array of nodes; dont need to go through and deallocate each node; to clear the PQ, just free the entire array
    }PriorityQueue;


typedef struct node{
    int value;
    unsigned int priority;
    }Node;

int main(void){
}

int pop(PriorityQueue*){
    out = PriorityQueue -> array[0];
    //might want helper meathod called largest child
    }

void push(PriorityQueue*, int value, unsigned int priority){
    arr[tail].value = value;
    arr[tail++].priorit = priority;
}
