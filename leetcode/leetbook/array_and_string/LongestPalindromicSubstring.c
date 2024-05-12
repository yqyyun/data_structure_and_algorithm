#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/**
*   5. 最长回文子串 Longest Palindromic Substring
*   <https://leetcode.cn/problems/longest-palindromic-substring/description/>
**/

/**
* 方法一：普通，暴力遍历, 由外向内。
*   1. 创建一个回文数组，以回文子串长度为下标存储对应的子串，显然最长为s.length。
*   2. 从开头开始遍历，以当前字符为子串起点，从后向前搜索相同字符作为子串终点。
*   判断子串substring(start, end) 是否是回文字符串，若是则存储到对应的回文数组，
*   直到遍历结束。
*
*   时间复杂度O(m²) m是字符串长度, 当遍历第i个位置时，start = i;搜索相同字符需要遍历(m-end)次, 
*   假设找到一次相同字符就是回文子串，则验证回文子串需要遍历(end - start)次，
*   则该次循环总计遍历(m - end + end - start) = (m -i)次。总体循环(m)+(m-1)+(m-2)+...+(1) = (m +1)m/2;
*   即时间复杂度为O(m²);
*   空间复杂度O(mn) m是字符串长度，子串的平均长度。
*   本函数为简化，直接令n = m，因此本函数空间复杂度O(m²)；
*
**/
bool isPalindrome(char* s, int start, int end);
// NOTE! 该函数内的代码存在很大问题，涉及到内存分配的许多细节。
//  可以作为一个不可多得的反面教材积累下来，故而保留了下来，
//  修正的代码在后面写出。
char* ERROR_longestPalindrome(char* s) {
    //就地返回子串，不另外存储子串。
    int length = 0;
    while (s[length] != '\0'){
        length++;
    }
    int size = length + 1;
    char* palindromes[size];
    for (int i = 0; i < size; ++i) {
        palindromes[i] = NULL;
    }

    for (int i = 0; i < length; ++i) {
        int j = length;
        do {
            while (--j > i && s[j] != s[i]);
            if (j == i) {
                continue;
            }
            if (isPalindrome(s, i, j)) {
                int pos = j - i + 1;
                // 末尾有个'\0'
                char pal[pos + 1];
                // ERROR
                palindromes[pos] = pal;
                printf("(%d, %d)\n", i, j);
                for (int k = pos-1; k > -1; --k,--j) {
                    pal[k] = s[j];
                }
                pal[pos] = '\0';
                printf("palindromes[%d] = %s\n", pos, pal);
                break;
            }
        } while(i < j);
    }
    for (int i = 0; i < size; ++i) {
        if (NULL != palindromes[i]) {
           // 输出结果不可预料。
           //一般为空字符串
           printf("%s\n", palindromes[i]);
        }
        else {
            printf("NULL\n");
        }
    }
    for (int i = length; i > 0; --i) {
        if (NULL != palindromes[i]) {
            // ERROR 
            return palindromes[i];
        }
    }
    //返回单个字符作为回文子串
    s[1] = '\0';
    return s;
}

bool isPalindrome(char* s, int start, int end) {
    //printf("(%d, %d)\n", start, end);
    while (start < end) {
        if (s[start++] != s[end--]) {
            //printf("%c,%c,false\n", s[start], s[end]);
            return false;
        }
    }
    //printf("true\n");
    return true;
}

/** 
* ERROR_longestPalindrome 函数修正的代码
**/
char* longestPalindrome(char* s) {
    int length = 0;
    while (s[length] != '\0'){
        length++;
    }
    int size = length + 1;
    char palindromes[size][size];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            palindromes[i][j] = 0;
        }
    }

    for (int i = 0; i < length; ++i) {
        int j = length;
        do {
            while (--j > i && s[j] != s[i]);
            if (j == i) {
                break;
            }
            if (isPalindrome(s, i, j)) {
                int pos = j - i + 1;
                for (int k = pos-1; k > -1; --k,--j) {
                    palindromes[pos][k] = s[j];
                }
//            printf("palindromes[%d] = %s\n", pos, palindromes[pos]);
                break;
            }
        } while(i < j);
    }
/**
    for (int i = 0; i < size; ++i) {
       printf("%s\n", palindromes[i]);
    }
**/
    for (int i = length; i > 0; --i) {
        if (palindromes[i][0] != 0) {
            char* lp = (char*)malloc(size * sizeof(char));
            char* plp = lp;
            char* src = palindromes[i];
            while((*plp++ = *src++) != '\0');
            return lp;
        }
    }
    //返回单个字符作为回文子串
    s[1] = '\0';
    return s;
}


int main(void) {
    char s1[] = {'c','b','b','d','\0'};
    char s2[] = {'b','a','b','a','d','\0'};
    char* rs1 = longestPalindrome(s1);
    char* rs2 = longestPalindrome(s2);
    printf("%s\n", rs1);
    printf("%s\n", rs2);
    return 0;
}
