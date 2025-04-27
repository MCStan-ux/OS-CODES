// parent.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void sort_array(int arr[], int n) {
    int i, j, temp;
    for (i=0; i<n-1; i++) {
        for (j=0; j<n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int n,i;
    printf("Enter the number of elements");
    scanf("%d",&n);
    int arr[n];
    printf("Enter the integers");
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }

    pid_t pid=fork();
    if(pid<0){
        printf("Fork Failed\n");
        exit(1);
    }else if(pid>0){
        wait(NULL);
    }else{
        sort_array(arr,n);
        char *args[n+2];
        args[0]="./child";
        for(i=0;i<n;i++){
            args[i+1]=(char*) malloc(10);
            sprintf(args[i+1],"%d",arr[i]);
        }
        args[n+1]=NULL;
        char* envp[]={NULL};
        execve("./child",args,envp);
        perror("Failed");
        exit(1);
    }

    return 0;
}
