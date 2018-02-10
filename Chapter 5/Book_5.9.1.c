/**UVa Online Judge ID 10035: Primary Arithmetic
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>

#define INTEGERMAXDIGITS 11

int acquireInput(int digitArray1[], int digitArray2[]){
    char c;
    int i;
    int digitArray1Len;
    int currentIndex = 0;
    int tempDigitArray[INTEGERMAXDIGITS] = {0};

    /*acquire first number*/
    while( (c=getchar()) != ' '){
        tempDigitArray[currentIndex] = c - '0';
        currentIndex++;
    }
    /*reverse order of digits*/
    for(i = 0; i < currentIndex; i++){
        digitArray1[i] = tempDigitArray[currentIndex-1-i];
    }
    digitArray1Len = currentIndex;
    currentIndex = 0;

    /*acquire second number*/
    while( (c=getchar()) != '\n'){
        tempDigitArray[currentIndex] = c - '0';
        currentIndex++;
    }
    if(digitArray1[digitArray1Len-1] == 0 && tempDigitArray[0] == 0){
        /*if first digit of both input numbers are 0, line indicating end of input was encountered*/
        return -1;
    }
    /*reverse order of digits*/
    for(i = 0; i < currentIndex; i++){
        digitArray2[i] = tempDigitArray[currentIndex-1-i];
    }

    /*add a terminating digit at the end of each array to signify end of number*/
    if(currentIndex >= digitArray1Len){
        digitArray1[currentIndex] = -1;  /*add a terminating digit*/
        digitArray2[currentIndex] = -1;  /*add a terminating digit*/
    }
    else{
        digitArray1[digitArray1Len] = -1;  /*add a terminating digit*/
        digitArray2[digitArray1Len] = -1;  /*add a terminating digit*/
    }

    return 0;
}

int printOutput(int numCarryOperations){
    switch(numCarryOperations){
        case 0:
            printf("No carry operation.\n");
            break;
        case 1:
            printf("1 carry operation.\n");
            break;
        default:
            printf("%d carry operations.\n",numCarryOperations);
            break;
    }
    return 0;
}

int main()
{
    int i;
    int digitA, digitB;
    int numCarryOperations = 0;
    int carry = 0;
    /*Note: these two arrays represent the digits of the numbers from right to left*/
    int digitArray1[INTEGERMAXDIGITS] = {0};
    int digitArray2[INTEGERMAXDIGITS] = {0};

    while(acquireInput(digitArray1,digitArray2) != -1){
        for(i = 0; i < INTEGERMAXDIGITS; i++){
            digitA = digitArray1[i];
            digitB = digitArray2[i];
            if(digitA == -1 || digitB == -1){  /*if reached end of numbers*/
                printOutput(numCarryOperations);
                break;
            }
            /*add digits*/
            if((digitA + digitB + carry) >= 10){  /*note: the sum of two single-digit numbers and 1 will be < 20*/
                numCarryOperations++;
                carry = 1;  /*there is a carry operation*/
            }
            else{
                carry = 0;  /*no carry operation*/
            }
        }

        /*reset variables for next iteration*/
        for(i = 0; i < INTEGERMAXDIGITS; i++){
            digitArray1[i] = 0;
            digitArray2[i] = 0;
        }
        numCarryOperations = 0;
        carry = 0;
    }

    return 0;
}
