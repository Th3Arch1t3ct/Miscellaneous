#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// How do you find the missing number in a given integer array of 1 to 100?

int main(int argc, char* argv[]){
    int i, missing_value, missing;
    int sum = 0;
    int test_sum = 0;

    int somearray[100];

    srand(time(0));

    // populate array with random numbers
    missing = rand() % 100 + 1;
    for (i = 0; i < sizeof(somearray)/sizeof(int); i++){
        if (i >= missing){
            somearray[i] = i+1;
        } else {
            somearray[i] = i;
        }
    }

    // Get sum of all numbers 0 to 100
    for(i = 0; i < 101; i++){
        sum += i;
    }

    // Get sum of all given numbers
    for(i = 0; i < sizeof(somearray)/sizeof(int); i++){
        printf("%d, ", somearray[i]);
        test_sum += somearray[i];
    }

    // calculate missing number
    missing_value = sum - test_sum;

    printf("The missing value is: %d\n", missing_value);

    return 0;
}