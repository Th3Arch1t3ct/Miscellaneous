#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

void heapify(int arr[], int aSize, int i){
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < aSize && arr[left] > arr[largest]){
        largest = left;
    }
    if(right < aSize && arr[right] > arr[largest]){
        largest = right;
    }

    if(largest != i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, aSize, largest);
    }

}

void heapSort(int arr[], int aSize){
    // Start at last element
    for(int i = aSize / 2 - 1; i >= 0; i--){
        heapify(arr, aSize, i);
    }

    for(int i = aSize - 1; i >= 0; i--){
        swap(&arr[0], &arr[i]);

        heapify(arr, i, 0);
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
    heapSort(arr, aSize);
    printArray(arr, aSize);

    return EXIT_SUCCESS;
}