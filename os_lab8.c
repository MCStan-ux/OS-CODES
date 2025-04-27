#include <stdio.h>
#include <stdlib.h>

void sstf(int request[], int n, int head);
void scan(int request[], int n, int head);
void clook(int request[], int n, int head);

int main() {
    int n, request[20], head, choice, i;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the request queue: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    printf("\nChoose Disk Scheduling Algorithm:\n");
    printf("1. SSTF\n");
    printf("2. SCAN\n");
    printf("3. C-LOOK\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            sstf(request, n, head);
            break;
        case 2:
            scan(request, n, head);
            break;
        case 3:
            clook(request, n, head);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

void sstf(int request[], int n, int head) {
    int completed[20] = {0}, i, index, count = 0;
    int total_movement = 0, min, distance, pos = head;

    printf("\nSSTF Disk Scheduling:\n");

    while(count < n) {
        min = 9999;
        for(i = 0; i < n; i++) {
            if(!completed[i]) {
                distance = abs(pos - request[i]);
                if(distance < min) {
                    min = distance;
                    index = i;
                }
            }
        }
        completed[index] = 1;
        total_movement += abs(pos - request[index]);
        printf("Move from %d to %d\n", pos, request[index]);
        pos = request[index];
        count++;
    }

    printf("Total head movement: %d\n", total_movement);
}

void scan(int request[], int n, int head) {
    int i, j, temp, total_movement = 0, pos = head;
    int disk_size = 199; 
    int arr[20];

    for(i = 0; i < n; i++) {
        arr[i] = request[i];
    }
    arr[n] = head;
    n++;

    for(i = 0; i < n; i++) {
        for(j = i+1; j < n; j++) {
            if(arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    
    for(i = 0; i < n; i++) {
        if(arr[i] == head) {
            break;
        }
    }

    printf("\nSCAN Disk Scheduling (Moving towards higher cylinder numbers):\n");

    for(j = i; j < n; j++) {
        printf("Move from %d to %d\n", pos, arr[j]);
        total_movement += abs(pos - arr[j]);
        pos = arr[j];
    }
  
    if(pos != disk_size) {
        printf("Move from %d to %d (End)\n", pos, disk_size);
        total_movement += abs(pos - disk_size);
        pos = disk_size;
    }
   
    for(j = i-1; j >= 0; j--) {
        printf("Move from %d to %d\n", pos, arr[j]);
        total_movement += abs(pos - arr[j]);
        pos = arr[j];
    }

    printf("Total head movement: %d\n", total_movement);
}

void clook(int request[], int n, int head) {
    int i, j, temp, total_movement = 0, pos = head;
    int arr[20];

    for(i = 0; i < n; i++) {
        arr[i] = request[i];
    }
    arr[n] = head;
    n++;

    for(i = 0; i < n; i++) {
        for(j = i+1; j < n; j++) {
            if(arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    for(i = 0; i < n; i++) {
        if(arr[i] == head) {
            break;
        }
    }

    printf("\nC-LOOK Disk Scheduling (Moving towards higher cylinder numbers):\n");

    for(j = i; j < n; j++) {
        printf("Move from %d to %d\n", pos, arr[j]);
        total_movement += abs(pos - arr[j]);
        pos = arr[j];
    }
    if(i != 0) {
        printf("Jump from %d to %d\n", pos, arr[0]);
        total_movement += abs(pos - arr[0]);
        pos = arr[0];
    }
    for(j = 0; j < i; j++) {
        printf("Move from %d to %d\n", pos, arr[j]);
        total_movement += abs(pos - arr[j]);
        pos = arr[j];
    }

    printf("Total head movement: %d\n", total_movement);
}