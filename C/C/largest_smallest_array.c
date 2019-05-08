#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAYSIZE 100

// How do you find the largest and smallest number in an unsorted integer array?


int main(int argc, char* argv[]){
    int i;
    int largest = 0;
    int smallest = 0;

    int somearray[ARRAYSIZE];

    srand(time(0));

    // populate array with random numbers
    for (i = 0; i < ARRAYSIZE; i++){
        somearray[i] = rand() % 1000 + 1;
    }

    for( i = 0; i < ARRAYSIZE; i++){
        if(smallest > somearray[i]){
            smallest = somearray[i];
        }
        if(largest < somearray[i]){
            largest = somearray[i];
        }
    }

    printf("The largest value in the array is: %d\n", largest);
    printf("The smallest value in the array is: %d\n", smallest);
    return 0;
}