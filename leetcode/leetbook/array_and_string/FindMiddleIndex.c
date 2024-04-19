#include<stdio.h>
#include<stdlib.h>

/**
* 1991. 找到数组的中间位置
**/

/**
*前缀和，使用数组保存前缀和，避免第二次遍历时重复计算前缀和。
* 时间复杂度O(n), 空间复杂度O(n)
*
**/
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

/**
* 将变长数组改为动态内存分配，c11 -> c99
*
* 前缀和：时间复杂度O(n)，空间复杂度O(n)
*
* 执行用时分布0ms 击败100.00%使用 C 的用户
* 消耗内存分布5.83MB击败17.49%使用 C 的用户

*   Change variable-arrays to dynamically allocate memory, c11 -> c99.
**/
int findMiddleIndex_0(int *nums, int numsSize) {
    int *l_sums = (int*)malloc((numsSize + 1) * sizeof(int));

    int l_sum = 0;

    for( int i = 0; i < numsSize; ++i) {
        l_sums[i] = l_sum;
        l_sum += nums[i];
    }

    // l_sum = total
    l_sums[numsSize] = l_sum;

    for( int i = 1; i <= numsSize; ++i) {
        if (l_sum - l_sums[i] == l_sums[i-1]) {
            return i - 1;
        }
    }
    return -1;
}

/**
* 前缀和：不使用数组保存中间计算结果。前缀和会被计算两次。
* if L == R then
*   L + M = R + M = total - L
* so L + M = total - L ie.
* ` L * 2 = total - M `
*  
* l_sum + nums[i] = total - l_sum
* 时间复杂度O(n)，空间复杂度O(1)
*
* 执行用时分布 0 ms 击败 100.00% 使用 C 的用户
* 消耗内存分布 5.62 MB 击败 63.05%使用 C 的用户
* 
**/
int findMiddleIndex_1(int *nums, int numsSize) {
    int total = 0;
    int prefix_sum = 0;

    for(int i = 0; i < numsSize; ++i) {
        // 隐含了中间结果前缀和的计算。
        total += nums[i];
    }

    for(int i = 0; i < numsSize; ++i) {
        // L * 2 = total - M 
        if( prefix_sum * 2 == total - nums[i]) {
            return i;
        }
        // again，再次计算前缀和
        prefix_sum += nums[i];
    }

    return -1;
}

int main(void) {
    return 0;
}
        

