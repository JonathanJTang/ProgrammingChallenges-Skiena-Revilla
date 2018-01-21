/**UVa Online Judge ID 10258: Contest Scoreboard
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>
#include <stdlib.h>

#define totalNumberOfProblems  9  /*a value set by the problem*/
#define numContestants  100  /*a value set by the problem*/


/*A struct used to hold info needed to calculate a contestant's ranking*/
typedef struct Contestant{
    int enabled;  /*a Contestant is enabled when one of its entries is received by the program*/
    int teamNum;  /*teamNums range from 1 to numContestants found in main()*/

    int numProblemsSolved;
    int totalPenaltyTime;
    int problemsSolved[totalNumberOfProblems];  /*will contain 0s and 1s (False/True)*/
    int problemPreviousIncorrectSubmissions[totalNumberOfProblems];
} Contestant;

int initContestantList(Contestant * contestantList, int listLength){
    int entry,i;
    for(entry = 0; entry < listLength; entry++){
        contestantList[entry].teamNum = entry + 1;
        contestantList[entry].enabled = 0;  /*enabled = False*/
        contestantList[entry].numProblemsSolved = 0;  /*initialize to 0*/
        contestantList[entry].totalPenaltyTime = 0;  /*initialize to 0*/
        for(i = 0; i < totalNumberOfProblems; i++){  /*initialize all elements to 0*/
            contestantList[entry].problemsSolved[i] = 0;  /*initialize to False*/
            contestantList[entry].problemPreviousIncorrectSubmissions[i] = 0;  /*initialize to 0*/
        }
    }
    return 0;
}


int compContestants(const void * first, const void * second){
    /*first and second are pointers to a pointer of a Contestant object*/
    Contestant * a = *(Contestant**)first;
    Contestant * b = *(Contestant**)second;
    if(a == NULL){
        return -1;  /*a < b*/
    }
    else if(b == NULL){
        return 1;  /*b < a*/
    }

    else{  /*both a and b are not NULL pointers*/
        if( (a->numProblemsSolved) > (b->numProblemsSolved) ){
            return 1;  /*a > b*/
        }
        else if( (a->numProblemsSolved) < (b->numProblemsSolved) ){
            return -1;  /*a < b*/
        }

        else{  /*a and b have solved the same number of problems*/
            if( (a->totalPenaltyTime) > (b->totalPenaltyTime) ){
                return -1;  /*b > a*/
            }
            else if( (a->totalPenaltyTime) < (b->totalPenaltyTime) ){
                return 1;  /*a > b*/
            }

            else{  /*a and b have the same amount of total penalty time*/
                if( (a->teamNum) > (b->teamNum) ){
                    return -1;  /*a < b*/
                }
                else{
                    return 1;  /*a > b*/
                }
            }
        }
    }
}

int printEnabledContestantsInOrder(Contestant * contestantList, int listLength){
    Contestant * contestantPtrList[listLength];
    int enabledContestants = 0;
    int entry,i;
    for(entry = 0; entry < listLength; entry++){
        if(contestantList[entry].enabled == 0){  /*Don't process the unenabled contestants*/
            contestantPtrList[entry] = NULL;
            continue;
        }

        contestantPtrList[entry] = &(contestantList[entry]);
        enabledContestants++;
        /*Calculate penalty time*/
        for(i = 0; i < totalNumberOfProblems; i++){
            if(contestantList[entry].problemsSolved[i] == 1){  /*this is only done for solved problems*/
                contestantList[entry].totalPenaltyTime += 20 * contestantList[entry].problemPreviousIncorrectSubmissions[i];
            }
        }
    }

    /*Build the smaller array enabledContestantsPtrList for quicker sorting*/
    Contestant * enabledContestantsPtrList[enabledContestants];
    int enabledContestantsPtrListIndex = 0;
    for(entry = 0; entry < listLength; entry++){
        if(contestantPtrList[entry] != NULL){
            enabledContestantsPtrList[enabledContestantsPtrListIndex] = contestantPtrList[entry];
            enabledContestantsPtrListIndex++;
        }
    }

    qsort(enabledContestantsPtrList,enabledContestants,sizeof(enabledContestantsPtrList[0]),compContestants);

    /*Print contestant info from highest-ranking to lowest-ranking*/
    for(entry = enabledContestants-1; entry >= 0; entry--){
        printf("%d %d %d\n",(enabledContestantsPtrList[entry])->teamNum,(enabledContestantsPtrList[entry])->numProblemsSolved,(enabledContestantsPtrList[entry])->totalPenaltyTime);
    }

    return 0;
}


int main()
{
    int testCase;
    char inputStr[14];
    int firstLoop = 1;
    int contestant, problem, time;
    char L;

    Contestant contestantList[numContestants];

    int numTestCases = atoi(fgets(inputStr,14,stdin));
    fgets(inputStr,14,stdin);  /*Read blank line*/

    for(testCase = 0; testCase < numTestCases; testCase++){
        initContestantList(contestantList,numContestants);

        if(firstLoop != 1){
            printf("\n");  /*Print blank line between cases*/
        }

        while(fgets(inputStr,14,stdin) != NULL){
            if(inputStr[0] == '\n'){  /*Reached the end of current test case's input*/
                break;
            }
            sscanf(inputStr,"%d %d %d %c",&contestant,&problem,&time,&L);  /*extract info from inputStr*/
            contestantList[contestant-1].enabled = 1;
            switch(L){
                case 'I':
                    if(contestantList[contestant-1].problemsSolved[problem-1] != 1){  /*If the problem hasn't yet been solved*/
                        contestantList[contestant-1].problemPreviousIncorrectSubmissions[problem-1] += 1;
                    }
                    break;

                case 'C':
                    if(contestantList[contestant-1].problemsSolved[problem-1] == 0){  /*If the problem previously was not solved*/
                        contestantList[contestant-1].problemsSolved[problem-1] = 1;  /*Make variable True*/
                        contestantList[contestant-1].totalPenaltyTime += time;
                        contestantList[contestant-1].numProblemsSolved += 1;
                    }
                    break;

                default:
                    /*Do nothing if the last character isn't 'I' or 'C'*/
                    break;
            }
        }  /* end while(fgets(inputStr,14,stdin) != NULL) */

        printEnabledContestantsInOrder(contestantList,numContestants);

        firstLoop = 0;

    }  /* end for(testCase = 0; testCase < numTestCases; testCase++) */

    return 0;
}
