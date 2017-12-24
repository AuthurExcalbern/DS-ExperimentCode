/* 数据结构课内实验五 动态查找表的操作算法
 * 
 * 问题描述：完成二叉排序树的查找、插入和删除。
 * 
 * 基本要求：
 * 1． 进行二叉排序树的结点等类型的相关定义。
 * 2． 编写一个子程序递归地查找二叉排序树。
 * 3． 向二叉排序树中插入元素。这个过程利用前面的查找子程序，若找到同样的关键字，则返回FALSE，否则插入该元素，并保持结果仍然是二叉排序树，返回TRUE。
 * 4． 利用上述插入元素的算法，生成一棵二叉排序树。
 * 5． 编写一个子程序删除二叉排序树中指定关键字的元素。
 * 
 * 测试数据：
 * 创建教材P227页图9.7（a）中的二叉排序树。
 * 
 * 实验目的：
 * 
 * 1． 掌握动态查找表的用法。
 * 2． 熟练递归程序的编写。
 * 3． 培养运用树解决问题的能力。
 * 
 */

#include<stdio.h>
#include<stdlib.h>

//#ifndef

typedef int ElementType;

struct Node;
typedef struct Node * PtrToNode;
typedef struct Node * Tree;

//#endif

Tree CreateTree(ElementType x);//以x为根节点内容创建新树
void InsertLeft(PtrToNode n, ElementType x);//把x插入到节点n的左边
void InsertRight(PtrToNode n, ElementType x);//把x插入到节点n的右边
int FindInsert(Tree t, ElementType x);//在树t里查找插入的位置，成功则返回1,失败返回0;
int Delete(Tree t, ElementType x);//删除树里的元素x，成功则返回1,失败返回0;

struct Node
{
    ElementType Element;
    PtrToNode l, r;
};

Tree CreateTree(ElementType x)
{
    Tree t;
    t = (Tree)malloc(sizeof(struct Node));
    t->Element = x;
    t->l = NULL;
    t->r = NULL;
    return t;
}

void InsertLeft(PtrToNode n, ElementType x)
{
    n->l = (PtrToNode)malloc(sizeof(struct Node));
    n->l->Element = x;
    n->l->l = NULL;
    n->l->r = NULL;
}

void InsertRight(PtrToNode n, ElementType x)
{
    n->r = (PtrToNode)malloc(sizeof(struct Node));
    n->r->Element = x;
    n->r->l = NULL;
    n->r->r = NULL;
}

int FindInsert(Tree t, ElementType x)
{
    if(t->Element == x)
        return 0;
    
    if(t->Element > x)
    {
        if(t->l != NULL)
            FindInsert(t->l, x);
        else
        {
            InsertLeft(t, x);
            return 1;
        }
    }
    else
    {
        if(t->r != NULL)
            FindInsert(t->r, x);
        else
        {
            InsertRight(t, x);
            return 1;
        }
    }
}

int Delete(Tree t, ElementType x)
{
    if(t->Element == x)
    {
        free(t);
        return 1;
    }
    if(t->Element > x)
    {
        if(t->l != NULL)
            Delete(t->l, x);
        else
            return 0;
    }
    else
    {
        if(t->r != NULL)
            Delete(t->r, x);
        else
            return 0;
    }
}

int main(void)
{
    Tree t;
    int n, f = 1,ff = 1, j, i;
    ElementType x;
    
    printf("请输入要插入数字的个数：\n");
    scanf("%d", &n);
    
    for(i = 0; i < n; i++)
    {
        if(ff) {printf("请输入树的根节点：\n"); ff = 0;}
        scanf("%d", &x);
        if(f)
        {
            t = CreateTree(x);
            f = 0;
            printf("树建立成功！\n");
        }
        else
        {
            j = FindInsert(t, x);
            if(j) printf("插入成功！\n");
            else printf("插入失败！\n");
        }
    }
    
    printf("二叉排序树生成成功。\n");
    printf("请输入要删除的元素:\n");
    
    scanf("%d", &x);
    j = Delete(t, x);
    if(j) printf("删除成功！\n");
    else printf("删除失败！\n");
    
    return 0;
}