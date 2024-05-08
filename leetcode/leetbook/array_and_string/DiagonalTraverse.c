#include<stdio.h>
#include<stdlib.h>


/**
* 498. 对角线遍历
* <https://leetcode.cn/problems/diagonal-traverse/description/>
*
**/

/**
* 方法一：边界校正、普通遍历，暴力检查。
*   对角线遍历时，x, y自增方向是相反的，要么x+1，y-1，要么x-1，y+1
*   使用一个方向变量表示x，y自增的方向。
*   其次在x或y即将突破边界时，对其进行归位校正，同时改变方向，即方向向量
*   变为相反数。
* 细节：在对角线处突破边界时，x和y会同时越界。经过分析验证发现在方向为正向
*   时（向右上方），先检查y边界，校正y，并改变方向向量时，再处理x，会直接
*   得到正确结果。
*   同时，方向为负方向时（向左下方），先检查x边界，校正x，并改变方向向量时，
*   再处理y，会直接得到正确结果。
*
* 时间复杂度O(mn) 空间复杂度O(1)
*
* 执行用时分布 68 ms 击败 68.58% 使用 C 的用户
* 消耗内存分布 13.96 MB 击败 84.96% 使用 C 的用户
**/
int* findDiagonalOrder(int** mat, int matSize, int* matColSize, int* returnSize) {
    int m = matSize;
    int n = matColSize[0];
    int m_1 = m - 1;
    int n_1 = n - 1;
    int rs = m * n;
    *returnSize = rs;
    int* ret = (int*)malloc(rs * sizeof(int));
    //TODO
    //direction x += d; y -= d;
    int d = -1;
    for (int i = 0, x = 0, y = 0; i < rs; ++i) {
        ret[i] = mat[x][y];
        if (d < 0) {
            // forward direction 
            if ((y -= d) > n_1) {
                y = n_1;
                d = -d;
            }
            if ((x += d) < 0) {
                x = 0;
                d = -d;
            }
        }
        else {
            // backward direction
            if ((x += d) > m_1) {
                x = m_1;
                d = -d;
            }
            if ((y -= d) < 0) {
                y = 0;
                d = -d;
            }
        }
    }

    return ret;
}


int main(void) {
    int** mat = (int**)malloc(3 * sizeof(int*));
    int m1[3] = {1,2,3};
    int m2[3] = {4,5,6};
    int m3[3] = {7,8,9};
    mat[0] = m1;
    mat[1] = m2;
    mat[2] = m3;
    int matColSize[3] = {3,3,3};
    int* returnSize = (int*)malloc(sizeof(int));
    int* ret = findDiagonalOrder((int**)mat, 3, matColSize, returnSize);
    for (int i = 0; i < *returnSize; ++i) {
        printf("%d ,", ret[i]);
    }
    return 0;
}
