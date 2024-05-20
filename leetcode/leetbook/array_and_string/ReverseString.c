#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
*   344.反转字符串Reverse String
*   <https://leetcode.cn/problems/reverse-string/description/>
**/
void swap_1(char* a, char* b) {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
}
void swap_2(char* a, char* b) {
    char t = *a;
    *a = *b;
    *b = t;
}

void reverseString(char* s, int sSize) {
    int i = 0;
    int j = sSize - 1;
    while(i < j) {
        swap_2(s + i, s + j);
        i++;
        j--;
    }
}

void print(char* s, int sSize) {
    printf("[");
    for (int i = 0; i < sSize; ++i) {
        printf("%c, ", s[i]);
    }
    printf("]");
}

int main(void) {
    char s1[5] = {"h","e","l","l","o"};
    char s2[6] = {"H","a","n","n","a","h"};
    reverseString(s1, 5);    
    reverseString(s2, 6);    
    print(s1, 5);
    print(s2, 6);

    return 0;
}


