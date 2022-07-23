/**
* This program loads processes data from a .txt file, simulates
* SJF and SJFL scheduling algorithms on the input data and display
* the results to the user
* Completion time: (5 hours)
*
* @author Mohammad Hamdan
* @version (1.0)
*
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct process{

int tau;
float alpha;
int* times;
int pid;

} process;

typedef struct timeArray{

int time;
int pid;

} timeArray;

process* processes = NULL;
int numberOfTicks;
int numberOfProcesses;



void selectionSort(timeArray* arr, int n)
{
    int min_idx;

    for (int i = 0; i < n; i++)
    {

        min_idx = i;
        for (int j = i+1; j < n; j++)
          if (arr[j].time < arr[min_idx].time)
            min_idx = j;

        timeArray temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;

    }
}
void readFile(char* filename){

  FILE* file = fopen(filename, "r");

  if (file == NULL){

  printf("no such file");
  return;
  }

fscanf(file, "%d", &numberOfTicks);
fscanf(file, "%d", &numberOfProcesses);
readProcesses(file);
fclose(file);
printSJF(processes);
printSJFL(processes);
terminateProcesses(&processes);
}



void readProcesses(FILE* file){

processes = malloc(sizeof(process) * numberOfProcesses);

for (int i=0; i<numberOfProcesses; i++){

        fscanf(file, "%d", &processes[i].pid);
        fscanf(file, "%d", &processes[i].tau);
        fscanf(file, "%f", &processes[i].alpha);
        processes[i].times =(int*) malloc(sizeof(int)*numberOfTicks);

    for (int j=0; j<numberOfTicks; j++){


        fscanf(file, "%d", &processes[i].times[j]);

    }
}

}


void printSJF(process* processes){

printf("== Shortest - Job - First ==\n");

int sum=0;
int waitingTime[numberOfProcesses];
waitingTime[0]=0;
int totalWaitingTime=0;
int turnaroundTime[numberOfProcesses];
int totalTurnarounTime=0;
timeArray* arr = malloc(sizeof(timeArray)* numberOfProcesses);

for (int i=0; i<numberOfTicks; i++){

    printf("Simulating %dth tick of processes @ time %d\n:", i, sum);

for (int j=0; j<numberOfProcesses; j++){

    arr[j].time = processes[j].times[i];
    arr[j].pid = processes[j].pid;
}

selectionSort(arr, numberOfProcesses);

for (int x=0; x<numberOfProcesses; x++){

printf("Process %d took %d.\n", arr[x].pid, arr[x].time);
sum = sum + arr[x].time;
}

for (int y=1; y<numberOfProcesses; y++){
waitingTime[y]=0;

for (int k=0; k<y; k++){

    waitingTime[y] = arr[k].time + waitingTime[y];
}

    totalWaitingTime = totalWaitingTime+waitingTime[y];
}


for (int n=0; n<numberOfProcesses; n++){
    turnaroundTime[n] = waitingTime[n]+arr[n].time;
    totalTurnarounTime = totalTurnarounTime + turnaroundTime[n];

}

}

printf("Turnaround time : %d\n", totalTurnarounTime);
printf("Waiting time : %d\n", totalWaitingTime);

free(arr);

}

void printSJFL(process* processes){

printf("== Shortest - Job - First Live ==\n");

int sum=0;
int waitingTime[numberOfProcesses];
waitingTime[0]=0;
int totalWaitingTime=0;
int turnaroundTime[numberOfProcesses];
int totalTurnarounTime=0;
int error=0;
timeArray** tauArr =  malloc(sizeof(timeArray*) * numberOfTicks);

for (int c=0; c< numberOfTicks; c++){

    tauArr[c] = malloc(sizeof(timeArray)*numberOfProcesses);
}


for (int i=0; i < numberOfTicks; i++){

 printf("Simulating %dth tick of processes @ time %d:\n", i, sum);

if (i==0){

   for (int k=0; k<numberOfProcesses; k++){

    tauArr[i][k].time = processes[k].tau;
    tauArr[i][k].pid = processes[k].pid;
    error = abs(tauArr[i][k].time - processes[k].times[i]) + error;
}

selectionSort(tauArr[i], numberOfProcesses);

for (int p=0; p<numberOfProcesses; p++){

    printf("Process %d was estimated for %d and took %d.\n", tauArr[i][p].pid, tauArr[i][p].time, processes[tauArr[i][p].pid].times[i]);
    sum = sum + processes[tauArr[i][p].pid].times[i];
}


for (int y=1; y<numberOfProcesses; y++){
waitingTime[y]=0;

for (int t=0; t<y; t++){

    waitingTime[y] = processes[tauArr[i][t].pid].times[i] + waitingTime[y];
}

    totalWaitingTime = totalWaitingTime+waitingTime[y];
}


for (int m=0; m<numberOfProcesses; m++){
    turnaroundTime[m] = waitingTime[m]+tauArr[i][m].time;
    totalTurnarounTime = totalTurnarounTime + turnaroundTime[m];

}

}

else {

for (int k=0; k<numberOfProcesses; k++){

    tauArr[i][k].time = (processes[k].times[i-1]*processes[k].alpha) + ((1 - (processes[k].alpha))*(tauArr[i-1][k].time));
    tauArr[i][k].pid = processes[k].pid;

}

selectionSort(tauArr[i], numberOfProcesses);

for (int p=0; p<numberOfProcesses; p++){

    printf("Process %d was estimated for %d and took %d.\n", tauArr[i][p].pid, tauArr[i][p].time, processes[tauArr[i][p].pid].times[i]);
    sum = sum + processes[tauArr[i][p].pid].times[i];
    error = abs(tauArr[i][p].time - processes[tauArr[i][p].pid].times[i]) + error;

}

for (int y=1; y<numberOfProcesses; y++){
waitingTime[y]=0;

for (int t=0; t<y; t++){

    waitingTime[y] = processes[tauArr[i][t].pid].times[i]+ waitingTime[y];
}

    totalWaitingTime = totalWaitingTime+waitingTime[y];
}


for (int m=0; m<numberOfProcesses; m++){
    turnaroundTime[m] = waitingTime[m]+tauArr[i][m].time;
    totalTurnarounTime = totalTurnarounTime + turnaroundTime[m];

}
}

}
printf("Turnaround time : %d\n", totalTurnarounTime);
printf("Waiting time : %d\n", totalWaitingTime);
printf("Estimation Error :%d\n", error);

terminateTimeArr(tauArr);

}

void terminateProcesses(process** processes){

free((*processes)->times);

free(*processes);

*processes = NULL;

}

void terminateTimeArr(timeArray** arr){

for (int i=0; i<numberOfTicks; i++){

    free(arr[i]);
}

free(arr);

}



int main(int argc, char* argv[])
{

 char* fileName;
 fileName = argv[1];


 readFile(fileName);


    return 0;
}
