/**UVa Online Judge ID 10082: WERTYU
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>
#include <string.h>

const int inputLineMaxLength = 100;  /*if a line of input is longer than 100 chars, adjust this variable*/

int main()
{
    int i,lineLength;
    char c;
    char inputLine[inputLineMaxLength];
    char correctLine[inputLineMaxLength];
    char correctChar[128] = {0};

    /*set up array correctChar (setting it up one by one is repetitive, but easier to do)*/
    correctChar[(int)' '] = ' ';  /*space is the only character that is correct*/
    /*first row of keyboard*/
    correctChar[(int)'1'] = '`';
    for(c = '2'; c <= '9'; c++){
        correctChar[(int)c] = c-1;
    }
    correctChar[(int)'0'] = '9';
    correctChar[(int)'-'] = '0';
    correctChar[(int)'='] = '-';

    /*second row of keyboard*/
    correctChar[(int)'W'] = 'Q';
    correctChar[(int)'E'] = 'W';
    correctChar[(int)'R'] = 'E';
    correctChar[(int)'T'] = 'R';
    correctChar[(int)'Y'] = 'T';
    correctChar[(int)'U'] = 'Y';
    correctChar[(int)'I'] = 'U';
    correctChar[(int)'O'] = 'I';
    correctChar[(int)'P'] = 'O';
    correctChar[(int)'['] = 'P';
    correctChar[(int)']'] = '[';
    correctChar[(int)'\\'] = ']';  /* the \ key*/

    /*third row of keyboard*/
    correctChar[(int)'S'] = 'A';
    correctChar[(int)'D'] = 'S';
    correctChar[(int)'F'] = 'D';
    correctChar[(int)'G'] = 'F';
    correctChar[(int)'H'] = 'G';
    correctChar[(int)'J'] = 'H';
    correctChar[(int)'K'] = 'J';
    correctChar[(int)'L'] = 'K';
    correctChar[(int)';'] = 'L';
    correctChar[(int)'\''] = ';';  /*the ' key*/

    /*fourth row of keyboard*/
    correctChar[(int)'X'] = 'Z';
    correctChar[(int)'C'] = 'X';
    correctChar[(int)'V'] = 'C';
    correctChar[(int)'B'] = 'V';
    correctChar[(int)'N'] = 'B';
    correctChar[(int)'M'] = 'N';
    correctChar[(int)','] = 'M';
    correctChar[(int)'.'] = ',';
    correctChar[(int)'/'] = '.';


    while(fgets(inputLine,inputLineMaxLength,stdin) != NULL){
        lineLength = strlen(inputLine)-1;  /*leave out the ending newline character*/
        for(i = 0; i < lineLength; i++){
            correctLine[i] = correctChar[(int)(inputLine[i])];
        }
        correctLine[lineLength] = '\0';  /*add the ending null character*/
        printf("%s\n",correctLine);
    }
    return 0;
}
