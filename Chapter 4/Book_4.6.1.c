/**UVa Online Judge ID 10041: Vito's Family
Run time on UVa Online Judge displayed as: 0.030 seconds*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compInts(const void * a, const void * b){
    int numA = *((int *)a);
    int numB = *((int *)b);
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

int acquireInput(int arr[]){
    int i, numItems;
    char inputLine[3010];
    fgets(inputLine,3010,stdin);
    numItems = atoi(strtok(inputLine," "));  /*the first number in the line is the number of items*/
    for(i = 0; i < numItems; i++){
        arr[i] = atoi(strtok(NULL," "));  /*get the other numbers in the line, each separated by a " " char*/
    }
    return numItems;
}

int main()
{
    int testCase,vitoHouse,i;
    char inputLine[5];
    int relativeAddresses[30000];
    int minNum, maxNum,numRelatives,minSumDifferences,currentSumDifferences,partition;
    int numTestCases = atoi(fgets(inputLine,5,stdin));

    for(testCase = 0; testCase < numTestCases; testCase++){
        numRelatives = acquireInput(relativeAddresses);
        qsort(relativeAddresses,numRelatives,sizeof(int),compInts);
        minNum = relativeAddresses[0];
        maxNum = relativeAddresses[numRelatives-1];
        /*partition is the index of the last element in (sorted array) relativeAddresses that is less than vitoHouse*/
        partition = 0;

        currentSumDifferences = 0;
        /*calculate the initial value for currentSumDifferences and minSumDifferences*/
        for(i = 0; i < numRelatives; i++){
            currentSumDifferences += abs(minNum - relativeAddresses[i]);
        }
        minSumDifferences = currentSumDifferences;

        for(vitoHouse = minNum+1; vitoHouse <= maxNum; vitoHouse++){
            /*advance partition*/
            for(i = partition; i < numRelatives; i++){
                if(relativeAddresses[i] >= vitoHouse){
                    partition = i-1;
                    break;
                }
            }

            /*update currentSumDifferences: add 1 for each number less than vitoHouse,
            subtract 1 for each number greater than or equal to vitoHouse; ie
            currentSumDifferences = currentSumDifferences + partition-0+1 - (numRelatives-1 - (partition+1) +1);*/
            currentSumDifferences = currentSumDifferences + 2*partition +2 - numRelatives;

            if(currentSumDifferences < minSumDifferences){
                minSumDifferences = currentSumDifferences;
            }
        }

        printf("%d\n", minSumDifferences);
    }  /* end for(testCase = 0; testCase < numTestCases; testCase++) */

    return 0;
}
