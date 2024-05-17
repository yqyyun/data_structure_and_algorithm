#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

/**
*   5. 最长回文子串 Longest Palindromic Substring
*   <https://leetcode.cn/problems/longest-palindromic-substring/description/>
*   已发布到力扣上的题解：<https://leetcode.cn/problems/longest-palindromic-substring/solutions/2776334/fang-fa-er-kuo-san-cha-zhao-you-nei-xian-nfew>
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

/**
* 方法一优化：
*   假设已经找到长度为k的回文子串，那么长度小于k的子串就没必要去查找和验证了。
*   即按照方法一函数的实现：游标从palindromes数组的左端，只能向右移动，不能来回移动了。
*
*   优化后的时间复杂度最坏为O(m²)，回文子串长度为1，最好时间复杂度为O(m)回文子串长度就是m。
*   空间复杂度为O(m²)，但可以改进为O(m)。
*   本函数空间复杂度为O(m²)。
*
* 执行用时分布 176 ms 击败 21.02% 使用 C 的用户
* 消耗内存分布 6.81 MB 击败 30.88% 使用 C 的用户
**/
char* longestPalindrome_1_imp1(char* s) {
    int length = 0;
    while (s[length] != '\0'){
        length++;
    }
    int size = length + 1;
    //空间复杂度为O(m²)。
    char palindromes[size][size];
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            palindromes[i][j] = 0;
        }
    }
    int maxl = 0;
    for (int i = 0; (i + maxl) < length; ++i) {
        int j = length;
        do {
            while (--j > (i + maxl) && s[j] != s[i]);
            if (j < (i + maxl)) {
                break;
            }
            if (isPalindrome(s, i, j)) {
                int pos = j - i + 1;
                if (pos > maxl) {
                    maxl = pos;
                }
                for (int k = pos-1; k > -1; --k,--j) {
                    palindromes[pos][k] = s[j];
                }
                break;
            }
        } while(true);
    }
    char* lp = (char*)malloc(size * sizeof(char));
    char* plp = lp;
    char* src = palindromes[maxl];
    while((*plp++ = *src++) != '\0');
    return lp;
}

/**
*   空间复杂度为O(m);
* 执行用时分布 103 ms 击败 46.66% 使用 C 的用户
* 消耗内存分布 5.89 MB 击败 69.41% 使用 C 的用户
**/
char* longestPalindrome_1_imp2(char* s) {
    int length = 0;
    while (s[length] != '\0'){
        length++;
    }
    int size = length + 1;
    //空间复杂度为O(m)。
    char* lpa = (char*)calloc(size, sizeof(char));

    int maxl = 0;
    for (int i = 0; (i + maxl) < length; ++i) {
        int j = length;
        do {
            while (--j > (i + maxl) && s[j] != s[i]);
            if (j < (i + maxl)) {
                break;
            }
            if (isPalindrome(s, i, j)) {
                int pos = j - i + 1;
                if (pos > maxl) {
                    maxl = pos;
                }
                for (int k = pos-1; k > -1; --k,--j) {
                    lpa[k] = s[j];
                }
                break;
            }
        } while(true);
    }
    return lpa;
}
/**
*   方法二：扩散查找，由内向外。
*   回文子串总是对称的：
*       当子串长度为偶数时，mid=(length-1)/2
*           S[mid-(i-1)]≡S[mid+i], i=1,2,...,mid。
*       当子串长度为奇数时，mid=(length-1)/2
*           S[mid-i]≡S[mid+1], i=1,2,...,mid。
*   此时回文子串的长度是由内向两侧逐渐扩散的，因此叫扩散查找。
*   
*   时间复杂度O(mn)，m为字符串长度，n为回文子串平均长度
*   空间复杂度O(m), m为字符串长度。
*
* 执行用时分布 6 ms 击败 94.01% 使用 C 的用户
* 消耗内存分布 5.96 MB 击败 63.43% 使用 C 的用户
**/
char* longestPalindrome_2(char* s) {
    int length = -1;
    while(s[++length] != '\0');
    //下标为回文子串长度，元素值为回文子串在s中的下标位置（从0开始）
    int pals[length+1];
    for (int i = 0; i < length+1; ++i)
        pals[i] = -1;
    //
    for (int i = 0; i < length; ++i) {
        // 按照偶数长度扩展
        int l = i, r = i + 1;
        for (; l > -1 && r < length; --l, ++r) {
            if (s[l] != s[r]) {
                //回文子串扩展结束
                break;
            }
        }
        int size = r - l - 1;
        // (l, r)
        pals[size] = l + 1;
        // 按照奇数长度扩展
        l = i - 1, r = i + 1;
        for (; l > -1 && r < length; --l, ++r) {
            if (s[l] != s[r]) {
                //回文子串扩展结束
                break;
            }
        }
        size = r - l - 1;
        pals[size] = l + 1;
    }
    for (int i = length; i > -1; --i) {
        if (pals[i] != -1) {
            // 就地返回 i是回文字长长度，pals[i]是起点。
            int start = pals[i];
            // '\0'字符位置
            //int e = pals[i] + i;
            s[start + i] = '\0';
            return s + start;
        }
    }
    return s + length - 1;
}

/**
*   方法二优化：
*   不再保存所有回文子串，改成只保留目前得到的最长回文子串。
*   空间复杂度从O(m) 变为O(1)
*
* 执行用时分布 6 ms 击败 93.98% 使用 C 的用户
* 消耗内存分布 5.57 MB 击败 99.53% 使用 C 的用户
*
*   备注：优化之处只是空间复杂度变成O(1)，执行用时理论不会减少，
*   甚至还会增加，变成负优化。
*   这是因为每次更新maxl和start时都会执行判断，这和未优化之前的
*   循环是一个效果，但是maxl和start每次循环都会执行两次，也就是2m
*   次。而未优化之前的循环只会在最后反向遍历，找到第一个有效值就结束
*   了，也就是最多m 次(回文子串长度为1时）。比较次数少了至少一半。
**/
char* longestPalindrome_2_impr1(char* s) {
    int length = -1;
    while(s[++length] != '\0');
    // 
    int maxl = 0;
    int start = 0;
    for (int i = 0; i < length; ++i) {
        // 按照偶数长度扩展
        int l = i, r = i + 1;
        for (; l > -1 && r < length; --l, ++r) {
            if (s[l] != s[r]) {
                //回文子串扩展结束
                break;
            }
        }
        int size = r - l - 1;
        // (l, r)
        if (size > maxl) {
            maxl = size;
            start = l + 1;
        }
        // 按照奇数长度扩展
        l = i - 1, r = i + 1;
        for (; l > -1 && r < length; --l, ++r) {
            if (s[l] != s[r]) {
                //回文子串扩展结束
                break;
            }
        }
        size = r - l - 1;
        if (size > maxl) {
            maxl = size;
            start = l + 1;
        }
    }
    s[start + maxl] = '\0';
    return s + start;
}

/**
*   方法二优化：
*   取消s.length计算，改为指针访问字符。
*
*   执行用时分布 2 ms 击败 98.76% 使用 C 的用户
*   消耗内存分布 5.70 MB 击败 88.16% 使用 C 的用户
*
**/
char* longestPalindrome_2_impr2(char* s) {
    // 
    int maxl = 0;
    char* start = s;
    for (char * p = s; *p != '\0'; ++p) {
        // 按照偶数长度扩展
        char* l = p, *r = p + 1;
        for (; l >= s && *r != '\0'; --l, ++r) {
            if (*l != *r) {
                //回文子串扩展结束
                break;
            }
        }
        int size = r - l - 1;
        // (l, r)
        if (size > maxl) {
            maxl = size;
            start = l + 1;
        }
        // 按照奇数长度扩展
        l = p - 1, r = p + 1;
        for (; l >= s && *r != '\0'; --l, ++r) {
            if (*l != *r) {
                //回文子串扩展结束
                break;
            }
        }
        size = r - l - 1;
        if (size > maxl) {
            maxl = size;
            start = l + 1;
        }
    }
    *(start + maxl) = '\0';
    return start;
}

/**
*   方法三：定长扩展
*   当找到一个长度为Len1的回文子串时，就没必要在去找长度小于或等于Len1的回文子串了。
*
*   先遍历s字符串，找到第一个回文子串时，长度记为Len1，位置记为start，末尾则为
*   start + Len1 + 1 = end。在查找到回文子串时，(start, end)都是已知的，因此可以直接
*   用双指针平行移动判断S[start + 1] =?= S[end + 1]，若相等则，判断Substring(start+1, end-1)
*   是不是回文子串，若是则扩展，扩展后的长度，记为Len2，更新maxl为len2，。。直到结束。
*
*   执行用时分布 0 ms 击败 100.00% 使用 C 的用户
*   消耗内存分布 5.87 MB 击败 70.86% 使用 C 的用户
*
**/
bool isPalindromes_1(char* start, char* end) {
    while (start < end) {
        if (*start++ != *end--) {
            return false;
        }
    }
    return true;
}
char* longestPalindrome_3(char* s) {
    if (*(s + 1) == '\0') {
        return s;
    }
    if (*(s + 2) == '\0' && *s == *(s + 1)) {
        return s;
    }
    //根据题意不存在空串
    int maxl = 1;
    char* lpa = s;
    //TODO 指针方式访问数组，不适合做步长较大的移动，否则容易越界访问报错。
    //       如果是步长较大的，应该采用数组下标的方式，进行边界检查。
    //偶数
    for (char* l = s, *r = s + 1; *r != '\0'; ++l, ++r) {
        if (*l == *r && isPalindromes_1(l, r)) {
            // 扩展
            --l;++r;
            for (; l >= s && *r != '\0'; --l, ++r) {
                if (*l != *r) {
                    break;
                }
            }
            if (r - l - 1 > maxl) {
            maxl = r - l - 1;
                lpa = l + 1;
            }
            if (*r == '\0') 
                break;
        }
    }
    for (char* l = s, *r = s + 2; *r != '\0'; ++l, ++r) {
        if (*l == *r && isPalindromes_1(l, r)) {
            //扩展
            --l; ++r;
            for (; l >= s && *r != '\0'; --l, ++r) {
                if (*l != *r) {
                    break;
                }
            }
            if (r - l - 1 > maxl) {
                maxl = r - l - 1;
                lpa = l + 1;
            }
            if (*r == '\0')
                break;
        }
    }
    *(lpa + maxl) = '\0';
    return lpa;
}

/**
* 方法三优化：
*   第二轮循环时，只找比偶数长度大的奇数回文子串，因此子串
*   右端点初始位置不再是*r = s + 2, 而是*r = s + maxl，
*   减少了第二轮遍历次数，而且由于s+2变成了s+maxl避免了指针
*   溢出因此，不在需要额外处理长度为1和2的字符串了，因为长度
*   为1或2时，此时maxl只能为0或2，不会溢出。
*
*  执行用时分布 0 ms 击败 100.00% 使用 C 的用户
*  消耗内存分布 6.00 MB 击败 59.28% 使用 C 的用户
*
**/
char* longestPalindrome_3_impr1(char* s) {
/*
    if (*(s + 1) == '\0') {
        return s;
    }
    if (*(s + 2) == '\0' && *s == *(s + 1)) {
        return s;
    }
*/
    //从0开始，以便处理长度为1或2时的奇数轮遍历 
    int maxl = 0;
    char* lpa = s;
    //TODO 指针方式访问数组，不适合做步长较大的移动，否则容易越界访问报错。
    //       如果是步长较大的，应该采用数组下标的方式，进行边界检查。
    //偶数
    for (char* l = s, *r = s + 1; *r != '\0'; ++l, ++r) {
        if (*l == *r && isPalindromes_1(l, r)) {
            // 扩展
            --l;++r;
            for (; l >= s && *r != '\0'; --l, ++r) {
                if (*l != *r) {
                    break;
                }
            }
            if (r - l - 1 > maxl) {
            maxl = r - l - 1;
                lpa = l + 1;
            }
            if (*r == '\0') 
                break;
        }
    }
    for (char* l = s, *r = s + maxl; *r != '\0'; ++l, ++r) {
        if (*l == *r && isPalindromes_1(l, r)) {
            //扩展
            --l; ++r;
            for (; l >= s && *r != '\0'; --l, ++r) {
                if (*l != *r) {
                    break;
                }
            }
            if (r - l - 1 > maxl) {
                maxl = r - l - 1;
                lpa = l + 1;
            }
            if (*r == '\0')
                break;
        }
    }
    *(lpa + maxl) = '\0';
    return lpa;
}


/**
*   力扣官方题解一：动态规划
*
* <https://leetcode.cn/problems/longest-palindromic-substring/solutions/255195/zui-chang-hui-wen-zi-chuan-by-leetcode-solution/>
*
*  如果"bab" 是一个回文串，那么"ababa"也是个回文串，因为首尾字母相同。
*  P(i,j)表示是否是回文串，则
*   P(i,j) = -> true  Si...Sj是回文串
*           |
*            -> false Si...Sj不是回文串，或i > j
*
*   动态规划状态转移方程：
*       P(i,j) = P(i+1,j-1) ∩ (Si == Sj)
*   显然当子串长度为1时，P(i+1,j-1)=false 因为i > j，但是长度为1的子串显然是个回文串。
*   当长度为2时，只要两个字符相同就是回文串。
*   因此长度为1或2的子串不符合上述状态方程，要特殊处理。
*   状态转移方程边界条件：
*
*       P(i,i) = true, P(i,i+1) = (Si == Si+1)
*
*   时间复杂度O(n²) 空间复杂度O(n²)
*
*  执行用时分布 186 ms 击败 19.22% 使用 C 的用户
*  消耗内存分布 7.10 MB 击败 25.82% 使用 C 的用户
**/
char* longestPalindrome_4(char* s) {
    int length = strlen(s);   
    if (length == 1) {
        return s;
    }
    if (length == 2) {
        if (*s == *(s+1)) {
            return s;
        }
        else {
            *(s+1) = '\0';
            return s;
        }
    }
    //记录状态
    bool dp[length][length];
    int maxl = 1;
    int st = 0;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            if (i == j) {
                //边界条件一 P(i,i) = true
                dp[i][i] = true;
            }
            else if (i + 1 == j && s[i] == s[j]) {
                //边界条件二 P(i,i+1) = (Si == Si+1)
                dp[i][j] = true;
                if (j - i + 1 > maxl) {
                    maxl = j - i + 1;
                    st = i;
                }
            }
            else {
                //其它情况先初始化为false;
                dp[i][j] = false;
            }
        }
    }
    for (int len = 2; len < length; ++len) {
        //len=j - i + 1;
        for (int i = 0, j = len; j < length; ++i, ++j) {
            //状态转移方程 
            //dp[i][j] = dp[i+1][j-1] && (s[i] == s[j]);
            if (s[i] == s[j] && (dp[i][j] = dp[i+1][j-1]) == true) {
                if (j - i + 1> maxl) {
                    maxl = j - i + 1;
                    st = i;
                }
            }
        }
    }
/**
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < length; ++j) {
            printf("[%d]", dp[i][j]);
        }
        printf("\n");
    }
**/
    /**
    *   以"babad"为例得到的dp数组
    *     0  1  2  3  4
    *  0 [1][0][1][0][0]
    *  1 [0][1][0][1][0]
    *  2 [0][0][1][0][0]
    *  3 [0][0][0][1][0]
    *  4 [0][0][0][0][1]
    **/
    s[st + maxl] = '\0';
    return &s[st];
}


int main(void) {
    char s1[] = {'c','b','b','d','\0'};
    char s2[] = {'b','a','b','a','d','\0'};
    char s3[] = {'c','c','c','\0'};
    char* rs1 = longestPalindrome_3_impr1(s1);
    char* rs2 = longestPalindrome_3_impr1(s2);
    char* rs3 = longestPalindrome_3_impr1(s3);
    printf("%s\n", rs1);
    printf("%s\n", rs2);
    printf("%s\n", rs3);
    return 0;
}
