#include<stdio.h>
#define MAX 30


void Roundrobin(){
    int i, n, sq = 0, bt[MAX], wt[MAX], rem_bt[MAX], tat[MAX], qt, count;
    float awt = 0, atat = 0;

    printf("Enter the Number of processes: ");
    scanf("%d", &n);
    printf("Enter the Burst time of each process:\n");
    for(i = 0; i < n; i++){
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];
    }
    printf("Enter the Quantum time: ");
    scanf("%d", &qt);

    while(1){
        count = 0;  
        for(i = 0; i < n; i++){
            if(rem_bt[i] == 0){
                count++;
                continue;
            }
            if(rem_bt[i] > qt){
                sq += qt;
                rem_bt[i] -= qt;
            }else{
                sq += rem_bt[i];
                rem_bt[i] = 0;
                tat[i] = sq;  
            }
        }
        if(count == n)
            break;
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for(i = 0; i < n; i++){
        wt[i] = tat[i] - bt[i];
        awt += wt[i];
        atat += tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d\n", i+1, bt[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time = %.2f\n", awt/n);
    printf("Average Turnaround Time = %.2f\n", atat/n);
}


void SRTN(){
 int i,j,n,temp,pid[MAX],bt[MAX],wt[MAX],tat[MAX];
    float awt=0,atat=0;

    printf("Enter the number of procceses");
    scanf("%d",&n);

    printf("Enter the Process Id and Burst time of Processes");
    for(i=0;i<n;i++){
        scanf("%d %d",&pid[i],&bt[i]);
    }
    //sorting the processes according to burst time 
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(bt[j]>bt[j+1]){
                temp=bt[j];
                bt[j]=bt[j+1];
                bt[j+1]=temp;

                temp=pid[j];
                pid[j]=pid[j+1];
                pid[j+1]=temp;
            }
        }
    }
    printf("Process Id\tBurst Time\tWaiting time\tTurnaround Time\n");
    for(i=0;i<n;i++){
        wt[i]=0;
        tat[i]=0;
        for(j=0;j<i;j++){
            wt[i]=wt[i]+bt[j];
        }
        tat[i]=wt[i]+bt[i];
        awt=awt+wt[i];
        atat=atat+tat[i];

        printf("%d \t %d \t\t %d \t\t %d\n",pid[i],bt[i],wt[i],tat[i]);
    }
    printf("Average Waiting time %f",awt/n);
    printf("Average Turn Around time %f",atat/n);
    
}


int main(){
   
   //SRTN OR SJF
    //SRTN();
    //Round Robin
    Roundrobin();

    return 0;
}
