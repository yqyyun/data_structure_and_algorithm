#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
*   Knuth-Morris-Pratt(KMP)算法
*   <https://leetcode.cn/leetbook/read/array-and-string/cm5e2/>
**/

int* buildNext(char* str) {
    int n = strlen(str);
    int* next = (int*)malloc(n * sizeof(int));
    int j = 0;
    int k = -1;
    next[0] = -1;
    while (j < (n - 1)) {
        if (k == -1 ||str[j] == str[k]) {
            ++k;++j;
            next[j] = k;
        }
        else {
            k = next[k];
        }
    }
    for (int i = 0; i < n; ++i) {
        printf("%d, ", next[i]);
    }
    printf("\n");
    return next;
}

//void buildNext(char* str, int* next);

int strStr(char* haystack, char* needle) {
    int m = strlen(haystack);
    int n = strlen(needle);
    int* next = buildNext(needle);
    int i = 0, j = 0;
    while (j < n && i < m) {
        if (j == -1 || haystack[i] == needle[j]) {
            ++i;++j;
        }
        else {
            j = next[j];
        }
    }
    free(next);
    if (j < n) {
        return -1;
    }
    return i - n;
}

int main(void) {
    //0
    char* haystack = "sadbutsad", *needle = "sad";
    // -1
    char* haystack1 = "leetcode", *needle1 = "leeto";
    printf("%d\n", strStr(haystack, needle));
    printf("%d\n", strStr(haystack1, needle1));
    return 0;
}
