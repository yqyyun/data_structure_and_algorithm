#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

/**
*   561.数组拆分Array Partition
*   <https://leetcode.cn/problems/array-partition/description/>
**/

/**
*   方法一：排序法
*   将数组从小到大排序，再将偶数位置上的数字相加即可。
*   
*   时间复杂度：O(nlogn + n)
*   时间复杂度主要取决于排序算法的时间复杂度。
*   空间复杂度O(1)
*
*   执行用时分布 72 ms 击败 61.03% 使用 C 的用户
*   消耗内存分布 8.15 MB 击败 55.16% 使用 C 的用户
*
**/   
int i_comp(const void * a, const void * b) {
    return *(int*)a - *(int*)b;
}
int arrayPairSum_1(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), i_comp);
    int sum = 0;
    for (int i = 0; i < numsSize; i += 2) {
        sum += nums[i];
    }
    return sum;
}

/**
*   方法二：选择排序法，双指针法
*
*   选择排序的中间过程会将最小值从左到右逐渐找出来。   
*
*   时间复杂度O(n²)， 第一轮需要查找最小差值n-1次，第二轮需要n-2次
*       依次类推最后一轮，只需要一次, 1 + 2 + 3 .. +n -1 = n*n/2
*   空间复杂度O(1)
*
*   测试用例通过了，但耗时太长。
**/
int arrayPairSum_2(int* nums, int numsSize) {
    int sum = 0;
    for(int i = 0; i < numsSize; ++i) {
        int min = nums[i];\
        int k = i;
        for (int j = i + 1; j < numsSize; ++j) {
            if (min > nums[j]) {
                min = nums[j];
                k = j;
            }
        }
        if (k != i) {
            nums[i] = nums[i] ^ nums[k];
            nums[k] = nums[i] ^ nums[k];
            nums[i] = nums[i] ^ nums[k];
        }
        if (i % 2 == 0) {
            sum += nums[i];
        }
    }
    return sum;
}

/**
*   方法三：基数排序
*
*
**/
int bucketsSize = 19;
typedef struct Node{
    int data;
    struct Node * next;
} *LinkList, Node;
void print(LinkList* lists);
//TODO Node* heads, *tails;
int arrayPairSum_3(int* nums, int numsSize) {
    int bucketsSize = 19;
    int offset = 9;
    Node** buckets = (Node**)malloc(bucketsSize * sizeof(Node*));
    Node** tails = (Node**)malloc(bucketsSize * sizeof(Node*));
    for(int i = 0; i < bucketsSize; ++i) {
        //空头节点，减少空指针判断。
        LinkList dummy = (LinkList)malloc(sizeof(Node));
        buckets[i] = dummy;
        //可能存在随机值，必须手动置空
        //若一个变量被赋值后未被使用就被修改了，这个赋值语句可能会被编译器优化删掉
        //所以为了代码不容易出错手动初始NULL，降低出错率也不会影响性能
        dummy->next = NULL;
        //初始化尾指针数组,初始指向头节点
        tails[i] = buckets[i];
    }

    for (int i = 0; i < numsSize; ++i) {
        //先入桶, 尾插法
        int index = nums[i] % 10 + offset;
        LinkList newNode = (LinkList)malloc(sizeof(Node));
        newNode->data = nums[i];
        newNode->next = NULL;
        //尾插
        tails[index]->next = newNode;
        tails[index] = newNode;
    }
    Node** temp = (Node**)malloc(bucketsSize * sizeof(Node*));
    for (int j = 0; j < bucketsSize; ++j) {
        LinkList dummy = (LinkList)malloc(sizeof(Node));
        dummy->next = NULL;
        temp[j] = dummy;
    }
    //100/0
    int base = 1;
    //  TODO,第六轮时，所有元素都在9号链表上就是求余尾0的数。
    for (int i = 1; i < 4 + 1; ++i) {
        //处理剩余三轮, 采用尾插法
        base *= 10;
        
        for (int j = 0; j < bucketsSize; ++j) {
            //尾指针数组初始化为新的node指针数组头节点。
            //新节点有效元素为空（除了空节点）
            tails[j] = temp[j];
        }
        for (int j = 0; j < bucketsSize; ++j) {
            LinkList p = buckets[j]->next;
            LinkList q;
            //FIX 清空数组, 修复死循环错误
            buckets[j]->next = NULL;

            while (p != NULL) {
                
                int index = (p->data / base % 10 ) + offset;
                q = p;
                p = p->next;
                //将节点尾插到新链表数组。
                tails[index]->next = q;
                q->next = NULL;
                //更新尾节点指针数组
                tails[index] = q;
            }
        }
        Node** t = buckets;
        buckets = temp;
        temp = t;

    }
    // 将排序结果保存到nums，并释放内存
    int sum = 0;
    int k = 0;
    for (int i = 0; i < bucketsSize; ++i) {
        LinkList p = buckets[i]->next;
        LinkList q;
        while(p != NULL) {
            q = p;
            p = p->next;

            nums[k] = q->data;
            if (k%2 == 0) sum += nums[k];
            ++k;
            free(q);
        }
    }
    for (int i = 0; i < bucketsSize; ++i) {
        free(buckets[i]);
        free(temp[i]);
    }
    free(buckets);
    free(temp);
    return sum;
        
}

void print(LinkList * lists) {
    for (int k = 0; k < bucketsSize; ++k) {
        printf("%d: ", k);
        LinkList p = lists[k];
        LinkList q;
        if (p->next == NULL) {
            puts("NULL");
            //printf("NULL\n");
            //puts("hello");
            continue;
        }
        while (p->next != NULL) {
            //printf("hello");
            //在测试这段代码时，发现printf和puts在出错代码时表现不同
            //具体表现为puts能稳定输出到出错代码处，而printf在出错
            //代码之前就不输出了，出现了不同步的现象。
            //疑似puts同步的，而printf不同步，查询手册得知两者都是线程安全的
            //puts("hello");
            q = p->next;
            //error
            //p = q->next;
            p = q;
            printf("%d,", q->data);
        }
        printf("\n");
    }
}


int main(void) {
    int n1[4] = {1,4,3,2};
    int n2[6] = {6,2,6,5,1,2};
    int n3[4] = {6214, -2290, 2833, -7908};
    //printf("%d\n", arrayPairSum_3(n1, 4));
    //printf("%d\n", arrayPairSum_3(n2, 6));
    //-5075
    printf("%d\n", arrayPairSum_3(n3, 4));
    return EXIT_SUCCESS;
}
