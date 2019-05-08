#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int middle, int right){
    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    int Left[leftSize], Right[rightSize];

    for(int i = 0; i < leftSize; i++){
        Left[i] = arr[left + i];
    }
    for(int i = 0; i < rightSize; i++){
        Right[i] = arr[middle + 1 + i];
    }
    int i = 0;
    int j = 0;
    int k = left; // initial index of merged subarray
    while(i < leftSize && j < rightSize){
        if(Left[i] <= Right[j]){
            arr[k] = Left[i];
            i++;
        } else {
            arr[k] = Right[j];
            j++;
        }
        k++;
    }

    while(i < leftSize){
        arr[k] = Left[i];
        i++;
        k++;
    }

    while(j < rightSize){
        arr[k] = Right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right){
    // Split in half
    if (left < right){
        int middle  = left + (right - left) / 2;

        // mergeSort left
        mergeSort(
            arr, left, middle);

        //mergeSort right
        mergeSort(arr, middle+1, right);

        // merge
        merge(arr, left, middle, right);
    }
}

void printArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(){
    int arr[7] = {38, 27, 43, 3, 9, 82, 10};
    int aSize = (sizeof(arr)/sizeof(arr[0]));

    printArray(arr, aSize);

    mergeSort(arr, 0, aSize - 1);

    printArray(arr, aSize);

    return EXIT_SUCCESS;
}