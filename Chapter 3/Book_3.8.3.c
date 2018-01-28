/**UVa Online Judge ID 10252: Common Permutation
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>
#include <string.h>

int getLine(char inputLine[1002]){
    /*obtains a line of input and adds the null character at the end, even if the line is a blank line*/
    int i = 0;
    int c;
    char actualChar;
    while((c = getchar()) != EOF){
        actualChar = (char)c;
        if(actualChar == '\n'){  /*end when the ending newline character is encountered*/
            break;
        }
        inputLine[i] = actualChar;
        i++;
    }
    inputLine[i] = '\0';  /*add the terminating null character*/
    return 0;
}

int buildLetterFreqList(char str[], int freqList[26]){
    /*Assumes that all elements of freqList are 0*/
    int i;
    for(i = 0; i < strlen(str); i++){
        freqList[str[i] - 'a'] += 1;  /*increment the frequency of the corresponding letter*/
    }
    return 0;
}

int main()
{
    int i,n;
    int firstLoop = 1;
    int strAFreq,strBFreq;
    char inputLine[1002];
    int letterFreqsA[26] = {0};
    int letterFreqsB[26] = {0};

    while(feof(stdin) == 0){
        getLine(inputLine);
        buildLetterFreqList(inputLine,letterFreqsA);
        getLine(inputLine);
        buildLetterFreqList(inputLine,letterFreqsB);

        if(!firstLoop){
            printf("\n");  /*print the ending newline char for all lines except the very last one*/
        }

        for(i = 0; i < 26; i++){
            strAFreq = letterFreqsA[i];
            strBFreq = letterFreqsB[i];
            if(strAFreq <= strBFreq){
                for(n = 0; n < strAFreq; n++){
                    printf("%c",'a'+i);
                }
            }
            else{
                for(n = 0; n < strBFreq; n++){
                    printf("%c",'a'+i);
                }
            }
        }

        firstLoop = 0;
        for(i = 0; i < 26; i++){  /*reset arrays*/
            letterFreqsA[i] = 0;
            letterFreqsB[i] = 0;
        }
    }  /* end while(feof(stdin) == 0) */

    return 0;
}
