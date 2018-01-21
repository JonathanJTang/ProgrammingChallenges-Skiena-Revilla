/**UVa Online Judge ID 100: The 3n + 1 Problem
Run time on UVa Online Judge displayed as: 0.320 seconds*/

#include <stdio.h>

int main(){
    /*Use unsigned long int since numbers range between 0 and 1 000 000*/
    unsigned long int origI, origJ, i, j, num, n;
    unsigned long int maxCycleLength, currentCycleLength;

    while(scanf("%ld %ld",&origI,&origJ) == 2){ /*This part will not be true after EOF has been reached*/
        maxCycleLength = 1; /*Reset this variable for each line of input*/

        /* If origI > origJ, swap i and j so that i < j*/
        if(origI > origJ){
            i = origJ;
            j = origI;
        }
        else{
            i = origI;
            j = origJ;
        }

        /*Iterate over numbers between i and j (inclusive) to find maxCycleLength*/
        for(num = i; num <= j; num++){
            n = num;
            currentCycleLength = 1; /*Reset this variable for each number between i and j*/

            /*Code to follow the 3n+1 calculation sequence*/
            while(n != 1){
                if(n % 2 == 0){ /*If n is even*/
                    n = n/2;
                }
                else{ /*If n is odd*/
                    n = 3*n + 1;
                }
                currentCycleLength++;
            }

            if(currentCycleLength > maxCycleLength){
                /*Store new cycle length only if it's longer than the previous longest cycle length*/
                maxCycleLength = currentCycleLength;
            }
        }
        printf("%ld %ld %ld\n",origI,origJ,maxCycleLength); /*print output after processing a line of input*/
    }
    return 0;
}
