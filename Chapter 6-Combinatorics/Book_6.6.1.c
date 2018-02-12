/**UVa Online Judge ID 10183: How Many Fibs?
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>
#include <stdlib.h>

/* these values defined based on problem restraints*/
#define FIBTABLEMAXSIZE  490
#define NUMBERMAXDIGITS  110

typedef struct ArrayNum{  /*note: only positive integers will be dealt with in this problem*/
    int numDigits;
    int digits[NUMBERMAXDIGITS];  /*digits in reverse order*/
} ArrayNum;

int compArrayNums(ArrayNum * arrayNumA, ArrayNum * arrayNumB){
    int i;
    /*first compare the number of digits each ArrayNum has*/
    if(arrayNumA->numDigits > arrayNumB->numDigits){
        return 1;
    }
    else if(arrayNumA->numDigits < arrayNumB->numDigits){
        return -1;
    }
    else{  /*ie the two numbers have the same number of digits*/
        for(i = (arrayNumA->numDigits) - 1; i >= 0; i--){  /*compare individual digits*/
            if(arrayNumA->digits[i] > arrayNumB->digits[i]){
                return 1;
            }
            else if(arrayNumA->digits[i] < arrayNumB->digits[i]){
                return -1;
            }
        }
        return 0;  /*if function gets here, all digits of the two numbers are the same*/
    }
}

int acquireInput(ArrayNum * a, ArrayNum * b){
    char c, aFirstDigit, bFirstDigit;
    int i;
    char tempStr[NUMBERMAXDIGITS+1];
    int currentIndex = 0;

    /*acquire first number*/
    while( (c = getchar()) != ' '){
        tempStr[currentIndex] = c;
        currentIndex++;
    }
    aFirstDigit = tempStr[0];
    /*write digits in reverse order to ArrayNum*/
    for(i = 0; i < currentIndex; i++){
        a->digits[i] = tempStr[currentIndex-1-i] - '0';
    }
    a->numDigits = currentIndex;

    /*acquire second number*/
    currentIndex = 0;
    while( (c = getchar()) != '\n'){
        tempStr[currentIndex] = c;
        currentIndex++;
    }
    bFirstDigit = tempStr[0];
    /*write digits in reverse order to ArrayNum*/
    for(i = 0; i < currentIndex; i++){
        b->digits[i] = tempStr[currentIndex-1-i] - '0';
    }
    b->numDigits = currentIndex;

    if(aFirstDigit == '0' && bFirstDigit == '0'){
        return -1;  /*line indicating end of input was encountered*/
    }
    else{
        return 2;  /*successfully acquired two items*/
    }
}

int buildFibSequence(ArrayNum fibNums[], int nextIndex){
    int i,end, sum;
    int carry = 0;
    ArrayNum a = fibNums[nextIndex-1];
    ArrayNum b = fibNums[nextIndex-2];

    /*use the larger one between a's numDigits and b's numDigits*/
    if(a.numDigits > b.numDigits){
        end = a.numDigits;
    }
    else{
        end = b.numDigits;
    }

    /*add digits column by column*/
    for(i = 0; i < end; i++){
        sum = a.digits[i] + b.digits[i] + carry;
        if(sum >= 10){
            carry = 1;
            fibNums[nextIndex].digits[i] = sum - 10;
        }
        else{
            carry = 0;
            fibNums[nextIndex].digits[i] = sum;
        }
    }

    if(carry == 1){  /*if there's still a carry digit left over*/
        fibNums[nextIndex].digits[end] = 1;
        fibNums[nextIndex].numDigits = end + 1;
    }
    else{
        fibNums[nextIndex].numDigits = end;
    }

    return 0;
}

int returnFibsInInterval(ArrayNum fibTable[], ArrayNum * smallerNum, ArrayNum * largerNum){
    /*Uses binary search to find the smallest and largest Fibonacci numbers
      in the interval [smallerNum,largerNum]*/
    int retVal, currentIndex;
    int firstIncludedFibIndex, lastIncludedFibIndex;
    int lowerBound = 0;
    int upperBound = FIBTABLEMAXSIZE-1;

    /*search for smallest fib number >= smallerNum*/
    while(1){
        currentIndex = (lowerBound + upperBound)/2;
        retVal = compArrayNums(&(fibTable[currentIndex]), smallerNum);

        if(retVal == 1){  /*current num > smallerNum*/
            if(currentIndex-1 < 0  ||
               compArrayNums(&(fibTable[currentIndex-1]), smallerNum) == -1){
                /*if reached beyond the start of the array, or if the number before currentNum < smallerNum*/
                firstIncludedFibIndex = currentIndex;
                break;
            }
            else{
                upperBound = currentIndex;
            }
        }
        else if(retVal == -1){  /*current num < smallerNum*/
            lowerBound = currentIndex;
        }
        else{  /*current num == smallerNum*/
            firstIncludedFibIndex = currentIndex;
            break;
        }

        if(lowerBound == upperBound){  /*if smallerNum is not between two fib numbers in the array*/
            firstIncludedFibIndex = currentIndex;
            break;
        }
    }
    /*search for largest fib number <= largerNum*/
    lowerBound = 0;
    upperBound = FIBTABLEMAXSIZE-1;
    while(1){
        currentIndex = (lowerBound + upperBound)/2;
        retVal = compArrayNums(&(fibTable[currentIndex]), largerNum);

        if(retVal == 1){  /*current num > largerNum*/
            upperBound = currentIndex;
        }
        else if(retVal == -1){  /*current num < largerNum*/
            if(currentIndex+1 >= FIBTABLEMAXSIZE  ||
               compArrayNums(&(fibTable[currentIndex+1]), largerNum) == 1){
                /*if reached beyond the end of the array, or if the number after currentNum > largerNum*/
                lastIncludedFibIndex = currentIndex;
                break;
            }
            else{
                lowerBound = currentIndex;
            }
        }
        else{  /*current num == largerNum*/
            lastIncludedFibIndex = currentIndex;
            break;
        }

        if(lowerBound == upperBound){  /*if largerNum is not between two fib numbers in the array*/
            lastIncludedFibIndex = currentIndex;
            break;
        }
    }

    if(lastIncludedFibIndex >= firstIncludedFibIndex){
        /*if there is a fib number between the indices, the difference of the indices should >= 0*/
        return (lastIncludedFibIndex - firstIncludedFibIndex + 1);
    }
    else{  /*no fib number is between smallerNum and largerNum*/
        return 0;
    }
}

int main()
{
    int i,j;
    ArrayNum a,b;

    /*prepare table of Fibonacci numbers*/
    ArrayNum fibNums[FIBTABLEMAXSIZE];
    for(i = 0; i < FIBTABLEMAXSIZE; i++){  /*initialize all elements to 0*/
        for(j = 0; j < NUMBERMAXDIGITS; j++){
            fibNums[i].digits[j] = 0;
        }
    }
    /*initialize first two elements*/
    fibNums[0].numDigits = 1;
    fibNums[0].digits[0] = 1;
    fibNums[1].numDigits = 1;
    fibNums[1].digits[0] = 2;
    int nextIndex = 2;
    while(nextIndex < FIBTABLEMAXSIZE){
        buildFibSequence(fibNums,nextIndex);
        nextIndex++;
    }

    /* Debug
    printf("fibTable:\n");
    for(i = 0; i < FIBTABLEMAXSIZE; i++){
        printf("%d  ",fibNums[i].numDigits);
        for(j = 0; j < fibNums[i].numDigits; j++){
            printf("%d",fibNums[i].digits[fibNums[i].numDigits-1-j]);
        }
        printf("\n");
    }
    printf("\n");*/

    while(acquireInput(&a, &b) != -1){
        printf("%d\n",returnFibsInInterval(fibNums, &a, &b));
    }

    return 0;
}
