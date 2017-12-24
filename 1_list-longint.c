/* 2017-12-10 数据结构的课内实验一
 * 
 * 问题描述：用双向循环链表实现任意长整数的加减法计算
 * 
 * 基本要求：
 * 利用双向循环链表实现长整数的存储，每个结点含一个整形变量。
 * 输入和输出形式：按中国对于长整数的表示习惯，每四位一组，组间用逗号隔开。
 * 
 * 测试数据：
 * （1）0；0；应输出“0”。
 * （2）-2345,6789；-7654,3211；应输出“-1,0000,0000”。
 * （3）-9999,9999；1,0000,0000,0000；应输出“9999,0000,0001”。
 * （4）1,0001,0001；-1,0001,0001；应输出“0”。
 * （5）1,0001,0001；-1,0001,0000；应输出“1”。
 * （6）-9999,9999,9999；-9999,9999,9999；应输出“-1,9999,9999,9998”。
 * （7）1,0000,9999,9999；1；应输出“1,0001,0000,0000”。
 */

#include<stdio.h>
#include<stdlib.h>
#define ElementType int

//#ifndef

struct Node;
typedef struct Node * PtrToNode;
typedef PtrToNode List;

List CreateList(ElementType x);//创建双向循环链表，并把头指针的内容赋值为x
void AddNode_front(ElementType N, List L);//在L的表头添加节点N
void AddNode_end(ElementType N, List L);//在L的表尾添加节点N
void Pop_end(PtrToNode x, List L);//把双向链表表尾的节点删除
List GetNum();//输入数字
List Add(List a, List b);//a和b的符号相同，将a和b里的数相加
List Cmp(List a, List b);//a和b的符号不同，比较a和b的绝对值
List Sub(List a, List b);//a和b的符号不同，将a和b里的数相减，且此时已经判断出：|a| > |b|
void MakePoint(List L);//从低位向高位遍历，每隔4个位加一个逗号标记
List GetAns(List a, List b);//得到答案
void PrintAns(List L);//输出答案


//#endif

struct Node
{
    ElementType Element;//每一个节点只存储一位数值
    int s;//标记是否为头指针，其实我后来发现可以不用这个
    int d;//标记是否需要输出逗号，因为我们是按高位到低位输出，所以要事先从低位往高位表明那里需要逗号
    PtrToNode Next, Previous;//指针
};

List CreateList(ElementType x)
{
    List L;
    L = (List)malloc(sizeof(struct Node));
    L->Element = x;
    L->s = 1;//标明为头指针
    L->Next = L;
    L->Previous = L;
    return L;
}

void AddNode_front(ElementType x, List L)
{
    PtrToNode NewNode;
    NewNode = (PtrToNode)malloc(sizeof(struct Node));
    //在双向链表的表头指针的next添加节点
    NewNode->Element = x;
    NewNode->Next = L->Next;
    NewNode->Previous = L;
    L->Next->Previous = NewNode;
    L->Next = NewNode;
}

void AddNode_end(ElementType x, List L)
{
    PtrToNode NewNode;
    NewNode = (PtrToNode)malloc(sizeof(struct Node));
    //在双向链表的表头指针的previous添加节点
    NewNode->Element = x;
    NewNode->Next = L;
    NewNode->Previous = L->Previous;
    L->Previous->Next = NewNode;
    L->Previous = NewNode;
}

void Pop_end(PtrToNode x, List L)
{
    L->Previous = x->Previous;
    x->Previous->Next = L;
    free(x);
}

List GetNum()
{
    List L;
    char c;
    
    //第一个字符区分一下输入的数字是正数还是负数
    c = getchar();
    if(c == '-') L = CreateList(-1);
    else
    {
        L = CreateList(1);
        AddNode_front(c-'0', L);
    }
    
    //忽略输入的逗号，只读入数字，在对数字计算后再加入逗号
    c = getchar();
    while(c != ';')
    {
        if(c != ',') AddNode_front(c-'0', L);
        c = getchar();
    }
    
    //免去换行符的影响
    getchar();
    
    return L;
}

List Add(List a, List b)
{
    int temp1 = 0, temp2 = 0;//temp1为每一位a和b相加后的个位数，temp2为加的进位
    List L;
    L = CreateList(a->Element);//a和b的符号相同，随便取其中一个作为结果的符号
    
    //跳过头指针
    a = a->Next;
    b = b->Next;
    //a与b相每个节点的内容相加
    while(a->s == 0 && b->s == 0)
    {
        temp1 = a->Element + b->Element + temp2;
        
        if(temp1 > 9)
        {
            temp2 = temp1 / 10;
            temp1 = temp1 % 10;
        }
        else
            temp2 = 0;
        
        AddNode_end(temp1, L);
        
        a = a->Next;
        b = b->Next;
    }
    //当a比b长时，要把剩下的a录入结果里，不要忘了现在进位temp2不一定为零
    while(a->s == 0)
    {
        temp1 = a->Element+ temp2;
        
        if(temp1 > 9)
        {
            temp2 = temp1 / 10;
            temp1 = temp1 % 10;
        }
        else
            temp2 = 0;
        
        AddNode_end(temp1, L);
        
        a = a->Next;
    }
    //当b比a长时，要把剩下的b录入结果里，不要忘了现在进位temp2不一定为零
    while(b->s == 0)
    {
        temp1 = b->Element + temp2;
        
        if(temp1 > 9)
        {
            temp2 = temp1 / 10;
            temp1 = temp1 % 10;
        }
        else
            temp2 = 0;
        
        AddNode_front(temp1, L);
        
        b = b->Next;
    }
    
    //当a和b长度相等时，可能会有多的进位
    if(temp2 != 0) AddNode_end(temp2, L);
    
    return L;
}

List Cmp(List a, List b)
{
    List L;
    PtrToNode aa;
    PtrToNode bb;
    aa = a->Next;
    bb = b->Next;
    while(aa->s == 0 && bb->s == 0)
    {
        aa = aa->Next;
        bb = bb->Next;
    }
    
    if(aa->s == 0 && bb->s != 0) L = Sub(a, b);//a比b长
    else if(aa->s != 0 && bb->s == 0) L = Sub(b, a);//b比a长
    else if(aa->s != 0 && bb->s != 0)//a和b等长
    {
        aa = a->Previous;
        bb = b->Previous;
        while(aa->Element == bb->Element)//从高位到低位跳过值相等的
        {
            aa = aa->Previous;
            bb = bb->Previous;
        }
        if(aa->s != 0 && bb->s != 0)//a和b绝对值相同
        {
            L = CreateList(1);
            AddNode_end(0, L);
            return L;
        }
        else if(aa->Element > bb->Element) L = Sub(a, b);//a绝对值大于b
        else if(aa->Element < bb->Element) L = Sub(b, a);//a绝对值小于b
    }
    
    return L;
}

List Sub(List a, List b)
{
    int temp1 = 0, temp2 = 0;//temp1为每一位a和b相减后的个位数，temp2是减进位
    List L;
    L = CreateList(a->Element);//因为a的绝对值大，所以用a是正是负来决定结果是正是负
    
    //跳过头指针
    a = a->Next;
    b = b->Next;
    //把a减去b
    while(a->s == 0 && b->s == 0)
    {
        temp1 = a->Element - b->Element - temp2;
        
        if(temp1 < 0)
        {
            temp2 = 1;
            temp1 = temp1 + 10;
        }
        else
            temp2 = 0;
        
        AddNode_end(temp1, L);
        
        a = a->Next;
        b = b->Next;
    }
    //录入剩下的a
    while(a->s == 0)
    {
        temp1 = a->Element - temp2;
        
        if(temp1 < 0)
        {
            temp2 = 1;
            temp1 = temp1 + 10;
        }
        else
            temp2 = 0;
        
        AddNode_end(temp1, L);
        
        a = a->Next;
    }
    
    //要删除减后产生的在顶端的零
    while(L->Previous->Element == 0 && L->Previous->s == 0)
        Pop_end(L->Previous, L);
    
    return L;
}

void MakePoint(List L)
{
    int cnt = 1;
    L = L->Next;//从低位向高位遍历
    while(L->s == 0)
    {
        L = L->Next;
        cnt++;
        if(cnt == 4)//每隔4位加一个逗号标记
        {
            L->d = 1;
            cnt = 0;
        }
    }
    L->Previous->d = 0;
}

List GetAns(List a, List b)
{
    List L;
    if(a->Element * b->Element < 0) L = Cmp(a, b);//a和b的符号不同
    else L = Add(a, b);//a和b的符号相同
    MakePoint(L);//加入逗号
    return L;
}

void PrintAns(List L)
{
    if(L->Element == -1) printf("-");
    
    L = L->Previous;//从高位开始输出
    while(L->s == 0)
    {
        if(L->d == 1)//有标记则输出一个逗号
            printf(",");
        printf("%d", L->Element);
        L = L->Previous;
    }
    
    printf("\n");
}
    
int main(void)
{
    List a, b, ans;
    printf("请输入第一个数：\n");
    a = GetNum();
    printf("请输入第二个数：\n");
    b = GetNum();
    ans = GetAns(a, b);
    printf("运算结果是：\n");
    PrintAns(ans);
    return 0;
}

/* 下面是老师给的代码，我个人加上了许些注释

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
typedef struct BaseNote
{
	struct BaseNote *prior, *next;
	int data;
}BaseNote, *BaseElem;

BaseElem CreatList(int style);
BaseElem InputData();
void InsertDataAtTail(BaseElem L, int num);
void InsertDataAtHead(BaseElem L, int num);
void PrintList(BaseElem L);
BaseElem AddData(BaseElem a, BaseElem b);
BaseElem Add(BaseElem a, BaseElem b);
BaseElem Sub(BaseElem a, BaseElem b);
void DelData(BaseElem L, BaseElem p);

//建立一个初始循环列表，用style确定长整数的正负
BaseElem CreatList(int style)
{
	BaseElem s;
	s = (BaseElem)malloc(sizeof(BaseNote));
	s->next = s->prior = s;
	s->data = style;
	return s;
}

//用于读入输入的长整数
BaseElem InputData()
{
	int num;//用来存储4位十进制整数
	char c;
	BaseElem L;
	printf("Please input data:");
	if ((c = getchar()) == '-') L = CreatList(-1);
	else L = CreatList(1);
	if (isdigit(c)) ungetc(c, stdin);//isdigit(c)判断c是否为1~9，是则送回读入的字符
	scanf("%d", &num);
	InsertDataAtTail(L, num);
	while ((c = getchar()) != '\n')//读入逗号时自动忽略
	{
		scanf("%d", &num);//按输入的特点，一次性读入四位整数
		InsertDataAtTail(L, num);
	}
	printf("Your input data is:");
	PrintList(L);
	//printf("\n");
	return L;
}

//在循环链表L的表尾插入新数num
void InsertDataAtTail(BaseElem L, int num)
{
	BaseElem s;
	s = (BaseElem)malloc(sizeof(BaseNote));
	s->data = num;
	s->next = L;
	s->prior = L->prior;
	L->prior->next = s;
	L->prior = s;
}

//在循环链表L的表头插入新数num
void InsertDataAtHead(BaseElem L, int num)
{
	BaseElem s;
	s = (BaseElem)malloc(sizeof(BaseNote));
	s->data = num;
	s->next = L->next;
	s->prior = L;
	L->next->prior = s;
	L->next = s;
}

//输出循环链表中的长整数
void PrintList(BaseElem L)
{
	BaseElem counter;
	counter = L;
	if (counter->data == -1) printf("-");
	counter = counter->next;
	if (counter != L)
	{
		printf("%d", counter->data);
		counter = counter->next;
	}
	while (counter != L)
	{
		printf(",%04d", counter->data);
		counter = counter->next;
	}
	printf("\n");
}

//将循环链表a和b里的两个长整数相加
BaseElem AddData(BaseElem a, BaseElem b)
{
	BaseElem c;
	if (a->data * b->data > 0) c = Add(a, b);
	else c = Sub(a, b);
	return c;
}

//a和b同正负的情况
BaseElem Add(BaseElem a, BaseElem b)
{
	BaseElem c = CreatList(a->data);
	BaseElem pa, pb;
	int temp1 = 0, temp2;
	pa = a->prior;
	pb = b->prior;
	while (pa != a && pb != b)
	{
		temp2 = pa->data + pb->data + temp1;
		if (temp2 >= 10000)
		{
			temp1 = 1;
			temp2 = temp2 - 10000;
		}
		else temp1 = 0;
		InsertDataAtHead(c, temp2);
		pa = pa->prior;
		pb = pb->prior;
	}
	while (pa != a)
	{
		temp2 = pa->data + temp1;
		if (temp2 >= 10000)
		{
			temp1 = 1;
			temp2 = temp2 - 10000;
		}
		else temp1 = 0;
		InsertDataAtHead(c, temp2);
		pa = pa->prior;
	}
	while (pb != b)
	{
		temp2 = pb->data + temp1;
		if (temp2 >= 10000)
		{
			temp1 = 1;
			temp2 = temp2 - 10000;
		}
		else temp1 = 0;
		InsertDataAtHead(c, temp2);
		pb = pb->prior;
	}
	if (temp1 != 0) InsertDataAtHead(c, 1);
	return c;
}

//a和b是一正一负的情况
BaseElem Sub(BaseElem a, BaseElem b)
{
	BaseElem c = CreatList(b->data);//可能首位会发生变化
	BaseElem pa, pb, pc;
	int temp1 = 0, temp2;
	pa = a->prior;
	pb = b->prior;
	while (pa != a && pb != b)
	{
		temp2 = pa->data - pb->data - temp1;
		if (temp2 >= 0) temp1 = 0;
		else
		{
			temp2 = temp2 + 10000;
			temp1 = 1;
		}
		InsertDataAtHead(c, temp2);
		pa = pa->prior;
		pb = pb->prior;
	}
	if (pb == b && temp1 == 0) c->data = a->data;//a大于b且进位为0
	if (c->data != a->data)//b大于a，进位不一定为0
	{
		pc = c->prior;
		pc->data = 10000 - pc->data;
		pc = pc->prior;
		while (pc != c)
		{
			pc->data = 9999 - pc->data;
			pc = pc->prior;
		}
		temp1 = temp1 ? 0 : 1;//进位转换
		while (pb != b)
		{
			if (pb->data >= temp1)
			{
				temp2 = pb->data - temp1;
				temp1 = 0;
			}
			else
			{
				temp2 = 10000 + pb->data - temp1;
				temp1 = 1;
			}
			InsertDataAtHead(c, temp2);
			pb = pb->prior;
		}
	}
	else//a大于b，进位不为0
	{
		while(pa != a)
		{
			if(pa->data >= temp1)
			{
				temp2 = pb->data - temp1;
				temp1 = 0;
			}
			else
			{
				temp2 = 10000 + pb->data -temp1;
				temp1 = 1;
			}
			InsertDataAtHead(c, temp2);
			pa = pa->prior;
		}
	}
	pc = c->next;
	while(pc->next != c && pc->data == 0)//删除最左边的0
	{
		DelData(c, pc);
		pc = pc->next;
	}
	return c;
}

//在L中删除节点p
void DelData(BaseElem L, BaseElem p)
{
    p->prior->next = p->next;
    p->next->prior = p->prior;
    free(p);
}

int main(void)
{
	BaseElem a, b, c;
	a = InputData();
	b = InputData();
	c = AddData(a, b);
	printf("The sum is:");
	PrintList(c);
	printf("over\n");
	return 0;
}

 */
