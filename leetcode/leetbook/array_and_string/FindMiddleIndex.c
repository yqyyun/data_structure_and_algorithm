#include<stdio.h>


int findMiddleIndex(int *nums, int numsSize) {
    int l_sums[numsSize + 1];
    int l_sum = 0;

    for( int i = 0, j = 0; i < numsSize; ++i, ++j) {
        l_sums[j] = l_sum;
        l_sum +=nums[i];
    }

    l_sums[numsSize] = l_sum;

    for( int i = 1; i < numsSize + 1; ++i) {
        int r_sum = l_sum - l_sums[i];
        if( r_sum == l_sums[i - 1]) {
            return i - 1;
        }
    }
    return -1;
}

int main(void) {
    return 0;
}
        

