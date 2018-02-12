/**UVa Online Judge ID 10198: Counting
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>

#define RESULTSARRAYMAXLEN  1001  /*defined by problem*/
#define MAXNUMDIGITS  410  /*derived based on the maximum input number*/

typedef struct ArrayNum{
    /*An array representation of really large integers*/
    int numDigits;
    char digits[MAXNUMDIGITS];  /*will contains digits in reverse order*/
} ArrayNum;

int calculatePossibleNumbers(int n){
    /*The recursive form of the logic used in this program.
      Was replaced by a table of results since this function took too long*/
    int output = 0;
    if(n == 0){
        return 1;  /*at the base case, there's only 1 way to make a number*/
    }

    if(n >= 3){
        output += calculatePossibleNumbers(n-3);
    }
    if(n >= 2){
        output += calculatePossibleNumbers(n-2);
    }
    if(n >= 1){
        output += 2*calculatePossibleNumbers(n-1);  /*Gustavo thinks digit '4' and digit '1' both represent the number 1*/
    }
    return output;
}

void addArrayNums(ArrayNum * a, ArrayNum * b, ArrayNum * c, ArrayNum * sumNum){
    /*adds numbers a, b, & c, where a is the n-3 term, b is the n-2 term, and c is the n-1 term;
      then writes result in sumNum*/
    int i, largestNumDigits, sum;
    int carry = 0;

    /*For numDigits, compare the larger of a & b with c to find the largest numDigits*/
    if(a->numDigits >= b->numDigits){
        if(a->numDigits >= c->numDigits){
            largestNumDigits = a->numDigits;
        }
        else{  /*ie c->numDigits > a->numDigits*/
            largestNumDigits = c->numDigits;
        }
    }
    else{  /*ie b->numDigits > a->numDigits*/
        if(b->numDigits >= c->numDigits){
            largestNumDigits = b->numDigits;
        }
        else{  /*ie c->numDigits > b->numDigits*/
            largestNumDigits = c->numDigits;
        }
    }

    /*Add digits, column by column*/
    for(i = 0; i < largestNumDigits; i++){
        sum = a->digits[i] + b->digits[i] + 2*(c->digits[i]) - '0'*4 + carry;  /*digits are chars, while sum and carry are ints*/
        carry = 0;  /*reset carry after using it*/
        while(sum >= 10){  /*determine carry for next loop*/
            sum -= 10;
            carry++;
        }
        sumNum->digits[i] = '0' + sum;
    }

    /*process the leftover carry digits, if any*/
    if(carry > 0){
        sumNum->digits[largestNumDigits] = '0' + carry;
        sumNum->numDigits = largestNumDigits + 1;
    }
    else{
        sumNum->numDigits = largestNumDigits;
    }
}

char * returnArrayNumStr(ArrayNum * num, char * str){
    /*Returns a string representation of the given ArrayNum.
      Assumes that parameter str is a char array with enough length*/
    int i;
    /*reverse order of digits to show the true order*/
    for(i = 0; i < num->numDigits; i++){
        str[i] = num->digits[num->numDigits -1 - i];
    }
    str[num->numDigits] = '\0';  /*terminating null byte*/
    return str;
}

int main()
{
    int i,j,inputN;
    char outputLine[MAXNUMDIGITS+1];

    /*initialize results array*/
    ArrayNum results[RESULTSARRAYMAXLEN];
    for(i = 1; i < RESULTSARRAYMAXLEN; i++){
        for(j = 0; j < MAXNUMDIGITS; j++){
            results[i].digits[j] = '0';  /*set all digits to '0' for easier processing*/
        }
    }
    /*set the first three terms*/
    results[1].digits[0] = '2';
    results[1].numDigits = 1;

    results[2].digits[0] = '5';
    results[2].numDigits = 1;

    results[3].digits[1] = '1';
    results[3].digits[0] = '3';
    results[3].numDigits = 2;
    int resultsCurrentSize = 3;

    /*the main loop*/
    while(scanf(" %d",&inputN) != EOF){
        while(inputN > resultsCurrentSize){  /*build results array if needed*/
            addArrayNums(&(results[resultsCurrentSize-2]),&(results[resultsCurrentSize-1]),&(results[resultsCurrentSize]),&(results[resultsCurrentSize+1]));
            resultsCurrentSize++;
        }
        printf("%s\n",returnArrayNumStr(&(results[inputN]),outputLine));
    }

    return 0;
}
