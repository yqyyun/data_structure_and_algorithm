#include<stdio.h>
#include<stdlib.h>

/**
* 48. 旋转图像
*  <https://leetcode.cn/problems/rotate-image/description/>
*
**/

void swap_0(int* a, int* b) {
    int tem = *a;
    *a = *b;
    *b = tem;
}

void swap_1(int* a, int* b) {
    //异或交换
    *a = (*a) ^ (*b);
    *b = (*a) ^ (*b);
    *a = (*a) ^ (*b);
}

void swap_2(int* a, int* b) {
    //求和交换，注意避免溢出
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}


/**
* 
* 方法一： 先按照主对角线对折，再按照[n/2]位置对折
* 1. 主对折：a[i][j] <=> a[j][i], i ≠ j , i ∈ [0, n), j ∈  [0, i), 
*      i > j 或 j > i
* 2. [n/2]对折：a[i][j] <=> a[i][n-j-1] i ∈ [0, n], j ∈ [0, [n/2])
*
*  时间复杂度: 1. 主对折 遍历n*n/2个元素 2. 对折 遍历n*n/2个元素 
*       时间复杂度为O(n²)
*  空间复杂度O(1)
*
* 执行用时分布 0 ms 击败 100.00% 使用 C 的用户 
* 消耗内存分布 6.14 MB 击败 26.05% 使用 C 的用户 
*
**/
void rotate(int** matrix, int matrixSize, int* matrixColSize) {
    int n = matrixSize;
    // n2 = n / 2;
    int n2 = n >> 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            swap_0(&matrix[i][j], &matrix[j][i]);
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n2; ++j) {
            swap_0(&matrix[i][j], &matrix[i][n-j-1]);
        }
    }
}

int main(void) {
    return 0;
}
