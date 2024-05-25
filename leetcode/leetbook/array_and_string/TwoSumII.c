#include<stdio.h>
#include<stdlib.h>

/**
*   167.两数之和Ⅱ - 输入有序数组 
*   <https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/description/>
**/

/**
*   方法一：双指针
*   遍历当前数组，取当前元素尾备选元素a，得target - a = b，在剩下的元素中查找b，
*   若找到直接返回两个下标。
*
*   时间复杂度 O(n²) 当遍历第i个元素时，需在剩下的 n - i 个元素中寻找b，因此总
*   循环次数为 n + (n - 1) + .. + 2 + 1 = n(n+1)/2 = O(n²)
*   空间复杂度O(1)
*
*
**/
int* twoSum_1(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* retNums = (int*)malloc(2*sizeof(int));
    for (int i = 0; i < numsSize; ++i) {
        int b = target - nums[i];
        for (int j = i + 1; j < numsSize; ++j) {
            if (b == nums[j]) {
                retNums[0] = i + 1;
                retNums[1] = j + 1;
                return retNums;
            }
        }
    }
    return retNums;
}
/**
* 方法一优化
*   在不减数组中
*   当向前或向后查找b = target - a元素时，是有一个明显的边界的。
*   当超出这一边界，是不可能找到b的。
*   比如，当从后 向前查找b时，当b > nums[j]时，是安全的，可以继续
*   向前查找，当b <= nums[j]时，就超出了边界。
*
*   执行用时分布 5 ms 击败 97.49% 使用 C 的用户
*   消耗内存分布 6.78 MB 击败 75.41% 使用 C 的用户   
**/
int* twoSum_1_impr1(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* retNums = (int*)malloc(2*sizeof(int));
    int k = numsSize - 1;
    for (int i = 0; i < numsSize; ++i) {
        int b = target - nums[i];
        for (int j = k; j > i; --j) {
            if (b == nums[j]) {
                retNums[0] = i+1;
                retNums[1] = j+1;
                return retNums;
            }
            else if (b >  nums[j]) {
                k = j;
                break;
            }
        }
    }
    return retNums;
}

/**
*   方法而：二分查找法
*   采用二分查找找到b = target - nums[i]
*
*   时间复杂度O(nlogn), 当遍历第i个元素时，需在剩下的n-i个元素中寻找b，因此
*   总循环次数为log₂n + log₂(n-1) + .. + log₂2 + 1 = log₂(n*(n-1)..2)..) + 1 = O(log₂n!) = O(nlogn)
*   空间复杂度O(1)
*
*   执行用时分布 16 ms 击败 5.31% 使用 C 的用户
*   消耗内存分布 6.75 MB 击败 86.82% 使用 C 的用户
*
**/
int* twoSum_2(int *numbers, int numbersSize, int target, int* returnSize) {
    *returnSize = 2;
    int * retNums = (int*)malloc(2*sizeof(int));
    for (int i = 0; i < numbersSize; ++i) {
        int b = target - numbers[i];
        int s = i + 1;
        int e = numbersSize - 1;
        while (s <= e) {
            int m = s + (e - s)/2;
            if (numbers[m] == b) {
                retNums[0] = i + 1;
                retNums[1] = m + 1;
                return retNums;
            }
            else if (numbers[m] < b) {
                s = m + 1;
            }
            else {
                e = m - 1;
            }
        }
    }
    return retNums;
}
    
/** 方法三 利用升序数组特性排除掉明显不可能符合条件的项。
** TODO
**/

int main(void) {
    //输入：numbers = [2,7,11,15], target = 9
    //输出：[1,2]
    int nums[4] = {2,7,11,15};
    return 0;
}

