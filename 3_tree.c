/* 数据结构课内实验三 二叉树的层次遍历 2017-12-12
 * 
 * 问题描述：设计一个能够对 **链式** 存储的二叉树进行层次遍历的演示程序。
 * 
 * 基本要求：从键盘输入数据，创建一棵二叉树，然后将层次编历的结果输出。
 * 
 * 测试数据：输入的二叉树见教材127页图6.8（b），输出为ABCDEFG。
 * 
 * 实验目的：
 * １．熟悉掌握二叉树和队列的基本操作。
 * ２．培养运用队列解决问题的能力。
 * 
 * 分析：
 * 1.因为要求用链式存储的二叉树，所以要用数组作为二叉树，此时：n的左子数是2n，右子数是2n+1
 * 2.因为输入测试数据的二叉树只有5层，所以数组最长只要32（0不可用）
 * 3.要实现层次遍历，可以在队列每输出一个节点，则将它的左右子节点读入队列，初始为队列左右根节点存在
 * 4.我个人对输入的规定：
 * 第一行：输入要读入的节点数目n
 * 下面n行：输入要读入节点的位置和内容，格式为：
 * L B ->表示根节点的左子树内容为B
 * LL C ->表示根节点的右子树内容为C
 * LR D ->表示根节点的左子树的右子树内容为D
 * 注：根节点输入为：- A
 * 
 * 输入：
7 
- A
L B
LL C
LR D
LRL E
LRR F
LRLR G

 * 输出：
ABCDEFG

 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ElementType char

/***********************这是队列的实现************************/
//这里我是用循环双向链表实现队列

//#ifndef

struct QueueRecord;
typedef struct QueueRecord * PtrToQR;
typedef struct QueueRecord * Queue;

Queue CreateQueue(void);//创建一个空队列，只有头指针
void Enq(ElementType x,int PtrToTree, Queue Q);//把x入队，就是把x放到双向链表的尾部，同时要保存x在树里的位置
PtrToQR FrontAndDeq(Queue Q);//出队并返回出队的元素，就是读出表头的元素

struct QueueRecord
{
    ElementType Element;
    PtrToQR Next, Previous;
    int PtrToTree;//记录此元素在数里的位置，即为数组的数字
};

Queue CreateQueue()
{
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QueueRecord));
    Q->Next = Q;
    Q->Previous = Q;
    Q->PtrToTree = 0;
    return Q;
}

int IsEmpty(Queue Q)
{
    return Q->Next == Q;
}

void Enq(ElementType x,int PtrToTree, Queue Q)
{
    PtrToQR a;
    a = (PtrToQR)malloc(sizeof(struct QueueRecord));
    a->Element = x;
    a->PtrToTree = PtrToTree;
    a->Next = Q;
    a->Previous = Q->Previous;
    Q->Previous->Next = a;
    Q->Previous = a;
}

PtrToQR FrontAndDeq(Queue Q)
{
    PtrToQR temp;
    temp = Q->Next;
    Q->Next = temp->Next;
    temp->Next->Previous = Q;
    return temp;
}

//#endif
/***********************这是队列的实现************************/

//这里我用数组实现二叉树

ElementType Tree[3500];

int main(void)
{
    int i, j;
    int n, len, cnt;
    char s[6], e;
    Queue Q;
    PtrToQR r;
    
    memset(Tree, '*', sizeof(Tree));//初始化
    Q = CreateQueue();
    
    scanf("%d", &n);//要读入的数量
    for(i = 0; i < n; i++)//对每个读入元素确定其在树中位置并写进树中
    {
        scanf("%s %c", s, &e);
        len = strlen(s);
        cnt = 1;
        for(j = 0; j < len; j++)
        {
            if(s[j] == 'L')
                cnt = cnt * 2;
            else if(s[j] == 'R')
                cnt = cnt * 2 + 1;
            else if(s[j] == '-')
                cnt = 1;
        }
        Tree[cnt] = e;
    }
    
    if(Tree[1] != '*')//先入队根节点
        Enq(Tree[1], 1, Q);
    while(!IsEmpty(Q))//实现层次遍历，队列每输出一个节点，则将它的左右子节点读入队列
    {
        r = FrontAndDeq(Q);
        printf("%c", r->Element);
        if(Tree[r->PtrToTree * 2] != '*')
            Enq(Tree[r->PtrToTree * 2], r->PtrToTree * 2, Q);
        if(Tree[r->PtrToTree * 2 + 1] != '*')
            Enq(Tree[r->PtrToTree * 2 + 1], r->PtrToTree * 2 + 1, Q);
    }
    printf("\n");
    
    return 0;
}