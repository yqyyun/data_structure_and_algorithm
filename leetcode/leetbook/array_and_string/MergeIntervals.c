#include<stdio.h>
#include<stdlib.h>

/**
* 56. 合并区间 
* <https://leetcode.cn/problems/merge-intervals/description/>
*
**/

int compare(const void* e1, const void* e2) {
    return ((*(int**)e1)[0] - (*(int**)e2)[0]);
}

/**
* 方法一: 暴力遍历
* 遍历每一个区间元素，将其与剩下所有还未被合并的区间元素合并。合并到所有区间元素
* 都无法再合并时为止。
*
*   时间复杂度O(n²) ie. O(n^2)， 空间复杂度O(n)。
*   
*  执行用时分布 617 ms 击败 5.01% 使用 C 的用户
*  消耗内存分布 60.76 MB 击败 5.00% 使用 C 的用户
*
**/
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, 
    int** returnColumnSizes) {
    //returnSize = (int*)malloc(sizeof(int));
    int row = intervalsSize;
    //intervals[i].length == 2;
    int col = intervalsColSize[0];

    int ret_row = 0;

    //flag pointer 在堆中分配，若不考虑栈溢出可以考虑在栈内分配。
    int* flags = (int*)calloc(row, row * sizeof(int));
    //flag pointer 在栈内分配, 在栈内分配性能有提升，609 ms 击败 5.05% 使用 C 的用户 
    //int flags[row];
    //for (int i = 0; i < row; ++i) {
        //flags[i] = 0;
    //}
    int** returnIntervals = (int**)malloc(row * sizeof(int*));

    for(int i = 0; i < row; ++i) {
        // 过滤已经合并的区间元素
        if( flags[i] ) {
            continue;
        }
        flags[i] = 1;

        int left_1, left_2, right_1, right_2, merge_1, merge_2;

         merge_1 = intervals[i][0];
         merge_2 = intervals[i][1];


        for(int j = i + 1; j < row; ++j) {
            if( flags[j] ) {
                continue;
            }
            if( merge_1 < intervals[j][0] ) {
                left_1 = merge_1;
                left_2 = merge_2;
                right_1 = intervals[j][0];
                right_2 = intervals[j][1];
            }
            else {
                left_1 = intervals[j][0];
                left_2 = intervals[j][1];
                right_1 = merge_1;
                right_2 = merge_2;
            }
            // 左区间右端点可能处在3个位置之一，右区间左边，右区间内，右区间右边
            if( left_2 < right_1 ) {
                ;
            }
            else if( left_2 < right_2 ) {
                merge_1 = left_1;
                merge_2 = right_2;

                flags[j] = 1;
            }
            else {
                merge_1 = left_1;
                merge_2 = left_2;

                flags[j] = 1;
            }

        }

        int flag = 0;
        // 与returnIntervals中的区间元素合并，避免重复
        for (int j = 0; j < ret_row; ++j) {
            if (merge_1 < returnIntervals[j][0]) {
                left_1 = merge_1;
                left_2 = merge_2;
                right_1 = returnIntervals[j][0];
                right_2 = returnIntervals[j][1];
            }
            else {
                left_1 = returnIntervals[j][0];
                left_2 = returnIntervals[j][1];
                right_1 = merge_1;
                right_2 = merge_2;
            }
            // 左区间右端点可能处在3个位置之一，右区间左边，右区间内，右区间右边
            if( left_2 < right_1 ) {
                continue;
            }
            else if( left_2 < right_2 ) {
                merge_1 = left_1;
                merge_2 = right_2;

            }
            else {
                merge_1 = left_1;
                merge_2 = left_2;
            }
            returnIntervals[j][0] = merge_1;
            returnIntervals[j][1] = merge_2;
            flag = 1;

        }
       if (!flag) {
            returnIntervals[ret_row] = (int*)malloc(col * sizeof(int));
            returnIntervals[ret_row][0] = merge_1;
            returnIntervals[ret_row][1] = merge_2;
            ++ret_row;
       }
    }

    // 模版代码
    *returnSize = ret_row;

    *returnColumnSizes = (int*)malloc((*returnSize) * sizeof(int));

    for(int i = 0; i < *returnSize; ++i) {
        (*returnColumnSizes)[i] = col;
    }
    // qsort(returnIntervals, ret_row, sizeof(int*), compare);

    // returnIntervals中还存在可以互相合并的区间，因此递归调用直到不存在可以合并的区间为止。
    if (row == ret_row) {
        return returnIntervals;
    }
    return merge(returnIntervals, ret_row, intervalsColSize, returnSize, returnColumnSizes);
    // return returnIntervals;
    
}

/**
* 方法一改进：直接使用递归方式合并还未被合并的区间元素，删掉与returnIntervals合并去重的循环。性能提升一倍
* 时间复杂度和空间复杂度同上。
* 执行用时分布 347 ms 击败 8.50% 使用 C 的用户 消耗内存分布 12.22 MB 击败 59.82% 使用 C 的用户
*
**/
int** merge_0(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, 
    int** returnColumnSizes) {
    //returnSize = (int*)malloc(sizeof(int));
    int row = intervalsSize;
    //intervals[i].length == 2;
    int col = intervalsColSize[0];

    int ret_row = 0;

    //flag pointer 在堆中分配，若不考虑栈溢出可以考虑在栈内分配。
    int* flags = (int*)calloc(row, row * sizeof(int));
    //flag pointer 在栈内分配
    //int flags[row];
    //for (int i = 0; i < row; ++i) {
     //   flags[i] = 0;
    //}

    int** returnIntervals = (int**)malloc(row * sizeof(int*));

    for(int i = 0; i < row; ++i) {
        // 过滤已经合并的区间元素
        if( flags[i] ) {
            continue;
        }
        flags[i] = 1;

        int left_1, left_2, right_1, right_2, merge_1, merge_2;

         merge_1 = intervals[i][0];
         merge_2 = intervals[i][1];


        for(int j = i + 1; j < row; ++j) {
            if( flags[j] ) {
                continue;
            }
            if( merge_1 < intervals[j][0] ) {
                left_1 = merge_1;
                left_2 = merge_2;
                right_1 = intervals[j][0];
                right_2 = intervals[j][1];
            }
            else {
                left_1 = intervals[j][0];
                left_2 = intervals[j][1];
                right_1 = merge_1;
                right_2 = merge_2;
            }
            // 左区间右端点可能处在3个位置之一，右区间左边，右区间内，右区间右边
            if( left_2 < right_1 ) {
                ;
            }
            else if( left_2 < right_2 ) {
                merge_1 = left_1;
                merge_2 = right_2;

                flags[j] = 1;
            }
            else {
                merge_1 = left_1;
                merge_2 = left_2;

                flags[j] = 1;
            }

        }

        returnIntervals[ret_row] = (int*)malloc(col * sizeof(int));
        returnIntervals[ret_row][0] = merge_1;
        returnIntervals[ret_row][1] = merge_2;
        ++ret_row;
    }

    // 模版代码
    *returnSize = ret_row;

    *returnColumnSizes = (int*)malloc((*returnSize) * sizeof(int));

    for(int i = 0; i < *returnSize; ++i) {
        (*returnColumnSizes)[i] = col;
    }
    // qsort(returnIntervals, ret_row, sizeof(int*), compare);

    // returnIntervals中还存在可以互相合并的区间，因此递归调用直到不存在可以合并的区间为止。
    if (row == ret_row) {
        return returnIntervals;
    }
    return merge(returnIntervals, ret_row, intervalsColSize, returnSize, returnColumnSizes);
    // return returnIntervals;
    
}
int main(void) {
    return 0;
}
