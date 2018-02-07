/**UVa Online Judge ID 120: Stacks of Flapjacks
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compInts(const void * a, const void * b){
    int numA = *((int*)a);
    int numB = *((int*)b);
    if(numA > numB){
        return 1;
    }
    else if(numA < numB){
        return -1;
    }
    else{
        return 0;
    }
}

int extractNumberArray(char inputLine[], int arr[]){
    char * str;
    int numItems = 0;
    arr[numItems] = atoi(strtok(inputLine," "));  /*get number*/
    numItems++;
    while((str = strtok(NULL," ")) != NULL){  /*get numbers, each separated by a " " char, until the end of inputLine*/
        arr[numItems] = atoi(str);
        numItems++;
    }
    return numItems;
}

int isSorted(int pancakeArray[], int arrSize){
    int i;
    for(i = 0; i < arrSize-1; i++){
        if(pancakeArray[i+1] < pancakeArray[i]){
            return 0;  /*the pancake array is not sorted*/
        }
    }
    return 1;  /*if function gets to here, the pancake array is sorted*/
}

int flipSubStack(int pancakeArray[], int arrSize, int beginningIndex){
    int i;
    int temp;
    int endingNum = (beginningIndex+1)/2;  /*note: this integer division floors*/
    for(i = 0; i < endingNum; i++){
        /*swap corresponding elements*/
        temp = pancakeArray[beginningIndex-i];
        pancakeArray[beginningIndex-i] = pancakeArray[i];
        pancakeArray[i] = temp;
    }
    printf("%d ",arrSize-beginningIndex);
    /*debug
    for(i = 0; i < arrSize; i++){
        printf("%d ",pancakeArray[i]);
    }
    printf("\n");*/
    return 0;
}

int main()
{
    int i;
    int numPancakes, targetPancakeValue, targetStackIndex, index;
    int pancakeArray[30];  /*index 0 is top, end of array is bottom*/
    int pancakeArraySortedValues[30];  /*will be a sorted copy of pancakeArray*/
    char inputLine[130];

    while(fgets(inputLine,130,stdin) != NULL){
        printf("%s",inputLine);  /*echo the input as requested by the problem*/
        numPancakes = extractNumberArray(inputLine, pancakeArray);
        for(i = 0; i < numPancakes; i++){  /*make a copy of pancakeArray*/
            pancakeArraySortedValues[i] = pancakeArray[i];
        }
        qsort(pancakeArraySortedValues,numPancakes,sizeof(int),compInts);

        targetStackIndex = numPancakes - 1;
        targetPancakeValue = pancakeArraySortedValues[targetStackIndex];
        /*The main algorithm loop
          Note that other algorithms may produce a different sequence of results that also work*/
        while(!isSorted(pancakeArray,numPancakes)){
            if(pancakeArray[targetStackIndex] != targetPancakeValue){
                /*if targetPancake is not at its corresponding position near the bottom of the stack*/

                if(pancakeArray[0] != targetPancakeValue){
                    /*if targetPancake is not the topmost pancake of the entire stack,
                      flip so that targetPancake becomes the topmost pancake of the entire stack*/
                    for(i = 0; i < targetStackIndex; i++){
                        if(pancakeArray[i] == targetPancakeValue){
                            index = i;
                            break;
                        }
                    }
                    flipSubStack(pancakeArray,numPancakes,index);
                }

                /*flip the appropriate portion of the stack so that targetPancake is at its correct
                  position near the bottom of the stack*/
                flipSubStack(pancakeArray,numPancakes,targetStackIndex);

            }  /* end if(pancakeArray[targetStackIndex] != targetPancakeValue) */

            /*prepare for next iteration*/
            targetStackIndex--;
            targetPancakeValue = pancakeArraySortedValues[targetStackIndex];

        }  /* end while(!isSorted(pancakeArray,numPancakes)) */

        printf("0\n");
    }
    return 0;
}
