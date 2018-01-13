/**UVa Online Judge ID 10267: Graphical Editor
Run time on UVa Online Judge: 0.000 seconds*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int strNextElementIndex(char *str, int *currentIndex){
    /*This function doesn't do any checking; it assumes that after the
    next space in str there will be a character that is the start of a number or letter/word
    The value currentIndex points to will be modified*/
    int i;
    for(i = *currentIndex; i < strlen(str)-1; i++){  /*strlen-1 to ignore the ending newline character*/
        if(str[i] == ' '){
            if(str[i+1] != ' '){
                (*currentIndex) = i+1;
                return i+1;  /*i+1 is the index needed by the caller*/
            }
        }
    }
    return -1; /*function did not find the next number*/
}

/* Function for debugging */
int printOneDCharArrayAsTwoD(char * oneDCharArray, int numRows, int numColumns){
    int i,j;
    for(i = 0; i < numRows; i++){  /*traverse rows*/
        for(j = 0; j < numColumns; j++){  /*traverse columns*/
            printf("%c",oneDCharArray[i*numColumns +j]);
        }
        printf("\n");  /*ending newline character at the end of a line*/
    }
    return 0;
}

int crawlFill(char *image, int numRows, int numColumns, int y, int x, char origC, char newC){
    /*A modifier function; uses recursion*/
    /*Currently uses identical code many times, could be optimized*/
    int otherY,otherX;
    image[y*numColumns +x] = newC;
    if(!(y >= numRows)){  /*unless pixel is on the bottom row of the image */
        otherY = y+1;  /*search the pixel below the current pixel*/
        otherX = x;
        if(image[otherY*numColumns +otherX] == origC){
            crawlFill(image,numRows,numColumns,otherY,otherX,origC,newC);
        }
    }
    if(!(y <= 1)){  /*unless pixel is on the top row of the image */
        otherY = y-1;  /*search the pixel above the current pixel*/
        otherX = x;
        if(image[otherY*numColumns +otherX] == origC){
            crawlFill(image,numRows,numColumns,otherY,otherX,origC,newC);
        }
    }
    if(!(x >= numColumns)){  /*unless pixel is on the right-most column of the image */
        otherY = y;
        otherX = x+1;  /*search the pixel to the right of the current pixel*/
        if(image[otherY*numColumns +otherX] == origC){
            crawlFill(image,numRows,numColumns,otherY,otherX,origC,newC);
        }
    }
    if(!(x <= 1)){  /*unless pixel is on the left-most column of the image */
        otherY = y;
        otherX = x-1;  /*search the pixel to the left of the current pixel*/
        if(image[otherY*numColumns +otherX] == origC){
            crawlFill(image,numRows,numColumns,otherY,otherX,origC,newC);
        }
    }
    return 0;
}

int imageSubroutine(int numRows, int numColumns, char * editorLine){
    /*Due to difficulties with initializing an array in the switch statement in main,
    Actions upon an image are done in this separate function*/
    int i,j,pos;
    int x,y,x1,x2,y1,y2;
    int temp;
    char commandName;
    char c, newC, origC;
    char image[(numRows+1)*(numColumns+1)];  /*make image one row larger and one columns larger for easier processing*/
    for(i = 0; i < numRows+1; i++){  /*Initialize all elements of image to char O (the capital letter O, not zero) */
        for(j = 0; j < numColumns+1; j++){
            image[i*numColumns +j] = 'O';  /*The capital letter O, not zero*/
        }
    }

    fgets(editorLine,30,stdin);  /*Get new line of editor command*/
    commandName = editorLine[0];

    while(1){
        switch(commandName){
            case 'X':
                return 0;  /*Need to terminate the session; return this to main()*/
                break;

            case 'I':
                return 1;  /*Need to create new image; leave editorLine to be handled by main()*/
                break;

            case 'C':  /*Initialize/reset all elements of image */
                for(i = 1; i < numRows+1; i++){
                    for(j = 1; j < numColumns+1; j++){
                        image[i*numColumns +j] = 'O';  /*The capital letter O, not zero*/
                    }
                }
                break;

            case 'L':  /*color the given pixel*/
                pos = 2;
                j = atoi(&(editorLine[pos]));
                i = atoi(&(editorLine[strNextElementIndex(editorLine,&pos)]));
                image[i*numColumns +j] = editorLine[strNextElementIndex(editorLine,&pos)];
                break;

            case 'V':  /*color the given vertical segment*/
                pos = 2;
                x = atoi(&(editorLine[pos]));
                y1 = atoi(&(editorLine[strNextElementIndex(editorLine,&pos)]));
                y2 = atoi(&(editorLine[strNextElementIndex(editorLine,&pos)]));
                c = editorLine[strNextElementIndex(editorLine,&pos)];
                if(y1 > y2){
                    /*Switch y1 and y2 if necessary*/
                    temp = y2;
                    y2 = y1;
                    y1 = temp;
                }
                for(i = y1; i < y2+1; i++){  /*Iterate over pixels in given region*/
                    image[i*numColumns +x] = c;
                }
                break;

            case 'H':  /*color the given horizontal segment*/
                pos = 2;
                x1 = atoi(&(editorLine[pos]));
                x2 = atoi(&(editorLine[strNextElementIndex(editorLine,&pos)]));
                y = atoi(&(editorLine[strNextElementIndex(editorLine,&pos)]));
                c = editorLine[strNextElementIndex(editorLine,&pos)];
                if(x1 > x2){
                    /*Switch x1 and x2 to make x1 smaller than x2, if necessary*/
                    temp = x2;
                    x2 = x1;
                    x1 = temp;
                }
                for(j = x1; j < x2+1; j++){  /*Iterate over pixels in given region*/
                    image[y*numColumns +j] = c;
                }
                break;

            case 'K':  /*color the given rectangular-shaped region*/
                pos = 2;
                x1 = atoi(&(editorLine[pos]));
                y1 = atoi(&(editorLine[strNextElementIndex(editorLine,&pos)]));
                x2 = atoi(&(editorLine[strNextElementIndex(editorLine,&pos)]));
                y2 = atoi(&(editorLine[strNextElementIndex(editorLine,&pos)]));
                c = editorLine[strNextElementIndex(editorLine,&pos)];
                if(x1 > x2){
                    /*Switch x1 and x2 to make x1 smaller than x2, if necessary*/
                    temp = x2;
                    x2 = x1;
                    x1 = temp;
                }
                if(y1 > y2){
                    /*Switch y1 and y2 to make y2 bigger than y1, if necessary*/
                    temp = y2;
                    y2 = y1;
                    y1 = temp;
                }
                for(i = y1; i < y2+1; i++){  /*Iterate over pixels in given region*/
                    for(j = x1; j < x2+1; j++){
                        image[i*numColumns +j] = c;
                    }
                }
                break;

            case 'F':  /*color pixels in given "region"; see problem description for how a "region" is defined*/
                pos = 2;
                x = atoi(&(editorLine[pos]));
                y = atoi(&(editorLine[strNextElementIndex(editorLine,&pos)]));
                newC = editorLine[strNextElementIndex(editorLine,&pos)];
                origC = image[y*numColumns+ x];
                if(origC != newC){
                    crawlFill(image,numRows,numColumns,y,x,origC,newC);
                }
                break;

            case 'S':  /*Print contents of current image*/
                /*Print name of file*/
                for(pos = 2; pos < strlen(editorLine)-1; pos++){ /*strlen-1 to avoid the last newline character*/
                    printf("%c",editorLine[pos]);
                }
                printf("\n");
                /*Print pixels of image*/
                for(i = 1; i < numRows+1; i++){  /*traverse rows of image*/
                    for(j = 1; j < numColumns+1; j++){  /*traverse columns of image*/
                        printf("%c",image[i*numColumns +j]);
                    }
                    printf("\n");  /*ending newline character at the end of each line*/
                }
                break;
        }  /* end switch(commandName) */

        fgets(editorLine,30,stdin);  /*Get new line of editor command*/
        commandName = editorLine[0];
    }  /* end while(1) */

    return -1;  /*Function shouldn't get here, as a command should eventually return a value in the switch statement*/
}


int main()
{
    int pos;
    int numColumns,numRows;
    int returnVal = 0;
    char editorLine[30];
    char commandName;

    fgets(editorLine,30,stdin);  /*Get new line of editor command*/
    commandName = editorLine[0];

    while(1){
        switch(commandName){
            case 'X':
                return 0;  /*Need to terminate session*/
                break;

            case 'I':
                pos = 2;  /*str[2] is the start of the first number*/
                numColumns = atoi(&(editorLine[pos]));
                numRows = atoi(&(editorLine[strNextElementIndex(editorLine,&pos)]));
                returnVal = imageSubroutine(numRows,numColumns,editorLine);
                if(returnVal == 0){
                    return 0;  /*imageSubrountine read an 'X', need to terminate session*/
                }
                break;
        }
        if(returnVal != 1){  /*if imageSubroutine did not read an 'I' command*/
            fgets(editorLine,30,stdin);  /*Get new line of editor command*/
        }
        commandName = editorLine[0];
    }

    return -1;  /*Function should not reach here*/
}
