/**UVa Online Judge ID 10137: The Trip
Run time on UVa Online Judge displayed as: 0.000 seconds*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fabs(double arg); /*absolute function for decimals*/
double floor(double arg);


int main()
{
    int i;
    char inputLine[12];
    double dollarAmounts[1000];
    for(i = 0; i < 1000; i++){
        dollarAmounts[i] = 0.0;  /*initialize array*/
    }
    double item,amount,averageCost,averageCostRounded;
    double totalCost = 0.0;
    double totalDiffA = 0.0;
    double totalDiffB = 0.0;

    int numStudents = atoi(fgets(inputLine,11,stdin));  /*acquire number of students*/
    while(numStudents != 0){  /*0 for numStudnets signifies end of input */
        for(i = 0; i < numStudents; i++){  /*acquire amounts*/
             amount = atof(fgets(inputLine,11,stdin));
             dollarAmounts[i] = amount;
             totalCost += amount;
        }
        averageCost = totalCost / numStudents;
        averageCostRounded = floor(averageCost*100 + 0.5) / 100;  /*round averageCost to nearest cent*/

        /* For debugging
        printf("averageCost=%lf, averageCostRounded=%lf\n",averageCost,averageCostRounded); */

        for(i = 0; i < numStudents; i++){  /*Iterate over each itme in array dollarAmounts*/
            item = dollarAmounts[i];
            if(item < averageCostRounded){
                totalDiffA += fabs(item - averageCostRounded);  /*Differences for items less expensive than averageCostRounded*/
            }
            else{
                totalDiffB += fabs(item - averageCostRounded);  /*Differences for items more expensive than averageCostRounded*/
            }
        }
        /* For debugging
        printf("diffA=%lf, diffB=%lf\n",totalDiffA,totalDiffB);*/

        /*Choose the smaller one between totalDiffA and totalDiffB*/
        if(totalDiffA < totalDiffB){
            printf("$%.2f\n",totalDiffA);
        }
        else{
            printf("$%.2f\n",totalDiffB);
        }

        /*Get info for next test case, resest variables*/
        numStudents = atoi(fgets(inputLine,11,stdin));
        totalCost = 0.0;
        totalDiffA = 0.0;
        totalDiffB = 0.0;
    }
    return 0;
}
