#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int aSize){
    int i, key, j;
    for(i = 1; i < aSize; i++){
        key = arr[i];
        j = i-1;

        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

void printArray(int arr[], int aSize)
{
    for(int i =0; i < aSize; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int arr[8] = {4,3,2,10,12,1,5,6};
    int aSize = (sizeof(arr)/sizeof(arr[0]));

    printArray(arr, aSize);
    insertionSort(arr, aSize);
    printArray(arr, aSize);

    return EXIT_SUCCESS;
}