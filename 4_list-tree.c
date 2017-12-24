/* 数据结构实验四 图的储存和遍历 2017-12-13
 * 
 * 问题描述：根据用户的输入建立一个以邻接矩阵存储的无向图，然后转换为邻接表存储，最后进行深度优先搜索生成森林。
 * 
 * 基本要求：
 * 1． 编写一个子程序创建邻接矩阵。它从键盘输入数据。
 * 2． 编写一个子程序，将邻接矩阵转换为邻接表。
 * 3． 通过深度优先搜索遍历该邻接表，形成的森林用二叉链表存储。
 * 4． 用凹入法打印森林。
 * 
 * 测试数据：创建教材P159页无向图 G3，输出见教材171页图7.15（c）。
 * 
 * 实验目的：
 * １．掌握图的顺序存储和链式存储方法。
 * ２．培养树和图的综合运用能力。
 * 
 * 分析：
 * 先输入要输入的图的点个数n，再输入n×n的矩阵表示点与点间的联通关系，联通为1,不联通为0
 * 节点字母为：A，B，C……
 * 因为输入数据只有十三个点，所以可以建立静态数组来作为邻接矩阵
 * 
 * 输入数据：
请输入邻接矩阵的长宽：
12
请输入邻接矩阵：
0 1 1 0 0 1 0 0 0 0 0 1 0
1 0 0 0 0 0 0 0 0 0 0 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 1 1 0 1 0 0
0 0 0 0 0 0 1 0 0 0 1 0 0
0 0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 1 1
0 0 0 0 0 0 1 1 0 0 0 0 0
1 0 0 0 0 0 0 0 0 1 0 0 1
0 1 0 0 0 0 0 0 0 1 0 1 0
输出邻接链表：
11 5 2 1 
12 0 
0 
4 
3 
0 
10 8 7 
10 6 
6 
12 11 
7 6 
12 9 0 
11 9 1
 */

#include<stdio.h>
#include<stdlib.h>

//#ifndef

struct LNode;
typedef struct LNode * PtrToLNode;
typedef struct LNode * List;

List CreateList();
void Insert(int x, List L);
void ToList(int lf[][15],int n, List L[]);

struct TNode;
typedef struct TNode * PtrToTNode;
typedef struct TNode * Tree;

struct LNode
{
    int i;
    PtrToLNode Next;
};

List CreateList()
{
    List L;
    L = (List)malloc(sizeof(struct LNode));
    L->i = -1;
    L->Next = NULL;
    return L;
}

void Insert(int x, List L)
{
    PtrToLNode p, pp;
    p = (PtrToLNode)malloc(sizeof(struct LNode));
    p->i = x;
    p->Next = L->Next;
    L->Next = p;
}

void ToList(int lf[][15],int n, List L[])
{
    int i, j;
    for(i = 0; i <= n; i++)
    {
        L[i] = CreateList();
        for(j = 0; j <= n; j++)
            if(lf[i][j])
                Insert(j, L[i]);
    }
}
/*
struct TNode
{
    int i;
    PtrToTNode bro, child;
};

void MakeChild(Tree t, PtrToTNode p)
{
    PtrToTNode pp;
    pp = t->child;
    if(pp != NULL)
    {
        while(pp->bro != NULL) {pp = pp->bro;printf("B\n");}
        pp->bro = p;
    }
    else
    {
        t->child = p;printf("C %d %d\n",t->i,p->i);
    }
}

void CreateTree(Tree t, List l, int i, List L[])
{
    PtrToTNode pp;
    PtrToTNode pt;
    PtrToLNode pl;
    l->i++;
    t = (PtrToTNode)malloc(sizeof(struct TNode));
    t->i = i;
    t->child = NULL;
    t->bro = NULL;
    pl = l->Next;
    while(pl != NULL)
    {
        if(L[pl->i]->i != -1) {printf("HY %d\n", pl->i);pl = pl->Next;}
        else
        {printf("%d\n",pl->i);
            //MakeChild(t, pt);
            
            pp = t->child;
            if(pp != NULL)
            {
                while(pp->bro != NULL) {pp = pp->bro;printf("B\n");}
                pp->bro = pt;
                //t->child = pt;
                //pt->bro = pp;
            }
            else
            {
                t->child = pt;printf("C\n");
            }
            CreateTree(pt, L[pl->i], pl->i, L);
            pl = pl->Next;
        }
    }
}

Tree ToTree(List l[], int n)
{
    int i;
    Tree T, temp;
    PtrToTNode pp;
    T = (Tree)malloc(sizeof(struct TNode));
    T->bro = NULL;
    T->i=2233;
    T->child = NULL;
    for(i = 0; i <= n; i++)
    {//printf("H %d\n",i);
        if(l[i]->i == -1)
        {printf("HHHH %d\n", i);
            
            //MakeChild(T, temp);
            pp = T->child;
            if(pp != NULL)
            {
                while(pp->bro != NULL) {pp = pp->bro;printf("B\n");}
                pp->bro = temp;
                //T->child = temp;
                //temp->bro = pp;
            }
            else
            {
                T->child = temp;printf("C\n");
            }
            
            CreateTree(temp, l[i], i, l);
        }
    }
    return T;
}

void Pr(Tree t)
{
    //if(t->child != NULL) printf("%d\n",t->i);
}
*/
int main(void)
{
    int n, i, j;
    int lf[15][15];
    List L[15], pl;
    Tree T;
    
    printf("请输入邻接矩阵的长宽：\n");
    scanf("%d", &n);

    printf("请输入邻接矩阵：\n");
    for(i = 0; i <= n; i++)
        for(j = 0; j <= n; j++)
            scanf("%d", &lf[i][j]);
    
    ToList(lf, n, L);

    printf("输出邻接链表：\n");
    for(i = 0; i <= n; i++)
    {
        pl = L[i];
        while(pl->Next != NULL) {printf("%d ",pl->Next->i); pl=pl->Next;}
        printf("\n");
    }
    
    //T = ToTree(L, n);
    //printf("凹入法输出森林：\n");
    //Pr(T);
    
    return 0;
}