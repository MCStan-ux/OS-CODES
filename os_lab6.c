#include<stdio.h>

void lru(int p[], int n);
void optimal(int p[], int n);

int main() {
    int i, n, choice, p[20];

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the reference string: ");
    for(i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    printf("\nChoose Page Replacement Algorithm:\n");
    printf("1. LRU\n");
    printf("2. Optimal\n");
    printf("3. FIFO\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            lru(p, n);
            break;
        case 2:
            optimal(p, n);
            break;
        case 3:
            fifo(p,n);
            break;
        default:
            printf("Invalid choice!\n");
    }

    return 0;
}

void lru(int p[], int n) {
    int q[20], c1, c = 0, k = 0, b[20], c2[20], i, j, r, temp;

    q[k] = p[k];
    c++, k++;

    for(i = 1; i < n; i++) {
        c1 = 0;
        for(j = 0; j < k; j++) {
            if(p[i] != q[j]) {
                c1++;
            } else {
                break;
            }
        }

        if(c1 == k) {
            if(k < 3) {
                q[k] = p[i];
                k++;
            } else {
                for(j = 0; j < 3; j++) {
                    c2[j] = 0;
                    for(r = i-1; r >= 0; r--) {
                        if(q[j] != p[r]) {
                            c2[j]++;
                        } else {
                            break;
                        }
                    }
                }

                for(j = 0; j < 3; j++) {
                    b[j] = c2[j];
                }

                for(j = 0; j < 3; j++) {
                    for(r = j+1; r < 3; r++) {
                        if(b[j] < b[r]) {
                            temp = b[j];
                            b[j] = b[r];
                            b[r] = temp;
                        }
                    }
                }

                for(j = 0; j < 3; j++) {
                    if(c2[j] == b[0]) {
                        q[j] = p[i];
                        break;
                    }
                }
            }
            c++;
        }

        for(j = 0; j < k; j++) {
            printf("\t%d", q[j]);
        }
        printf("\n\n");
    }

    printf("The number of page faults (LRU) are %d\n", c);
}

void optimal(int p[], int n) {
    int q[20], c1, c = 0, k = 0, b[20], c2[20], i, j, r, temp;

    q[k] = p[k];
    c++, k++;

    for(i = 1; i < n; i++) {
        c1 = 0;
        for(j = 0; j < k; j++) {
            if(p[i] != q[j]) {
                c1++;
            } else {
                break;
            }
        }

        if(c1 == k) {
            if(k < 3) {
                q[k] = p[i];
                k++;
            } else {
                for(j = 0; j < 3; j++) {
                    c2[j] = 9999;
                    for(r = i+1; r < n; r++) {
                        if(q[j] == p[r]) {
                            c2[j] = r;
                            break;
                        }
                    }
                }

                for(j = 0; j < 3; j++) {
                    b[j] = c2[j];
                }

                for(j = 0; j < 3; j++) {
                    for(r = j+1; r < 3; r++) {
                        if(b[j] < b[r]) {
                            temp = b[j];
                            b[j] = b[r];
                            b[r] = temp;
                        }
                    }
                }

                for(j = 0; j < 3; j++) {
                    if(c2[j] == b[0]) {
                        q[j] = p[i];
                        break;
                    }
                }
            }
            c++;
        }

        for(j = 0; j < k; j++) {
            printf("\t%d", q[j]);
        }
        printf("\n\n");
    }


    printf("The number of page faults (Optimal) are %d\n", c);
}
void fifo(int p[], int n) {
    int q[3], count = 0, i, j = 0, k, avail;

    for(i = 0; i < 3; i++) {
        q[i] = -1;
    }

    for(i = 0; i < n; i++) {
        avail = 0; 
        for(k = 0; k < 3; k++) {
            if(q[k] == p[i]) {
                avail = 1; 
                break;
            }
        }
        if(avail == 0) {
            q[j] = p[i]; 
            j = (j + 1) % 3; 
            count++;
            for(k = 0; k < 3; k++) {
                printf("\t%d", q[k]);
            }
            printf("\n");
        }
    }

    printf("Total Page Faults (FIFO) = %d\n", count);
}