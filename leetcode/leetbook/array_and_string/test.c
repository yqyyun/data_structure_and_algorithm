#include<stdio.h>
#include<stdlib.h>

int compare(const void* e1, const void* e2) {
    return **(int**)e1 - **(int**)e2;
}

int main(void) {
    int** arr = (int**)malloc(4 * sizeof(int*));

    arr[0] = (int*)malloc(sizeof(int) * 2);
    arr[1] = (int*)malloc(sizeof(int) * 2);
    arr[2] = (int*)malloc(sizeof(int) * 2);
    arr[3] = (int*)malloc(sizeof(int) * 2);
    
    arr[0][0] = 106; arr[0][1] = 123;
    arr[1][0] = 318; arr[1][1] = 325;
    arr[2][0] = 27; arr[2][1] = 37;
    arr[3][0] = 95; arr[3][1] = 106;

    qsort(arr, 4 * sizeof(int*), sizeof(int*), compare);

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%d, ", arr[i][j]);
        }
        printf("\n");
    }
    return 0;
}
