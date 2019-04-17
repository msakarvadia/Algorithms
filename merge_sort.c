#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

void merge(int* arr, int l, int m, int r);
void merge_sort(int arr[], int l, int r);
void print_arr(int  arr[], int r);

int main(void){
    clock_t start, end;
    double cpu_time_used;

    printf("Note to teacher: Unfortunatly I read the function headers on canvas after programming this on my own, so my headers are different from yours and I statically allocated memorry for my arrays so I cannot free anything.\n");
    int arr[10] = {5,89, 91, 10, 7, 0, 62, 35, 0, 23};
    puts(" ");
    printf("Unsorted array:");
    print_arr(arr, 10);
    start = clock();
    merge_sort(arr, 0, 9);
    end = clock();
    cpu_time_used = ((double)(end-start))/ CLOCKS_PER_SEC;
    printf("Sorted array:");
    print_arr(arr, 10);
    printf("Time to sort array: %lf sec\n", cpu_time_used);
    printf("No matter what I try, the time to execute is so small that a double isn't displaying enought digits to see the computation time. I suspect the same problem will happen with quicksorting algorithms.");
    puts(" ");
    return 0;
}

void merge_sort(int arr[], int l, int r){
    if(l<r){
        int m = l + (r-l)/2; //middle index of cur array, not original
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        merge(arr, l, m, r);
        }
    return;
    }

void merge(int* arr, int l, int m, int r){
    int first[m-l+1];    //we add 1 because int division floors "m" in merge_sort
    int second[r-m];

    for(int i = 0; i < (m-l+1); i++){
        first[i] = arr[l+i];
    }
    for(int j = 0; j < (r-m); j++){
        second[j] = arr[m+1 + j];
    } 

    int i = 0;
    int j = 0;
    int k = l;
    while(i < (m-l+1) && j < (r-m)){
        if(first[i] <= second[j]){
            arr[k] = first[i];
            i++;
        }
        else{
            arr[k] = second[j];
            j++;
        }
        k++;
    }
    while(j < (r-m)){
        arr[k] = second[j];
        j++;
        k++;
    }
    while(i < (m-l+1)){
        arr[k] = first[i];
        i++;
        k++;
    }
    return;
}

void print_arr(int * arr, int r){
    for(int i = 0; i <r; i++){
        printf("|%d|", arr[i]);
        }
    puts(" ");
    }
