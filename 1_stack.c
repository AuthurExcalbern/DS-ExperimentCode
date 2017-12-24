/* 数据结构课内实验二 栈与马踏棋盘问题 2017-12-10
 * 
 * 问题描述：设计一个国际象棋的马踏遍棋盘的演示程序
 * 
 * 基本要求：
 * 将马随机放在国际象棋的8×8棋盘Board[0～7][0～7]的某个方格中，马按走棋规则进行移动。
 * 要求每个方格只进入一次，走遍棋盘上全部64个方格。
 * 编制非递归程序，求出马的行走路线，并按求出的行走路线，将数字1，2，…，64依次填入一个8×8的方阵，输出之。
 * 
 * 测试数据：自行指定马的初始位置。
 * 
 * 实现提示：
 * 马在棋盘上走“日”字型
 * 
 * 分析：
 * 所给图为稠密图，且只有8×8,可以用二维数组表示
 * 因为不可以用递归且要求用栈，所以对每一个点要有八个标记代表八个方向
 * 当栈顶元素的八个发现都被标记走不通时则出栈
 * 选择下一个栈顶元素的某一未标记方向走
 * 走得通则将新点压入栈内，并在二维数组更新数字
 * 当已经压入64个元素时则已经走完
 * 
 * 这个不用递归强行用栈的代码非常非常非常慢！！！
 */

#include<stdio.h>
#include<stdlib.h>

//#ifndef

struct Node;
typedef struct Node * PtrToNode;
typedef PtrToNode Stack;

Stack CreateStack(PtrToNode x);//创建栈，返回头指针，并压入第一个元素x
void Push(PtrToNode x, Stack S);//向栈压入元素x
PtrToNode Top(Stack S);//返回栈顶元素
void InitNode(PtrToNode x);//把地图地点x初始化
void Pop(Stack S);//把栈顶元素出栈
int GetNext(Stack S);//尝试得到栈顶元素的下一步

//#endif

struct Node
{
    int val;//数值代表第几步
    int x, y;//代表在棋盘里的位置
    int der[8];//代表八个方向
    PtrToNode Next;//
}Board[8][8];

Stack CreateStack(PtrToNode x)
{
    Stack S;
    S = (Stack)malloc(sizeof(struct Node));
    S->val = 0;//头指针步数为0
    S->Next = x;//压入第一个元素x
    return S;
}

void Push(PtrToNode x, Stack S)
{
    x->Next = S->Next;
    S->Next = x;
}

PtrToNode Top(Stack S)
{
    return S->Next;
}

void InitNode(PtrToNode x)
{
    int i;
    for(i = 0; i < 8; i++) x->der[i] = 0;
    x->val = 0;
    x->Next = NULL;
}

void Pop(Stack S)
{
    PtrToNode temp;
    temp = S->Next;
    S->Next = temp->Next;
    InitNode(temp);//在这里出栈并不释放内存，而是初始化出栈的点
    //free(temp);
}

int GetNext(Stack S)
{
    int i;
    int x, y;
    //下面是马走的八个方向
    int direction[8][2] = { { -2, 1 }, { -1, 2 }, { 1, 2 }, { 2, 1 }, { 2, -1 }, { 1, -2 }, { -1, -2 }, { -2, -1 } };
    for(i = 0; i < 8; i++)//依次尝试八个方向
    {
        x = Top(S)->x + direction[i][0];
        y = Top(S)->y + direction[i][1];
        //如果走的方向不超出地图且还未走过
        if(Top(S)->der[i] != 1 && x >= 0 && y >= 0 && x <= 7 && y <= 7 && Board[y][x].val == 0)
        {
            Top(S)->der[i]++;//标明已经走过，如果后来走不通退回来，即使把走过的点初始化了，有这标记也不会重复走
            Board[y][x].val = Top(S)->val + 1;
            Board[y][x].y = y;
            Board[y][x].x = x;
            Push(Board[y]+x, S);
            break;
        }
    }
    
    if(i == 8) return 0;
    else return 1;
}

int main(void)
{
    int x, y, cnt = 1;
    Stack S;
    PtrToNode temp;
    
    printf("请以棋盘右上点为原点，按x y输入起始坐标\n");
    scanf("%d %d", &x, &y);
    Board[y][x].val = cnt;
    Board[y][x].y = y;
    Board[y][x].x = x;
    S = CreateStack(Board[y]+x);
    
    while(cnt < 64)
    {
        if(GetNext(S)) cnt++;
        else
        {
            Pop(S);
            cnt--;
        }
    }
    
    for(y = 0; y < 8; y++)
    {
        for(x = 0; x < 8; x++)
            printf("%4d ", Board[y][x].val);
        printf("\n");
    }
    
    return 0;
}

/* 下面是我个人写的递归代码

#include<stdio.h>
#include<string.h>
int direction[8][2] = { { -2, 1 }, { -1, 2 }, { 1, 2 }, { 2, 1 }, { 2, -1 }, { 1, -2 }, { -1, -2 }, { -2, -1 } };
int Board[8][8];
int count = 1;


void Go(int y, int x)
{
    int i, tempy, tempx;
    Board[y][x] = count;
    count++;
    for (i = 0; i < 8; i++)
    {
        tempy = y + direction[i][0];
        tempx = x + direction[i][1];
        if (tempy >= 0 && tempy <= 7 && tempx >= 0 && tempx <= 7 && Board[tempy][tempx] == 0)
        {
            if (count > 64) return;
            else Go(tempy, tempx);
        }
    }
}

void PrintBoard()
{
    int i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++) printf("%4d", Board[i][j]);
        printf("\n");
    }		
}

int main(void)
{
    int y, x;
    memset(Board, 0, sizeof(Board));
    printf("请输入马在初始的位置：（先输行再输列）\n");
    scanf("%d %d", &x, &y);
    Go(y, x);
    PrintBoard();
    return 0;
}

*/