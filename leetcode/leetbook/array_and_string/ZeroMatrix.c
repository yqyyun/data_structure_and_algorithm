#include<stdio.h>
#include<stdlib.h>

/**
* 零矩阵
* <https://leetcode.cn/problems/set-matrix-zeroes/description/>
* <https://leetcode.cn/problems/zero-matrix-lcci/>
*
**/


/**
* 方法一：
*   1. 使用一个mxn的二维数组zeroes，初始化为0，遍历matrix若(i,j)元素值为0，
*       则将zeroes对应位置设置为1（或一个非零值）。
*   2. 遍历zeroes数组，若(i,j)元素值为1，，
*       则将matri对应行和列全部设置为0。
*  
*   时间复杂度O(2mn) 简化为O(n²)
*   空间复杂度O(mn)
*
* 执行用时分布 42 ms 击败 26.42% 使用 C 的用户
* 消耗内存分布 10.38 MB 击败 98.30% 使用 C 的用户
*
*
**/
void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    int m = matrixSize;
    // 列值相同
    int n = matrixColSize[0];
    
    // 变长数组
    int zeroes[m][n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            zeroes[i][j] = 0;
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!matrix[i][j]) 
                zeroes[i][j] = 1;
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (zeroes[i][j]) {
                for (int c = 0; c < n; ++c) {
                    matrix[i][c] = 0;
                }
                for (int r = 0; r < m; ++r) {
                    matrix[r][j] = 0;
                }
            }
        }
    }

}

/**
* 方法二：
*   方法一的改进，使用O(m + n)的额外空间。
*   分别申请一个m大小和一个n大小的数组。rowZeroes[m]和colZeroes[n]分别代表对应行
*   和对应列是否出现了0，若出现则将对应数组设置为1；
*
*  时间复杂度O(n²), 空间复杂度O(m + n)
*
*  执行用时分布 37 ms 击败 74.43% 使用 C 的用户 
*  消耗内存分布 10.57 MB 击败 56.25% 使用 C 的用户 *
**/
void setZeroes_0(int** matrix, int matrixSize, int* matrixColSize) {
   int m = matrixSize;
   int n = matrixColSize[0];

   //变长数组 栈分配
   int rowZeroes[m];
   int colZeroes[n];
   for (int i = 0; i < m; ++i)
        rowZeroes[i] = 0;
   for (int j = 0; j < n; ++j)
        colZeroes[j] = 0;

   // 堆分配
   //int* rowZeroes = (int*)calloc(m, sizeof(int));
   //int* colZeroes = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!matrix[i][j]) {
                rowZeroes[i] = 1;
                colZeroes[j] = 1;
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        if (rowZeroes[i]) {
            for (int c = 0; c < n; ++c) {
                matrix[i][c] = 0;
            }
        }
    }
    for (int j = 0; j < n; ++j) {
        if (colZeroes[j]) {
            for (int r = 0; r < m; ++r) {
                matrix[r][j] = 0;
            }
        }
    }
}

int main(void) {
    return 0;
}
