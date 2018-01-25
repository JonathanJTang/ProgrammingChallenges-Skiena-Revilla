/**UVa Online Judge ID 10196: Check the Check
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>
#include <string.h>


/*White pieces are represented with uppercase letters,
while black pieces arerepresented with lowercase letters.
White side will always be on the bottom of the board,
while black side will always be on the top of the board.*/

const int numRows = 8;  /*value set by problem*/
const int numColumns = 8;  /*value set by problem*/
const char pieces[2][3] = {{'R','Q','B'},{'r','q','b'}};  /*R for rook, Q for queen, B for bishop*/

int isValidIndex(int i, int j){
    /*returns 1 if true, 0 if false*/
    if(i >= 0 && i < numRows && j >= 0 && j < numColumns){
        return 1;
    }
    else{
        return 0;
    }
}

int acquireBoard(char * board){
    int i,j;
    int emptyRows = 0;
    char inputLine[10];

    for(i = 0; i < numRows; i++){
        fgets(inputLine,10,stdin);
        if(strncmp("........",inputLine,8) == 0){  /*if the first 8 bytes of the strings are the same*/
            emptyRows++;
        }
        for(j = 0; j < numColumns; j++){
            board[i*numColumns +j] = inputLine[j];
        }
    }

    if(emptyRows == numRows){
        return -1;  /*The board is empty*/
    }
    return 0;  /*The board is not empty*/
}

int oppRooks(char *board, int kI, int kJ, char currentSideChar){
    /*Check for the opposite side's Rooks or Queens by looking along the column and row of (kI,kJ)*/
    int oppSide;
    char currentPiece;
    int currentI,currentJ;

    if(currentSideChar == 'w'){
        oppSide = 1;
    }
    else if(currentSideChar == 'b'){
        oppSide = 0;
    }

    /*Search horizontally*/
    currentI = kI;
    for(currentJ = kJ+1; currentJ < numColumns; currentJ++){  /*search to the right*/
        currentPiece = board[currentI*numColumns +currentJ];
        if(currentPiece == pieces[oppSide][0] || currentPiece == pieces[oppSide][1]){
            /*If currentPiece is oppSide's rook or queen*/
            return 1;  /*King in check*/
        }
        else if(currentPiece != '.'){  /*if currentPiece is not empty*/
            break;
        }
    }
    for(currentJ = kJ-1; currentJ >= 0; currentJ--){  /*serach to the left*/
        currentPiece = board[currentI*numColumns +currentJ];
        if(currentPiece == pieces[oppSide][0] || currentPiece == pieces[oppSide][1]){
            /*If currentPiece is oppSide's rook or queen*/
            return 1;  /*King in check*/
        }
        else if(currentPiece != '.'){  /*if currentPiece is not empty*/
            break;
        }
    }

    /*Search vertically*/
    currentJ = kJ;
    for(currentI = kI+1; currentI < numRows; currentI++){  /*search downwards*/
        currentPiece = board[currentI*numColumns +currentJ];
        if(currentPiece == pieces[oppSide][0] || currentPiece == pieces[oppSide][1]){
            /*If currentPiece is oppSide's rook or queen*/
            return 1;  /*King in check*/
        }
        else if(currentPiece != '.'){  /*if currentPiece is not empty*/
            break;
        }
    }
    for(currentI = kI-1; currentI >= 0; currentI--){  /*search upwards*/
        currentPiece = board[currentI*numColumns +currentJ];
        if(currentPiece == pieces[oppSide][0] || currentPiece == pieces[oppSide][1]){
            /*If currentPiece is oppSide's rook or queen*/
            return 1;  /*King in check*/
        }
        else if(currentPiece != '.'){  /*if currentPiece is not empty*/
            break;
        }
    }

    return 0;  /*No pieces are checking the king*/
}

int oppBishops(char *board, int kI, int kJ, char currentSideChar){
    /*Check for the opposite side's Bishops or Queens by looking diagonally from (kI,kJ)*/
    int oppSide;
    char currentPiece;
    int currentI,currentJ;

    if(currentSideChar == 'w'){
        oppSide = 1;
    }
    else if(currentSideChar == 'b'){
        oppSide = 0;
    }

    /*Search diagonally: down right*/
    currentI = kI+1;
    currentJ = kJ+1;
    while(isValidIndex(currentI,currentJ)){
        currentPiece = board[currentI*numColumns +currentJ];
        if(currentPiece == pieces[oppSide][2] || currentPiece == pieces[oppSide][1]){
            /*If currentPiece is oppSide's bishop or queen*/
            return 1;  /*King in check*/
        }
        else if(currentPiece != '.'){  /*if currentPiece is not empty*/
            break;
        }
        currentI++;
        currentJ++;
    }
    /*Search diagonally: down left*/
    currentI = kI+1;
    currentJ = kJ-1;
    while(isValidIndex(currentI,currentJ)){
        currentPiece = board[currentI*numColumns +currentJ];
        if(currentPiece == pieces[oppSide][2] || currentPiece == pieces[oppSide][1]){
            /*If currentPiece is oppSide's bishop or queen*/
            return 1;  /*King in check*/
        }
        else if(currentPiece != '.'){  /*if currentPiece is not empty*/
            break;
        }
        currentI++;
        currentJ--;
    }

    /*Search diagonally: up left*/
    currentI = kI-1;
    currentJ = kJ-1;
    while(isValidIndex(currentI,currentJ)){
        currentPiece = board[currentI*numColumns +currentJ];
        if(currentPiece == pieces[oppSide][2] || currentPiece == pieces[oppSide][1]){
            /*If currentPiece is oppSide's bishop or queen*/
            return 1;  /*King in check*/
        }
        else if(currentPiece != '.'){  /*if currentPiece is not empty*/
            break;
        }
        currentI--;
        currentJ--;
    }

    /*Search diagonally: up right*/
    currentI = kI-1;
    currentJ = kJ+1;
    while(isValidIndex(currentI,currentJ)){
        currentPiece = board[currentI*numColumns +currentJ];
        if(currentPiece == pieces[oppSide][2] || currentPiece == pieces[oppSide][1]){
            /*If currentPiece is oppSide's bishop or queen*/
            return 1;  /*King in check*/
        }
        else if(currentPiece != '.'){  /*if currentPiece is not empty*/
            break;
        }
        currentI--;
        currentJ++;
    }

    return 0;  /*No pieces are checking the king*/
}

int processBoard(char *board){
    int i,j,n;
    int currentI,currentJ;
    int wKI,wKJ,bKI,bKJ;  /*the positions of the white king (wK) and the black king (bK)*/
    char tempChar;

    /*Find the kings' positions*/
    for(i = 0; i < numRows; i++){
        for(j = 0; j < numColumns; j++){
            tempChar = board[i*numColumns +j];
            if(tempChar == 'K'){
                wKI = i;
                wKJ = j;
            }
            else if(tempChar == 'k'){
                bKI = i;
                bKJ = j;
            }
        }
    }

    /*Consider white king first*/
    /*The potential positions where black pawns could be checking the king*/
    int bPawnCoordList[4] = {wKI-1,wKJ-1, wKI-1,wKJ+1};
    for(n = 0; n < 2; n++){  /*pawns, 2 cases*/
        currentI = bPawnCoordList[n*2];
        currentJ = bPawnCoordList[n*2+1];
        if(isValidIndex(currentI,currentJ)){
            if(board[currentI*numColumns +currentJ] == 'p'){
                return 1;  /*White king in check*/
            }
        }
    }
    /*The potential positions where black knights could be checking the king*/
    int bKnightCoordList[16] = {wKI-1,wKJ-2, wKI-1,wKJ+2, wKI-2,wKJ+1, wKI-2,wKJ-1, wKI+2,wKJ+1, wKI+2,wKJ-1, wKI+1,wKJ-2, wKI+1,wKJ+2};
    for(n = 0; n < 8; n++){  /*knights, 8 cases*/
        currentI = bKnightCoordList[n*2];
        currentJ = bKnightCoordList[n*2+1];
        if(isValidIndex(currentI,currentJ)){
            if(board[currentI*numColumns +currentJ] == 'n'){
                return 1;  /*White king in check*/
            }
        }
    }
    if(oppRooks(board,wKI,wKJ,'w') == 1){
        return 1;  /*White king in check*/
    }
    if(oppBishops(board,wKI,wKJ,'w') == 1){
        return 1;  /*White king in check*/
    }


    /*Now consider black king*/
    /*The potential positions where white pawns could be checking the king*/
    int wPawnCoordList[4] = {bKI+1,bKJ-1, bKI+1,bKJ+1};
    for(n = 0; n < 2; n++){  /*pawns, 2 cases*/
        currentI = wPawnCoordList[n*2];
        currentJ = wPawnCoordList[n*2+1];
        if(isValidIndex(currentI,currentJ)){
            if(board[currentI*numColumns +currentJ] == 'P'){
                return 2;  /*Black king in check*/
            }
        }
    }
    /*The potential positions where white knights could be checking the king*/
    int wKnightCoordList[16] = {bKI-1,bKJ-2, bKI-1,bKJ+2, bKI-2,bKJ+1, bKI-2,bKJ-1, bKI+2,bKJ+1, bKI+2,bKJ-1, bKI+1,bKJ-2, bKI+1,bKJ+2};
    for(n = 0; n < 8; n++){  /*knights, 8 cases*/
        currentI = wKnightCoordList[n*2];
        currentJ = wKnightCoordList[n*2+1];
        if(isValidIndex(currentI,currentJ)){
            if(board[currentI*numColumns +currentJ] == 'N'){
                return 2;  /*Black king in check*/
            }
        }
    }
    if(oppRooks(board,bKI,bKJ,'b') == 1){
        return 2;  /*Black king in check*/
    }
    if(oppBishops(board,bKI,bKJ,'b') == 1){
        return 2;  /*Black king in check*/
    }

    return 0;  /*Neither king is in check, return 0*/
}

int main()
{
    /*board is a 1-D array that represents the 2-D chess board.
    accessed (i,j) of 2-D chess board using: board[i*numColumns +j]*/
    char board[numRows*numColumns];
    int boardNum = 1;
    int ret;  /*return value*/
    char inputLine[10];

    while(acquireBoard(board) != -1){  /*while board is not empty*/
        fgets(inputLine,10,stdin);  /*Read the empty line*/

        ret = processBoard(board);
        if(ret == 1){
            printf("Game #%d: white king is in check.\n",boardNum);
        }
        else if(ret == 2){
            printf("Game #%d: black king is in check.\n",boardNum);
        }
        else{
            printf("Game #%d: no king is in check.\n",boardNum);
        }

        boardNum++;
    }
    return 0;
}
