#include<stdio.h>
#include<stdlib.h>

/**
** 35.搜索插入位置
**/

/**
* 二分查找法
* 时间复杂度O(log n), 空间复杂度O(1)
* 执行用时分布 0 ms 击败 100.00% 使用 C 的用户 
* 消耗内存分布 5.90 MB 击败 25.48% 使用 C 的用户
*
**/ 
int searchInsert(int *nums, int numsSize, int target) {
    int low = 0; int high = numsSize - 1;
    int mid; 
    if( nums[high] < target ) { 
        return numsSize;
    } else if( nums[low] > target ) {
        return low;
    }

    while( low < high ) {
        // 根据题目要求，无需考虑数据溢出问题
        mid = (low + high) >> 1;

        if( target == nums[mid] ) {
            return mid;
        }
        else if( target > nums[mid] ) {
            low = mid + 1;
        }
        else if( target < nums[mid] ) {
            high = mid;
        }
    }
    return low;
}

int main(void) {
    int nums[4] = {1, 3, 5, 6};
    int target = 2;

    printf(" %d \n", searchInsert(nums, 4, target));
}
