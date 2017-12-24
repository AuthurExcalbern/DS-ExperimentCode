/* 数据结构实验测试 2017-12-12
 * 
 * 要求：
 * 建立一个单向循环列表，节点里存储一个字符
 * 每次遇到与头指针同样的字符则把前面所有于头指针不同的字符连成单向循环列表
 * 用一个数组存储分出来的头指针
 */

#include<stdio.h>
#include<stdlib.h>

typedef struct node * list;
typedef struct node * per;

list createlist(char x);//创建循环链表，并在头指针节点存字符x
void inser(char x,list l);//在表尾插入字符x
per newlist(per p, list t);//把p的指针联到t，形成一个新的循环链表

struct node
{
    char c;
    per next;
};

list createlist(char x)
{
    list l;
    l = (list)malloc(sizeof(struct node));
    l->c = x;
    l->next = l;
    return l;
}

void inser(char x,list l)
{
    per t;
    per temp;
    t = (per)malloc(sizeof(struct node));
    t->c = x;
    t->next = l;
    temp = l->next;
    while(temp->next != l) temp = temp->next;
    temp->next = t;
}

per newlist(per p, list t)
{
    p->next = t;
    return t;
}

int main(void)
{
    list l;
    list ans[10];
    per p, pp, temp;
    int n, cnt = 0;
    char t;
    int first = 1, i;
    
    //输入数据
    scanf("%d", &n);getchar();
    for(i = 0; i < n; i++)
    {
        scanf("%c", &t);getchar();
        if(first)
		{l = createlist(t);first = 0;}
        else
            inser(t, l);
    }
    
    
    p = l->next;
    pp = l;//因为非双向链表，所以用一个指针存储前面的节点
    temp = l;
    t = l->c;
    
    //进行分表
    while(p != l)
    {
        if(p->c == t)
        {
            ans[cnt] = newlist(pp, temp);
            temp = p;
            cnt++;
        }
        pp = p;p = p->next;
    }
    ans[cnt] = newlist(pp, temp);//补上最后一个还
    
    //对单向循环链表进行输出
    for(i = 0; i <= cnt; i++)
    {
        p = ans[i];
        printf("%c", t);
        while(p->next->c != t)
        {
            printf("%c", p->next->c);
            p = p->next;
        }
        printf("\n");
    }
    
    return 0;
}