/**UVa Online Judge ID 10018: Reverse and Add
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>

#define MAXNUMDIGITS 10

typedef struct ArrayNum{
    /*A representation of an integer, with each digit as an element in an arry*/
    int numDigits;
    int digits[MAXNUMDIGITS];  /*will start from the rightmost digit to the leftmost digit*/
} ArrayNum;

int initializeArrayNum(ArrayNum * num){
    int i;
    num->numDigits = 0;
    for(i = 0; i < MAXNUMDIGITS; i++){
        num->digits[i] = 0;
    }
    return 0;
}

char * returnString(ArrayNum * num, char * str){
    int i;
    for(i = 0; i < num->numDigits; i++){
        /*display num->digits in reverse order to show the actual order*/
        str[i] = '0' + num->digits[num->numDigits -1 -i];
    }
    str[num->numDigits] = '\0';  /*the terminating null character*/
    return str;
}

int acquireNumber(ArrayNum * num){
    char c;
    int i;
    int tempArray[MAXNUMDIGITS];
    int currentIndex = 0;
    while( (c=getchar()) != '\n'){
        tempArray[currentIndex] = c - '0';
        currentIndex++;
    }
    /*reverse order of digits*/
    for(i = 0; i < currentIndex; i++){
        num->digits[i] = tempArray[currentIndex-1-i];
    }
    num->numDigits = currentIndex;

    return 0;
}

int isPalindrome(ArrayNum * num){
    int i;
    int end = (num->numDigits)/2;
    for(i = 0; i < end; i++){
        if(num->digits[i] != num->digits[num->numDigits -1 - i]){
            return 0;  /*num is not palindrome*/
        }
    }
    return 1;  /*num is palindrome*/
}

int reverseAdd(ArrayNum * origNum, ArrayNum * temp){
    int i, sum;
    int carry = 0;
    for(i = 0; i < origNum->numDigits; i++){
        sum = origNum->digits[i] + origNum->digits[origNum->numDigits-1-i] + carry;  /*add "opposite" digits*/
        if(sum >= 10){
            carry = 1;  /*a carry digit for the next addition*/
            temp->digits[i] = sum - 10;
        }
        else{
            carry = 0;  /*no carry digit*/
            temp->digits[i] = sum;
        }
    }
    if(carry == 1){  /*if there's a carry digit at the end of the addition operation*/
        temp->digits[origNum->numDigits] = 1;
        temp->numDigits = origNum->numDigits + 1;
    }
    else{
        temp->numDigits = origNum->numDigits;
    }

    *origNum = *temp;  /*overwrite origNum with temp*/

    return 0;
}

int main()
{
    int testCase;
    int numTestCases;
    int iterations = 0;
    char outputLine[MAXNUMDIGITS+1];
    ArrayNum numberA, tempNum;

    scanf(" %d",&numTestCases);
    getchar();  /*read the ending newline char*/
    for(testCase = 0; testCase < numTestCases; testCase++){
        acquireNumber(&numberA);
        /*the main loop: repeatedly reverseAdd until the number is a palindrome*/
        while(1){
            reverseAdd(&numberA, &tempNum);
            iterations++;
            if(isPalindrome(&numberA)){
                break;
            }
        }
        printf("%d %s\n",iterations,returnString(&numberA,outputLine));
        iterations = 0;
    }
    return 0;
}
