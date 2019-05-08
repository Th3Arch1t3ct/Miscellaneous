#include <stdio.h>
#include <stdlib.h>
#include <climits>

void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

class Heap{
    // This implements a min heap
private:
    int *heapArr;
    int capacity;
    int curHeapSize;
public:
    Heap(int capacity);

    void heapify(int);
    int extractMin();
    void decreaseKey(int i, int new_val);
    void deleteKey(int i);
    void insertKey(int k);

    int parent(int i){ return (i - 1) / 2; }
    int left(int i){ return 2 * i + 1; }
    int right(int i){ return 2 * i + 2; }
    int getMin() { return heapArr[0]; }

};

Heap::Heap(int capacity){
    this->curHeapSize = 0;
    this->capacity = capacity;
    this->heapArr = new int[this->capacity];
}

void Heap::heapify(int i){
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if(l < curHeapSize && heapArr[l] < heapArr[i]){
        smallest = l;
    }
    if ( r < curHeapSize && heapArr[r] < heapArr[smallest]){
        smallest = r;
    }
    if(smallest != i){
        swap(&heapArr[i], &heapArr[smallest]);
        heapify(smallest);
    }

}

int  Heap::extractMin(){
    if(curHeapSize <= 0){
        return INT_MAX;
    }
    if(curHeapSize == 1){
        curHeapSize--;
        return heapArr[0];
    }

    // store mine and remove from heap
    int root = heapArr[0];
    heapArr[0] = heapArr[curHeapSize-1];
    curHeapSize--;
    heapify(0);

    return root;
}

void Heap::decreaseKey(int i, int new_val){
    if(new_val > heapArr[i]){
        // number is not decreasing
        return;
    }

    heapArr[i] = new_val;
    while(i != 0 && heapArr[parent(i)] > heapArr[i]){
        swap(&heapArr[parent(i)], &heapArr[i]);
        i = parent(i); // This moves UP the tree
    }
}

void Heap::deleteKey(int i){
    // set node to minimum
    decreaseKey(i, INT_MIN);
    extractMin();
}

void Heap::insertKey(int k){
    if(curHeapSize == capacity){
        printf("Capacity has been reached");
        return;
    }

    curHeapSize++;
    int i = curHeapSize - 1; // Index to insert at
    heapArr[i] = k;

    // Fix heap property if violated
    // If we are root node or if parent is greater than current node
    while(i != 0 && heapArr[parent(i)] > heapArr[i]){
        // Do the swap between parent and i
        swap(&heapArr[i], &heapArr[parent(i)]);
        i = parent(i);
    }
}


void heapify(){

}

void heapSort(int arr[], int aSize){

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