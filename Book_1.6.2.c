/**UVa Online Judge ID 10189: Minesweeper
Run time on UVa Online Judge: 0.000 seconds*/

#include <stdio.h>

int numSurroundingMines(char field[][102], int row, int column){
    /**Returns the number of mines surrounding a square.
       row and column are the indices used to access array field*/
    int count = 0;
    if(field[row-1][column-1] == '*'){
        count++;
    }
    if(field[row-1][column] == '*'){
        count++;
    }
    if(field[row-1][column+1] == '*'){
        count++;
    }
    if(field[row][column-1] == '*'){
        count++;
    }
    if(field[row][column+1] == '*'){
        count++;
    }
    if(field[row+1][column-1] == '*'){
        count++;
    }
    if(field[row+1][column] == '*'){
        count++;
    }
    if(field[row+1][column+1] == '*'){
        count++;
    }
    return count;
}

int main(){
    int i, j, n, m;
    int firstLoop = 1;
    int fieldNum = 0;

    scanf("%d %d",&n,&m);
    while(n != 0 && m != 0){  /*Program will run until 0 0 is inputed*/
        /*make array field one unit larger on all four sides for easier calculations:
          the actual board will be surrounded by a ring of safe squares*/
        char field[n+2][102];  /*column width is set to 102, the max num of columns to make it easier to pass it to the function*/
        for(i = 0; i < n+2; i++){
            for(j = 0; j < m+2; j++){
                field[i][j] = '.';  /*Initialize all squares in array as safe spaces*/
            }
        }
        fieldNum++;

        char line[m+2];
        for(i = 0; i < n; i++){  /*Read each line of the input field*/
            scanf("%s",line);
            for(j = 0; j < m; j++){
                field[i+1][j+1] = line[j];  /*Write obtained input to array field*/
            }
        }

        /*Start printing output for this test case*/
        if(firstLoop != 1){  /*Print a blank line before output for this case only if it's not the first loop*/
            printf("\n");
        }
        printf("Field #%d:\n",fieldNum);
        for(i = 1; i <= n; i++){  /*Iterate over rows in field*/
            for(j = 1; j <= m; j++){  /*Iterate over columns in field*/
                if(field[i][j] == '*'){
                    printf("*");  /*print symbol for a mine if the square in field is a mine*/
                }
                else{ /*if the square in field is empty, print the number of surrounding mines*/
                    printf("%d",numSurroundingMines(field,i,j));
                }
            }
            printf("\n");  /*print ending newline character after printing a row*/
        }

        /*Get input for next loop*/
        scanf("%d %d",&n,&m);
        firstLoop = 0;
    }
    return 0;
}
