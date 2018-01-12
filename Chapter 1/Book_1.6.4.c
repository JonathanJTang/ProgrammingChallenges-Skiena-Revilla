/**UVa Online Judge ID 706: LCD Display
Run time on UVa Online Judge: 0.010 seconds*/

#include <stdio.h>
#include <string.h>

void fillInArray(){
    /* Making code into a separate function was not done
       as passing multi-dimensional array is a bit too complicated*/
}

int main(){
    int s;
    char numString[10];
    int digit,i,j;

    /*Get input for first loop*/
    scanf("%d %s",&s,numString);

    while(!(s == 0 && numString[0] == '0')){
        int numDigits = strlen(numString);
        int digitNumRows = 2*s+3;
        int digitNumColumns = s+2;
        char numPrint[numDigits][digitNumRows][digitNumColumns];

        /*Initialize array to all spaces*/
        for(digit = 0; digit < numDigits; digit++){
            for(i = 0; i < digitNumRows; i++){
                for(j = 0; j < digitNumColumns; j++){
                    numPrint[digit][i][j] = ' ';
                }
            }
        }

        /*Fill in array numPrint*/
        for(digit = 0; digit < numDigits; digit++){
            /*For each digit...(this code should be a separate function, by passing 2D arrays is too complicated)*/

            /*All 7 segments of the "LCD display" for the digit enabled by default*/
            /*1 is True, 0 is False*/
            int top = 1;
            int topLeft = 1;
            int topRight = 1;
            int middle = 1;
            int bottomLeft = 1;
            int bottomRight = 1;
            int bottom = 1;

            switch(numString[digit]){
                case '0':
                    middle = 0;
                    break;
                case '1':
                    top = 0;
                    topLeft = 0;
                    middle = 0;
                    bottomLeft = 0;
                    bottom = 0;
                    break;
                case '2':
                    topLeft = 0;
                    bottomRight = 0;
                    break;
                case '3':
                    topLeft = 0;
                    bottomLeft = 0;
                    break;
                case '4':
                    top = 0;
                    bottomLeft = 0;
                    bottom = 0;
                    break;
                case '5':
                    topRight = 0;
                    bottomLeft = 0;
                    break;
                case '6':
                    topRight = 0;
                    break;
                case '7':
                    topLeft = 0;
                    middle = 0;
                    bottomLeft = 0;
                    bottom = 0;
                    break;
                case '8':
                    break;
                case '9':
                    bottomLeft = 0;
                    break;
            }  /* end switch(numString[digit]) */

            /*write the enabled segments to digitArray*/
            if(top == 1){
                for(i = 1; i <= s; i++){
                    numPrint[digit][0][i] = '-';  /*Fill in the top segment*/
                }
            }
            if(topLeft == 1){
                for(j = 1; j <= s; j++){
                    numPrint[digit][j][0] = '|';  /*Fill in the top left segment*/
                }
            }
            if(topRight == 1){
                for(j = 1; j <= s; j++){
                    numPrint[digit][j][digitNumColumns-1] = '|';  /*Fill in the top right segment*/
                }
            }
            if(middle == 1){
                for(i = 1; i <= s; i++){
                    numPrint[digit][s+1][i] = '-';  /*Fill in the middle segment*/
                }
            }
            if(bottomLeft == 1){
                for(j = s+2; j <= 2*s+1; j++){
                    numPrint[digit][j][0] = '|';  /*Fill in the bottom left segment*/
                }
            }
            if(bottomRight == 1){
                for(j = s+2; j <= 2*s+1; j++){
                    numPrint[digit][j][digitNumColumns-1] = '|';  /*Fill in the bottom right segment*/
                }
            }
            if(bottom == 1){
                for(i = 1; i <= s; i++){
                    numPrint[digit][digitNumRows-1][i] = '-';  /*Fill in the bottom segment*/
                }
            }
        }  /* end for(digit = 0; digit < numDigits; digit++) */

        /*Print lines*/
        for(i = 0; i < digitNumRows; i++){  /*Printing a number line by line*/
            for(digit = 0; digit < numDigits-1; digit++){  /*Print info from all digits except the last one*/
                for(j = 0; j < digitNumColumns; j++){
                    printf("%c",numPrint[digit][i][j]);
                }
                printf(" ");
            }
            for(j = 0; j < digitNumColumns; j++){  /*Print the last digit's line  (no space after the digit)*/
                printf("%c",numPrint[numDigits-1][i][j]);
            }
            printf("\n");  /*The ending newline for the line*/
        }
        printf("\n");  /*The blank line after each number*/

        /*Get input for next loop*/
        scanf("%d %s",&s,numString);
    }  /* end while(!(s == 0 && numString[0] == '0')) */

    return 0;
}
