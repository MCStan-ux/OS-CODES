#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   
#include <sys/wait.h> 

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for(i=0;i<n;i++){
        for(j=i;j<n;j++){
            if(arr[j]>arr[j+1]){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
    }


void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n, i;
    printf("Enter number of integers: ");
    scanf("%d", &n);

    int arr[n], arr_copy[n];

    printf("Enter integers:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        arr_copy[i] = arr[i]; // copy for child process
    }

    pid_t pid = fork(); // create a new process

    if (pid < 0) {
        printf("Fork failed!\n");
        return 1;
    }
    else if (pid == 0) {
        // Child Process
        printf("\n[Child] PID: %d, Parent PID: %d\n", getpid(), getppid());

        printf("[Child] Sorting array using Selection Sort...\n");
        selectionSort(arr_copy, n);

        printf("[Child] Sorted array: ");
        printArray(arr_copy, n);

        // Sleep to become Orphan (if parent finishes early)
        printf("[Child] Sleeping for 5 seconds to become orphan if parent exits early...\n");
        sleep(5);

        printf("[Child] After sleep, my parent PID is: %d\n", getppid()); // new parent should be init or systemd (PID 1)
        exit(0);
    }
    else {
        // Parent Process
        printf("\n[Parent] PID: %d, Child PID: %d\n", getpid(), pid);

        printf("[Parent] Sorting array using Bubble Sort...\n");
        bubbleSort(arr, n);

        printf("[Parent] Sorted array: ");
        printArray(arr, n);

        // Sleep to let child exit first and become Zombie
        printf("[Parent] Sleeping for 10 seconds to create zombie child...\n");
        sleep(10);

        int status;
        wait(&status); // Wait for child to terminate
        printf("[Parent] Child exited. Parent cleaning up.\n");
    }

    return 0;
}