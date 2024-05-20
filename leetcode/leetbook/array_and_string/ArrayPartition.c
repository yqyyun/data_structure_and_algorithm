#include<stdio.h>
#include<stdlib.h>

/**
*   561.数组拆分Array Partition
*   <https://leetcode.cn/problems/array-partition/description/>
**/

/**
*   方法一：排序法
*   将数组从小到大排序，再将偶数位置上的数字相加即可。
*   
*   时间复杂度：O(nlogn + n)
*   时间复杂度主要取决于排序算法的时间复杂度。
*   空间复杂度O(1)
*
*   执行用时分布 72 ms 击败 61.03% 使用 C 的用户
*   消耗内存分布 8.15 MB 击败 55.16% 使用 C 的用户
*
**/   
int i_comp(const void * a, const void * b) {
    return *(int*)a - *(int*)b;
}
int arrayPairSum(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), i_comp);
    int sum = 0;
    for (int i = 0; i < numsSize; i += 2) {
        sum += nums[i];
    }
    return sum;
}

int main(void) {
    int n1[4] = {1,4,3,2};
    int n2[6] = {6,2,6,5,1,2};
    printf("%d\n", arrayPartition(n1, 4));
    printf("%d\n", arrayPartition(n2, 6));
    return EXIT_SUCCESS;
}
