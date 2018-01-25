/**UVa Online Judge ID 10033: Interpreter
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>
#include <stdlib.h>

int acquireRAM(int * ram, int casesLeft){
    int value;
    int pos = 0;
    char inputLine[5];

    fgets(inputLine,5,stdin);
    while(inputLine[0] != '\n'){  /*the loop stops when the blank line between cases is reached*/
        value = atoi(inputLine);
        ram[pos] = value;
        if(value == 100 && casesLeft == 0){  /*If reached 100 halt on the last case*/
            break;
        }
        pos++;
        fgets(inputLine,5,stdin);
    }
    return 0;
}

int processRAM(int * ram, int * reg){
    int instructionsExecuted = 0;
    int pos = 0;
    int num,firstDigit,middleDigit,lastDigit;

    while(1){  /*while True*/
        num = ram[pos];
        pos++;
        /*Extract digits from the 3-digit number*/
        lastDigit = num % 10;
        num /= 10;  /*In C, integer division floors*/
        middleDigit = num % 10;
        num /= 10;
        firstDigit = num;

        switch(firstDigit){
            case 1:  /*halt*/
                instructionsExecuted++;
                return instructionsExecuted;
                break;

            case 2:  /*Set register d (middleDigit) to n (lastDigit)*/
                reg[middleDigit] = lastDigit;
                break;

            case 3:  /*Add n (lastDigit) to register d (middleDigit)*/
                reg[middleDigit] = (reg[middleDigit] + lastDigit) % 1000;
                break;

            case 4:  /*Multiply register d (middleDigit) by n (lastDigit)*/
                reg[middleDigit] = (reg[middleDigit] * lastDigit) % 1000;
                break;

            case 5:  /*Set register d (middleDigit) to the value of register s (lastDigit)*/
                reg[middleDigit] = reg[lastDigit];
                break;

            case 6:  /*Add value of register s (lastDigit) to register d (middleDigit)*/
                reg[middleDigit] = (reg[middleDigit] + reg[lastDigit]) % 1000;
                break;

            case 7:  /*Multiply value of register d (middleDigit) by value of register s (lastDigit)*/
                reg[middleDigit] = (reg[middleDigit] * reg[lastDigit]) % 1000;
                break;

            case 8:  /*Set register d (middleDigit) to value in RAM whose address is in register a (lastDigit)*/
                reg[middleDigit] = ram[reg[lastDigit]];
                break;

            case 9:  /*Set value in RAM whose address is in register a (lastDigit) to the value of register s (middleDigit)*/
                ram[reg[lastDigit]] = reg[middleDigit];
                break;

            case 0:  /*goto location in register d (middleDigit), unless register s (lastDigit) contains 0*/
                if(reg[lastDigit] != 0){
                    pos = reg[middleDigit];
                }
                break;
        }  /* end switch(firstDigit) */
        instructionsExecuted++;

    }  /* end while(1) */

    return -1;  /*The function shouldn't get here*/
}

int main()
{
    int i,pos,testCase;
    int firstLoop = 1;
    int reg[10];
    int ram[1000];
    for(i = 0; i < 10; i++){  /*Initialize array reg to 0*/
        reg[i] = 0;
    }
    for(pos = 0; pos < 1000; pos++){  /*Initialize array ram to 0*/
        ram[pos] = 0;
    }

    char inputLine[5];
    fgets(inputLine,3,stdin);  /*Get first line*/
    int numCases = atoi(inputLine);
    fgets(inputLine,3,stdin);  /*Read the blank line*/

    /*Loop is here*/
    for(testCase = 1; testCase <= numCases; testCase++){
        acquireRAM(ram,numCases-testCase);

        if(firstLoop != 1){
            printf("\n");
        }
        printf("%d\n",processRAM(ram,reg));
        firstLoop = 0;

        /*Reset variables*/
        for(i = 0; i < 10; i++){  /*Reset array reg to 0 */
            reg[i] = 0;
        }
        for(pos = 0; pos < 1000; pos++){  /*Reset array ram to 0 */
            ram[pos] = 0;
        }
    }

    return 0;
}
