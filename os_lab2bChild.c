// child.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Array in reverse order:\n");
   // printf("%d\n",argc);
    for (int i = argc - 1; i >= 1; i--) { // argv[0] is program name
        printf("%s ", argv[i]);
    }
    printf("\n");
    return 0;
}