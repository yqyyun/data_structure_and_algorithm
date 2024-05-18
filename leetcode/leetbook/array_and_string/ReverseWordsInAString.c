#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
* 151. 反转字符串中的单词 Reverse Words in a String
* <https://leetcode.cn/problems/reverse-words-in-a-string/description/>
*
**/

/**
* 方法一：常规法，数组中转法
*   先通过遍历将字符串按照单词分割保存到字符串数组中，在按照倒序从字符串数组中
*   读出即可。
*   如何算一个单词呢？
*       由字母开头由空格结束为一个单词。
*
*   时间复杂度O(m + n)，其中m是字符串的长度，n是单词的个数，最终时间复杂度为O(n);
*   空间复杂度O(n), n是单词的个数
*   
* 执行用时分布 2 ms 击败 69.32% 使用 C 的用户
* 消耗内存分布 6.25 MB 击败 27.43% 使用 C 的用户
**/
char* reverseWords_1(char* s) {
    //字符串数组，大小为n，n不用太精确，就等于空格数加1即可。
    int n = 0;
    char* p = s;
    while(*p != '\0') {
        if (*p == ' ') {
            ++n;
        }
        ++p;
    }
    ++n;
    char* words[n];
    //需返回的字符串长度
    int len = 0;
    char** wp = words;
    for (p = s; *p != '\0'; ++p) {
        //1. 先找到一个字母
        char* ws = p;
        while(*ws != '\0' && *ws == ' '){
            ++ws;
        }
        //2. 找后面的第一个空格
        char* we = ws;
        while(*we != '\0' && *we != ' ') {
            ++we;
        }
        if (ws != we) {
            len += we - ws + 1;
            //有效值
            *wp = ws;
            wp++;
            if (*we == '\0') {
                break;
            }
            *we = '\0';
            p = we;
        } 
        else {
            break;
        }
        
    }
    //返回字符串
    char* rs = (char*)malloc(len * sizeof(char));
    //倒序读出
    p = rs;
    while(--wp >= words) {
        char* c = *wp;
        while((*p++ = *c++) !='\0');
        //将'\0'换成' '
        *(p-1) = ' ';
    }
    //最后一个' ' 换成'\0'
    *(p -1) = '\0';
    return rs;
}

/**
* 方法二：倒序遍历
*   思路：倒序遍历空格，正向遍历字符。
*   
*   时间复杂度O(m + n) m是字符串长度，n是所有单词总长度。
*
*   执行用时分布 1 ms 击败 73.97% 使用 C 的用户
*   消耗内存分布 6.26 MB 击败 21.48% 使用 C 的用户 
*/
char* reverseWords_2(char* s) {
    int len = 0;
    char* p = s;
    //s中至少存在一个单词 s.length >= 1
    while(*(++p) != '\0') ;
    //末尾还存在一个'\0'
    len = p - s + 1;

    char* rs = (char*)malloc(len * sizeof(char));
    char* prs = rs;

    while (p >= s) {
        //单词末尾字符
        while(--p >= s && *p == ' ');
        if (p < s) break;
        char* e = p;
        //单词前一个空格
        while(--p >= s && *p != ' ');
        char* s1 = p + 1;
        while((*prs++ = *s1++) && s1 <= e);
        //单词后跟一个空格
        *prs++ = ' ';
    }
    //末尾为'\0'
    //最后一次执行了*prs++ = ' ' 要替换的就是最后这一个空格
    *(prs-1) = '\0';
    return rs;
}

/**
*   方法三：原地算法
*       1. 先将整个字符串首尾交换。
*       2. 再将每个单词首尾交换。
*       3. 再调整空格
*   时间复杂度O(3n) 步骤1需要n次遍历，步骤2，也需要n次遍历,
*       步骤3，也需要n次遍历。
*   空间复杂度O(1)
*
*   执行用时分布 12 ms 击败 8.34% 使用 C 的用户
*   消耗内存分布 5.98 MB 击败 67.43% 使用 C 的用户
*
**/
void swap(char* a, char* b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}
char* reverseWords_3(char* s) {
    int len = strlen(s);
    for (int i = 0, j = len-1; i < j; ++i, --j) {
        swap(s + i, s + j); 
    }
    //返回字符串的长度
    int n = 0;
    for (int cur = 0; cur < len; ++cur) {
        //words = substring(i, j);
        int i = cur;

        while (i < len && s[i] == ' ') {
            ++i;
        }
        if (i == len) {
            break;
        }
        int j = i + 1;
        while (j < len && s[j] != ' ') {
            ++j;
        }
        n += j - i + 1;
        cur = j;
        --j;
        while(i < j) {
            swap(s + i, s + j);
            ++i;
            --j;
        }
    }
    //处理所有空格
    for (int k = 0; k < n; ++k) {
        int i = k;
        while (i < len && s[i] == ' ') {
            ++i;
        }
        int j = i;
        while (j < len && s[j] != ' ') {
            ++j;
        }
        if (i > k) {
            //需要移动
            while (i < j) {
                s[k++] = s[i++];
            }
            // 移动后有残余的字母，已经是无效字母了，会影响下一轮循环
            int b = k;
            while (b < j) {
                s[b++] = ' ';
            }
        }
        else {
            k = j;
        }
    }
    s[n-1] = '\0';
    return s;
}

int main(void) {
    //15 15
    char s1[] = "the sky is blue";
    //15 11
    char s2[] = "  hello world  ";
    //16 14
    char s3[] = "a good   example";
    char* rs1 = reverseWords_3(s1);
    char* rs2 = reverseWords_3(s2);
    char* rs3 = reverseWords_3(s3);
    printf("rs1=%s#\n", rs1);
    printf("%s#\n", rs2);
    printf("%s#\n", rs3);
    return 0;
}
