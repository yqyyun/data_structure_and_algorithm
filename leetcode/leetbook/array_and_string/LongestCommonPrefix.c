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

int main(void) {
    char* strs[2];
    strs[0] = "ab";
    strs[1] = "a";
    char* p = longestCommonPrefix_2((char**)strs, 2);
    printf("*p = %s\n", p);
    return 0;
}
