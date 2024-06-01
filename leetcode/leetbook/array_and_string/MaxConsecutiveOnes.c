#include<stdio.h>
#include<stdlib.h>

/**
*   485.最大连续1的个数Max Consecutive Ones
*   <https://leetcode.cn/problems/max-consecutive-ones/description/>
**/

/**
*   方法一：双指针
*   思路：使用快慢指针分别记录窗口的起始边界和结束边界
*   其中左边界包含，右边界不包含。
*   算法：
*       初始化一个快指针fast，一个满指针slow，快指针每次移动一步，
*       慢指针只有当快指针fast指向位置的元素为0时，才会移动。
*       并将满指针移动到fast下一个位置（左闭）。
*       在移动之前需要记录当前窗口的长度，并更新最大窗口长度。
*       
*       在遍历结束后，还需要更新一次最大窗口长度，因为最后一个元素很有可能为1
*       但因为fast == numsSize而退出了循环，最后一次长度没有更新。
*   
*   时间复杂度O(n) 空间复杂度O(1)
*
**/
int findMaxConsecutiveOnes(int *nums, int numsSize) {
    int max = 0;
    // [slow, fast)，左闭右开的窗口
    int slow = 0;
    int fast = 0;
    for (; fast < numsSize; ++fast) {
        if (nums[fast] == 0) {
            if (max < fast - slow) {
                max = fast - slow;
            }
            slow = fast + 1;
        }
    }
    if (max < numsSize - slow) {
        max = numsSize - slow;
    }
    return max;
}

int main(void) {
    //3
    int nums[] = {1,1,0,1,1,1};
    printf("%d\n",findMaxConsecutiveOnes(nums, 6));
    return EXIT_SUCCESS;
}
