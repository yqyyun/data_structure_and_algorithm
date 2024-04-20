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
*
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

/**
* 方法二：有序合并
* 一、先将区间元素，按照区间左端点从小到大的顺序排列。
* 二、遍历有序区间元素，将当前区间右端点依次与右边其它区间元素右端点相比较，找到第一个比当前区间元素大的
*       区间元素，称之为边界区间元素。
* 三、判断当前元素处在边界区间元素的哪个位置，必定是3个位置之一，边界区间左边，边界区间内，边界区间右边。
*       根据判断结果进行合并。
* 
*   分析：排序算法使用的是快速排序，时间复杂度为O(nlogn), 然后遍历数组，需要n次遍历，时间复杂度为O(n)
*       因此时间复杂度是O(nlogn) + O(n) 最终为O(nlogn)
*       空间复杂度为O(1)
*
* 执行用时分布 41 ms 击败 99.38% 使用 C 的用户 
* 消耗内存分布 11.88 MB 击败 84.75% 使用 C 的用户
*
**/
int** merge_1(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, 
    int** returnColumnSizes) {
    //returnSize = (int*)malloc(sizeof(int));
    int row = intervalsSize;
    //intervals[i].length == 2;
    int col = intervalsColSize[0];

    int ret_row = 0;

    int** returnIntervals = (int**)malloc(row * sizeof(int*));

    qsort(intervals, row, sizeof(int*), compare);

    for (int i = 0; i < row; ) {
        returnIntervals[ret_row] = (int*)malloc(col * sizeof(int));
        //当前区间左端点
        returnIntervals[ret_row][0] = intervals[i][0];
        //当前区间右端点
    cur_loop:
        int cur_1 = intervals[i][1];

        //找到边界区间元素。
        while (++i < row && cur_1 >= intervals[i][1]); 
        
        if (i == row || cur_1 < intervals[i][0]) {
            // 当前区间右端点没有发生变化，说明右边不可能存在可以合并的元素了，
            // 更新元素到结果数组后，进行下一轮迭代合并。
            returnIntervals[ret_row][1] = cur_1;
        }
        else {
            //当区间右端点更新为新值时，右边可能还存在可以合并的元素，
            //按照相同的逻辑继续找下一个边界元素并合并。
            goto cur_loop;
        }
        ++ret_row;
    }
    
    // 模版代码
    *returnSize = ret_row;

    *returnColumnSizes = (int*)malloc((*returnSize) * sizeof(int));

    for(int i = 0; i < *returnSize; ++i) {
        (*returnColumnSizes)[i] = col;
    }

    return returnIntervals;
}

/**
* 方法二另一种实现：取消goto语句，并就地修改数组，不申请新内存空间
* 
* 
**/
int** merge_2(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, 
    int** returnColumnSizes) {
    //returnSize = (int*)malloc(sizeof(int));
    int row = intervalsSize;
    //intervals[i].length == 2;
    int col = intervalsColSize[0];

    int ret_row = 0;

    int** returnIntervals = (int**)malloc(row * sizeof(int*));

    qsort(intervals, row, sizeof(int*), compare);

    //指向当前区间元素或上一次合并的元素（用于合并右边剩余潜在区间）
    int* pre = NULL;

    for (int i = 0; i < row; ++i) {
        if (pre == NULL || pre[1] < intervals[i][0]) {
            //右边不存在可以合并的区间元素了，存入返回数组，开始新一轮迭代
            pre = intervals[i];
            returnIntervals[ret_row++] = pre;

            for (int j = i + 1; j < row; ++j) {
                //优化：因为0 <= start(i) <= end(i) <= 10⁴
                // 所以若pre[1] < intervals[j][0]则后续无需再判断了，可直接中止循环。
                if (pre[1] < intervals[j][0]) {
                    break;
                }
               if (pre[1] >= intervals[j][0] && 
                    pre[1] < intervals[j][1]) {
                        pre[1] = intervals[j][1];
                }
            }
        }

    }
    
    // 模版代码
    *returnSize = ret_row;

    *returnColumnSizes = (int*)malloc((*returnSize) * sizeof(int));

    for(int i = 0; i < *returnSize; ++i) {
        (*returnColumnSizes)[i] = col;
    }

    return returnIntervals;
}
int main(void) {
    return 0;
}
