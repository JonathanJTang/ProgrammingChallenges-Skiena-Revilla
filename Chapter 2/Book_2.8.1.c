/**UVa Online Judge ID 10038: Jolly Jumpers
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>

int acquireInputV2(int * sequence){
    int i;
    int index = 0;  /*index for array sequence*/
    int j = 0;  /*index for building array tempString*/
    int inputC;
    int numItems;

    if(scanf(" %d",&numItems) != EOF){
        for(i = 0; i < numItems; i++){
            scanf(" %d",&(sequence[i]));
        }
        return numItems;
    }
    return -1;  /*reached end of input*/
}


int main()
{
    int i, diff, numIntegers;
    int isJolly = 1;  /*Assume sequence is jolly unless otherwise*/
    int sequence[3000];
    int diffs[3000];  /*will be accessed with indices from 1 to n-1*/
    for(i = 0; i < 3000; i++){  /*Initialize diffs to 0*/
        diffs[i] = 0;
    }

    numIntegers = acquireInputV2(sequence);
    while(numIntegers != -1){
        /*Calculate differences between adjacent integers in the sequence*/
        for(i = 0; i < numIntegers-1; i++){
            diff = abs(sequence[i+1] - sequence[i]);
            if(diff <= numIntegers-1){
                diffs[diff] = 1;
            }
            else{  /*for jolly jumpers, the absolute difference between any two items cannot be greater than n-1*/
                isJolly = 0;
                break;
            }
        }

        if(isJolly == 1){  /*if isJolly is still assumed to be true at this point*/
            for(i = 1; i <= numIntegers-1; i++){
                /*if a diff in the sequence of integers from 1 to n-1 is missing, then the sequence cannot be jolly*/
                if(diffs[i] == 0){
                    isJolly = 0;
                    break;
                }
            }
        }

        if(isJolly == 1){
            printf("Jolly\n");
        }
        else{
            printf("Not jolly\n");
        }

        /*Reset variables for next test case*/
        isJolly = 1;  /*Assume sequence is jolly unless otherwise*/
        for(i = 0; i < 3000; i++){  /*Reset diffs to 0*/
            diffs[i] = 0;
        }

        numIntegers = acquireInputV2(sequence);
    }

    return 0;
}
