#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

/**
*   27.移除元素 Remove Element
*   <https://leetcode.cn/problems/remove-element/>
**/

/**
*   方法一：双指针
*
**/
int removeElement(int*nums,int numsSize, int val) {
    int k = numsSize;
    for (int i = 0, j = 0; i < numsSize; ++i) {
        while (j < numsSize && nums[j++] == val) {
            --k;
        }
        if (j == numsSize) {
            break;
        }
        // remove element
        nums[i] = nums[j];
    }

    return k;
}

/**
*   方法二：快慢指针
*
**  初始化一个快指针，一个慢指针，快指针每次移动一步，
**  而slow只有当fast指向的值不等于目标val值时，才移动一步。
*   时间复杂度 O(n)
*   空间复杂度O(1)
**/
int removeElement_2(int* nums, int numsSize, int val) {
    int fast = 0;
    int slow = 0;
    for (; fast < numsSize; ++fast) {
        if (nums[fast] != val) {
            nums[++slow] = nums[fast];
        }
    }
    return slow;
}

/**
*   方法二优化
*   
*   如果要移除的元素在数组的开头，例如[1,2,3,4,5], 当val=1时
*   我们需要把每一个元素都左移一位。题目说：【元素的顺序可以
*   改变】。实际上我们可以直接把最后一个元素5移动到数组开头，
8   取代元素1，得到[5,2,3,4]，同样满足题目要求。这个优化在val
*   元素数量非常少时非常有效。
*   
*   算法：
*   如果左指针left指向的元素等于val，此时将右指针right指向的元素
*   复制到左指针left的位置，然后right左移一位。如果复制过来的元素
*   恰好还等于val，可以继续把right指向的元素复制过来。
*   若左指针left指向的元素不等于val，则left右移一位。
*   当left和right重合的时候，左右指针遍历完所有元素。
*
*   时间复杂度O(n),空间复杂度O(1)
*
**/
int removeElement_2_impr1(int * nums, int numsSize, int val) {
    int left = 0;
    int right = 0;
    while ( left <= right) {
        if (nums[left] == val) {
            nums[left] = nums[right];
            --right;
        }
        else {
            ++left;
        }
    }
    return left;
}

int main(void) {
    int nums[4] = {3,2,2,3};
    int expectedNums[2] = {2,2};
    int k = removeElement_2(nums, 4, 3);
    assert(k == 2);
    nums[0] = nums[1] = 2;
    for (int i = 0; i < k; i++) {
        assert(nums[i] == expectedNums[i]);
    }
    return 0;
}
