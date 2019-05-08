#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr[], int aSize){
    bool sorted = false;
    while(!sorted){
        for(int i = 0; i < aSize; i++){
            if(arr[i] > arr[i+1]){
                //Swap them
                arr[i] += arr[i+1];
                arr[i+1] = arr[i] - arr[i+1];
                arr[i] = arr[i] - arr[i+1];
                break;
            }
            sorted = true;
        }

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
    bubbleSort(arr, aSize);
    printArray(arr, aSize);

    return EXIT_SUCCESS;
}