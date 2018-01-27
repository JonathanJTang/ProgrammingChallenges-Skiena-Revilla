/**UVa Online Judge ID 10010: Where's Waldorf?
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int acquireInput(char letterGrid[][50], int numRows, int numColumns, char targetWords[][51]){
    char inputLine[53];
    int i,j;
    int numTargetWords, wordLength;

    for(i = 0; i < numRows; i++){
        fgets(inputLine,53,stdin);
        for(j = 0; j < numColumns; j++){
            letterGrid[i][j] = tolower(inputLine[j]);  /*convert all letters to lowercase*/
        }
    }

    numTargetWords = atoi(fgets(inputLine,4,stdin));
    for(i = 0; i < numTargetWords; i++){
        fgets(inputLine,52,stdin);
        wordLength = strlen(inputLine)-1;  /*exclude the ending newline character*/
        for(j = 0; j < wordLength; j++){
            targetWords[i][j] = tolower(inputLine[j]);  /*convert all letters to lowercase*/
        }
        targetWords[i][wordLength] = '\0';  /*add the terminating null char*/
    }

    return numTargetWords;
}

int isValidIndex(int row, int column, int numRows, int numColumns){
    if(row < 0 || row >= numRows || column < 0 || column >= numColumns){  /*check that (row column) is not out of bounds*/
        return 0;  /*not a valid index*/
    }
    else{
        return 1;  /*is a valid index*/
    }
}

int searchForWord(char letterGrid[][50], int numRows, int numColumns, int currentRow, int currentColumn, int dRow, int dColumn,
                  char * target, int targetLength, int charsLeft){
    int newRow, newColumn;

    if(letterGrid[currentRow][currentColumn] != target[targetLength-charsLeft]){
        /*stop if the current letter doesn't match the corresponding letter of the target word*/
        return 0;
    }
    else{
        charsLeft--;
        if(charsLeft == 0){  /*if the search gets to this point, a match has been found*/
            return 1;
        }
        else{
            newRow = currentRow + dRow;
            newColumn = currentColumn + dColumn;
            if(isValidIndex(newRow,newColumn,numRows,numColumns)){
                return searchForWord(letterGrid,numRows,numColumns,newRow,newColumn,dRow,dColumn,target,targetLength,charsLeft);
            }
            return 0;  /*stop if (newRow newColumn) is not a valid index */
        }
    }
}


int main()
{
    int i,j,n,wordNum,testCase;
    int numRows,numColumns,numTargetWords;
    int firstLoop = 1;
    int foundWord = 0;
    char inputLine[53];
    char targetWords[20][51];  /*assuming that no target words are longer than 50 characters*/
    int directionDeltas[16] = {-1,-1,  -1,0,  -1,1,
                                0,-1,          0,1,
                                1,-1,   1,0,   1,1};  /*changes to row and column indices needed to search all 8 directions*/

    int numTestCases = atoi(fgets(inputLine,4,stdin));

    for(testCase = 0; testCase < numTestCases; testCase++){
        if(!firstLoop){
            printf("\n");  /*blank line between cases*/
        }
        fgets(inputLine,4,stdin);  /*read blank line*/

        scanf("%d %d ",&numRows,&numColumns);
        char letterGrid[numRows][50];

        numTargetWords = acquireInput(letterGrid,numRows,numColumns,targetWords);

        for(wordNum = 0; wordNum < numTargetWords; wordNum++){  /*iterate through the target words*/
            /*set starting position in topmost row, then leftmost column and move on from there*/
            for(i = 0; i < numRows; i++){
                for(j = 0; j < numColumns; j++){
                    for(n = 0; n < 8; n++){
                        if(searchForWord(letterGrid,numRows,numColumns,i,j,directionDeltas[n*2],directionDeltas[n*2+1],targetWords[wordNum],strlen(targetWords[wordNum]),strlen(targetWords[wordNum]))){
                            printf("%d %d\n",i+1,j+1);  /*array indices start from 0 while output indices start from 1*/
                            foundWord = 1;  /*a way to break out of multiple nested for loops*/
                            break;
                        }
                    }
                    if(foundWord){
                        break;
                    }
                }
                if(foundWord){
                    break;
                }
            }
            foundWord = 0;  /*reset after each word is found*/
        }
        firstLoop = 0;

    }  /* end for(testCase = 0; testCase < numTestCases; testCase++) */

    return 0;
}
