#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define SIZE 30

//Class algorithms for sorting
//later, sort using both meathods mentioned on wikapedia
//

//for lobuto pivot should be a median of three value, and u should place that median at end of array
//for hore pivot should still be a midian of three value, and u should place that median in the middle of array - see wiki "choice of pivot" snippet for pointer

size_t lomuto_partition(int *arr, int l, int h);
void quickSort_lomuto(int *arr, int l, int h);
int medianOfthree(int *arr, int l, int h);
void print(int *arr);

int main(void){
    int arr[SIZE];
    for(size_t i = 0; i < SIZE; ++i){
        arr[i] = rand() % SIZE + 1;
        }  
    printf("Unsorded array: \n");
    print(arr);
    quickSort_lomuto(arr, 0, SIZE-1);
    printf("sorded array: \n");
    print(arr);
    return 0;
}

void print(int *arr){
    for(size_t i = 0; i < SIZE; ++i){ //prints arr
        printf("|%d|", arr[i]);
        }
    puts(" ");
    
    }

void quickSort_lomuto(int *arr, int l, int h){
    if(l<h){
       size_t p =lomuto_partition(arr, l, h);
//       printf("partition index: %zu, arr[p]: %zu\n", p, arr[p]);
  //     print(arr);
       quickSort_lomuto(arr, l, p-1);
       quickSort_lomuto(arr, p+1, h);
    }
}

size_t lomuto_partition(int *arr, int l, int h){
    int pivot_index = medianOfthree(arr, l, h);
    int first_tmp = arr[h];
    arr[h] = arr[pivot_index];
    arr[pivot_index] = first_tmp;
  
    
    int i = l-1;
    for(int j = l; j<(h); j++){
        if(arr[j] <= arr[h]){
            i++;
            int tmp = arr[j];
            arr[j] = arr[i];
            arr[i] = tmp;
        }
    }
    int tmp = arr[h];
    arr[h] = arr[i+1];
    arr[i+1] = tmp;
    return i+1;
}

int medianOfthree(int *arr, int l, int h){     //return indexes
    int first  = arr[l];
    int m = (l+ h)/2;
    int middle = arr[m];
    int last = arr[h];
    if (((first >= last) && (first <= middle)) || ((first <= last) && (first >= middle))){
        return l;
    } 

    else if(((last >= first) && (last <= middle)) || ((last <= first) && (last >= middle))){
        return (h);
    }

    else{
        return m;
    }
}
