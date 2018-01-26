/**UVa Online Judge ID 10142: Australian Voting
Run time on UVa Online Judge displayed as: 0.070 seconds*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int advanceArrayIndex(char *str, int strLength, int *currentIndex){
    /*function assumes there is another element later on in the array after whitespace*/
    int i;
    for(i = *currentIndex; i < strLength; i++){
        if(str[i] == ' '){
            if(str[i+1] != ' '){
                (*currentIndex) = i+1;
                return i+1;
            }
        }
    }
    return -1;  /*function did not find the next number*/
}

int acquireBallots(int *ballots, int numCandidates){
    char inputLine[60];
    int ballotNum = 0;
    int pos = 0;
    int j;
    int strLength;
    while(fgets(inputLine,60,stdin) != NULL){
        if(inputLine[0] == '\n'){  /*stop after blank line between cases is reached*/
            break;
        }
        /*acquire choices from one ballot*/
        ballots[ballotNum*numCandidates +0] = atoi(&(inputLine[pos]));
        strLength = strlen(inputLine)-1;
        for(j = 1; j < numCandidates; j++){
            advanceArrayIndex(inputLine, strLength, &pos);
            ballots[ballotNum*numCandidates +j] = atoi(&(inputLine[pos]));
        }
        pos = 0;
        ballotNum++;  /*advance ballotNum index*/
    }
    return ballotNum;
}

int notEliminated(int * eliminatedList, int personVotedFor, int numCandidates){
    int i,person;
    for(i = 0; i < numCandidates; i++){
        person = eliminatedList[i];
        if(person == -1){  /*if reached the end of filled values in the array*/
            break;
        }
        else if(person == personVotedFor){
            return 0;  /*person is already eliminated*/
        }
    }
    return 1;  /*person isn't eliminated*/
}

int countVotes(int * ballots, int numValidBallots, int numCandidates, int * eliminatedCandidates){
    int i,j,n,index;
    int personVotedFor,numVotes;
    int personMostVotes = -1;
    int personSecondMostVotes = -1;
    int largestNumberOfVotes = 0;
    int smallestNumberOfVotes = 1001;  /*in this problem the maximum number of ballots is 1000*/
    int candidateVotes[numCandidates + 1];  /*One larger on purpose*/
    for(i = 0; i < numCandidates+1; i++){
        candidateVotes[i] = 0;  /*initialize values to 0*/
    }

    for(i = 0; i < numValidBallots; i++){  /*traverse ballots*/
        for(j = 0; j < numCandidates; j++){
            personVotedFor = ballots[i*numCandidates + j];
            if(notEliminated(eliminatedCandidates,personVotedFor,numCandidates)){
                /*for each ballot, count the highest ranked choice that is not an eliminated candidate*/
                candidateVotes[personVotedFor] += 1;
                break;
            }
        }
    }

    /*Find candidate with most votes*/
    for(n = 1; n < numCandidates+1; n++){
        numVotes = candidateVotes[n];
        if(numVotes >= largestNumberOfVotes){
            largestNumberOfVotes = numVotes;
            personSecondMostVotes = personMostVotes;
            personMostVotes = n;
        }
        if(numVotes < smallestNumberOfVotes && notEliminated(eliminatedCandidates,n,numCandidates)){
            /*keep track of what's the smallest number of votes in case a candidate(s) needs to be eliminated later*/
            smallestNumberOfVotes = numVotes;
        }
    }

    if(largestNumberOfVotes >= (numValidBallots/2)+1){  /*Someone has over 50% of the vote*/
        return personMostVotes;
    }
    else if(smallestNumberOfVotes == largestNumberOfVotes){  /*If all current candidates are tied*/
        return 0;
    }
    else{  /*No one has over 50% of the votes, eliminate candidates with the smallest number of votes*/
        index = 0;
        while(eliminatedCandidates[index] != -1){  /*Get to the first empty position*/
            index++;
        }
        for(n = 1; n < numCandidates+1; n++){
            if(candidateVotes[n] == smallestNumberOfVotes){  /*eliminate candidates with the smallest number of votes*/
                eliminatedCandidates[index] = n;
                index++;
            }
        }

        return countVotes(ballots,numValidBallots,numCandidates,eliminatedCandidates);  /*Recount with candidate(s) eliminated*/
    }

    return -1;  /*Function shouldn't get here*/
}


int main()
{
    int i,j,n,testCase;
    int numCandidates,numValidBallots,winner;
    int firstLoop = 1;
    char inputLine[84];
    int candidateNameLengths[21];  /*One row longer so array can be accessed starting from index 1*/
    char candidateNames[21][84];  /*One row longer so array can be accessed starting from index 1*/

    fgets(inputLine,5,stdin);  /*Read the number of test cases*/
    int numCases = atoi(inputLine);
    fgets(inputLine,5,stdin);  /*Read the blank line*/


    for(testCase = 0; testCase < numCases; testCase++){
        if(firstLoop != 1){
            printf("\n");  /*the blank line between cases*/
        }

        fgets(inputLine,5,stdin);  /*Read the number of candidates*/
        numCandidates = atoi(inputLine);

        /*set up arrays*/
        int ballots[1000*numCandidates];  /*a 2-D array represented as 1-D; accessed using ballots[i*numCandidates +j]*/
        int eliminatedCandidates[numCandidates];  /*contains the numbers representing eliminated candidates*/
        for(i = 0; i < numCandidates; i++){
            eliminatedCandidates[i] = -1;  /*initialize values to -1, meaning none*/
        }
        for(i = 0; i < 21; i++){
            for(j = 0; j < 84; j++){
                candidateNames[i][j] = ' ';  /*initialize values to "empty" characters*/
            }
        }

        /*Read the names of the candidates & store their lengths*/
        for(n = 1; n < numCandidates+1; n++){
            candidateNameLengths[n] = strlen(fgets(candidateNames[n],83,stdin)) - 1;  /*strlen counts the '\n' char, so subtract one*/
        }

        numValidBallots = acquireBallots(ballots,numCandidates);

        /*Note: the returned value winner matches the name array indices, starting from 1 to numCandidates*/
        winner = countVotes(ballots,numValidBallots,numCandidates,eliminatedCandidates);

        if(winner == 0){  /*Multiple people tied, print all non-eliminated names*/
            for(n = 1; n < numCandidates+1; n++){
                if(notEliminated(eliminatedCandidates,n,numCandidates)){
                    for(j = 0; j < (candidateNameLengths[n]); j++){
                        printf("%c",candidateNames[n][j]);
                    }
                    printf("\n");
                }
            }
        }
        else{  /*only one winner*/
            for(j = 0; j < (candidateNameLengths[winner]); j++){
                printf("%c",candidateNames[winner][j]);
            }
            printf("\n");
        }

        firstLoop = 0;
    }  /* end for(testCase = 0; testCase < numCases; testCase++)*/

    return 0;
}
