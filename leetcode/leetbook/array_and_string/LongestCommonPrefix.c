#include<stdio.h>
#include<stdlib.h>

/**
*
*   14. 最长公共前缀
* <https://leetcode.cn/problems/longest-common-prefix/description/>
**/

/**
* 方法一：按列遍历
*   按列顺序遍历所有元素，在当前列存在和第一行元素不相同的字符，则查找停止，
*   否则，将当前列元素追加到返回字符数组末尾，继续下一列遍历。
*
*   时间复杂度O(n²) 空间复杂度O(1)
*
* 执行用时分布 0 ms 击败 100.00% 使用 C 的用户
* 消耗内存分布 5.63 MB 击败 56.92% 使用 C 的用户
**/
char* longestCommonPrefix(char** strs, int strsSize) {
    //题目要求 1 <= strs.length <= 200
    //         0 <= strs[i].length <= 200
    // strs[i]仅小写英文字母组成
    int maxSize = 200;
    char* prefixs = (char*)malloc(maxSize * sizeof(char));
    int prefixsSize = 0;
    for (int j = 0; strs[0][j] != '\0'; ++j) {
        // 从第二行开始判断是否和第一行相同
        int  i = 1;
        for (; i < strsSize && strs[i][j] != '\0'; ++i) {
            if (strs[i][j] != strs[0][j]) 
                break;
        }
        if (i == strsSize) {
            prefixs[prefixsSize++] = strs[0][j];
        }
        else {
            break;
        }
    }
        prefixs[prefixsSize] = '\0';
    return prefixs;
}       

/**
*   更具c风格的方法一：按列遍历
* 执行用时分布 0 ms 击败 100.00% 使用 C 的用户
* 消耗内存分布 5.54 MB 击败 74.85% 使用 C 的用户
**/
char* longestCommonPrefix_1(char** strs, int strsSize) {
    int maxSize = 200;
    char* cp = (char*)malloc(maxSize * sizeof(char));
    char* p = cp;
    
    char* str1 = *(strs+0);
    while(*str1 != '\0') {
        int i = 1;
        for (; i < strsSize; ++i) {
            int j = p - cp;
            char* c = (*(strs + i) + j);
            if (*c == '\0' || *c != *str1) 
                break;
        }
        if (i == strsSize) {
            *p++ = *str1++;
        }
        else {
            break;
        }
    }
    *p = '\0';
    return cp;
}

/** 
* 方法二：横向扫描
*   先得到S1和S2最长公共前缀，LCP(S1S2),在得到LCP(S1S2)和S3的最长公共前缀。
*   LCP(S₁S₂...Sn) = LCP(LCP(LCP(S₁,S₂),S₃)...Sn)
*
*  时间复杂度O(mn)，n是字符串平均长度 O(1);
* 执行用时分布 3 ms 击败 45.45% 使用 C 的用户
* 消耗内存分布 5.60 MB 击败 58.70% 使用 C 的用户
*
**/
char* longestCommonPrefix_2(char** strs, int strsSize) {
        int maxSize = 200;
        char* lcp = (char*)malloc(maxSize * sizeof(char));

        // 复制s1到lcp;
        char* s1 = strs[0];
        char* p = lcp;

        while((*p++=*s1++) != '\0');

        for (int i = 1; i < strsSize && *lcp !='\0'; ++i) {
            char* c = strs[i];
            char* p = lcp;
            while(*c != '\0' && *c == *p){
                c++;
                p++;
            }
            *p = '\0';
        }
        return lcp;
}

char* longestCommonPrefix_sub(char**, int, int);
char* commonPrefix(char* leftLcp, char* rightLcp);
/**
* 方法三：分治
*   LCP(S₁...Sn)  = LCP(S₁...Sk),LCP(Sk+1...Sn))
*   其中LCP(S₁...Sn)是字符串的最长公共前缀，1<k<n。
*
*   对问题LCP（Si...Sj)可以分解长两个子问题
*   LCP(Si...Smid)与LCP(Smid+1...Sj), 其中mid=(i+j)/2。
*   对两个子问题分别求解，然后对两个子问题的解计算最长公共前缀。
*
*   时间复杂度O(mn), m是字符串平均长度，n是字符串数量。
*   空间复杂度O(mlogn), m是字符串的平均长度，n是字符串数量.
*   空间复杂度主要取决于递归调用的层数，层数最大为logn,ie.log₂n，
*   每层需要m的空间存储返回结果。
*
* 执行用时分布 0 ms 击败 100.00% 使用 C 的用户
* 消耗内存分布 5.85 MB 击败 13.43% 使用 C 的用户
*
**/
char* longestCommonPrefix_3(char** strs, int strsSize) {
    if(NULL == strs) {
        return "";
    }
    return longestCommonPrefix_sub(strs, 0, strsSize - 1);
}  

char* longestCommonPrefix_sub(char** strs, int start, int end) {
    //printf("(%d, %d)\n", start, end);
    if (start == end) {
        return strs[start];
    }
    //int mid = start + (end - start)/2 ;
    // 根据题设，无需担心溢出
    int mid = (start + end) >> 1;
    char* leftLcp = longestCommonPrefix_sub(strs, start, mid);
    char* rightLcp = longestCommonPrefix_sub(strs, mid+1, end);
    return commonPrefix(leftLcp, rightLcp);

}

char* commonPrefix(char* leftLcp, char* rightLcp) {
    // 就地修改;
    //printf("lfetLcp = %s, rightLcp = %s\n", leftLcp, rightLcp);
    char* prefix = leftLcp;
    while (*leftLcp != '\0' && *rightLcp != '\0') {
        if (*leftLcp != *rightLcp) {
            break;
        }
        leftLcp++;
        rightLcp++;
    }
    // 由于是就地修改，若修改字符串常亮空间会导致段错误。
    *leftLcp = '\0';
    return prefix;
}

int main(void) {
    char* strs[2];
    //strs[0] = "ab";
    //strs[1] = "a";
    char strs1[2][3] = {{'a', 'b', '\0'}, {'a', '\0'}};
    strs[0] = strs1[0];
    strs[1] = strs1[1];
    char* p = longestCommonPrefix_3((char**)strs, 2);
    printf("*p = %s\n", p);
    return 0;
}
