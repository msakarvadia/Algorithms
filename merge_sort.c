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
    int arr[3] = {5, 10, 3};
    merge_sort(arr, 0, 2);
    print_arr(arr, 3);
    return 0;
}

void merge_sort(int arr[], int l, int r){
    if(l<r){
        int m = l + (r-1)/2; //middle index
        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        merge(arr, l, m, r);
        }
    }

void merge(int* arr, int l, int m, int r){
    int first[m];
    int second[r-m];

    for(int i = 0; i < m; i++){
        first[i] = arr[l+i];
    }
    for(int j = 0; j < (r-m); j++){
        second[j] = arr[m+1 + j];
    } 

    int i = 0;
    int j = 0;
    int k = l;
    while(i < m && j < (r-m)){
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
    while(i < m){
        arr[k] = first[i];
        i++;
        k++;
    }
    while(j < (r-m)){
        arr[k] = second[j];
        j++;
        k++;
    }
}

void print_arr(int * arr, int r){
    for(int i = 0; i <r; i++){
        printf("|%d|", arr[i]);
        }
    puts(" ");
    }
