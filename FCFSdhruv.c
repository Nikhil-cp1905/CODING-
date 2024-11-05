#include <stdio.h>
void findwaiting(int proc[], int n, int bt[], int wt[]){
wt[0]=0;
for(int i=1;i<n;i++){
  wt[i]=bt[i-1]+wt[i-1];
}
}

void findturnaroudntime(int proc[],int n,int bt[],int wt[],int tat[]){
    for(int i=0;i<n;i++0{
       tat[i]=bt[i]+wt[i];
}
}

void findaveragetime(int proc[],int n,int bt[]){
   int wt[n],tat[n],total_wt=0;total_tat=0;
   findwaitingtime(proc,n,bt,wt);
   findturnaroundtime(proc,n,bt,wt,tat);
   printf("proc bursttime waitingtime turnaround");
   for(int i=0;i<n;i++){
      total_wt+=wt[i];
     
