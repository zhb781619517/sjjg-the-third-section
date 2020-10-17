//队列及其相关操作
#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Elem;

typedef struct
{
    Elem data;
    struct QNode *next;
}QNode,* QueuePtr;

typedef struct
{
    QueuePtr head;
    QueuePtr end;
}QueueList;

QueueList InitQueue();
void DestroyQueue(QueueList);
void ClearQueue(QueueList);
int QueueEmpty(QueueList);
int QueueLength(QueueList);
Elem GetHead(QueueList);
void EnQueue(QueueList,Elem);
Elem DeQueue(QueueList);
void QueueRead(QueueList);

int main()
{
    char c;
    Elem ha;
    QueueList a;
    printf("1.建立一个空队列\n2.清除队列\n3.判断队列是否为空\n4.得到队列长度\n5.得到队列头元素（非出队）\n6.入队\n7.出队\n8.读出该队列\n\n输入其他键销毁队列并退出程序\n\n");
    printf("\n请输入你需要执行的操作：");
    while((c=getchar())!='\n')
    {
        switch(c)
        {
            case '1':
                a=InitQueue();
                break;
            case '2':
                ClearQueue(a);
                break;
            case '3':
                if(QueueEmpty(a))
                {
                    printf("队列为空\n");
                }
                else
                {
                    printf("队列非空\n");
                }
                break;
            case '4':
                printf("队列长度为%d\n",QueueLength(a));
                break;
            case '5':
                if(QueueEmpty(a))
                {
                    printf("队列为空，无法执行当前操作！\n");
                }
                else
                {
                    printf("该队列头元素的值为：%d\n",GetHead(a));
                }
                break;
            case '6':
                printf("请输入你想插入的元素：");
                scanf("%d",&ha);
                EnQueue(a,ha);
                break;
            case '7':
                printf("出队成功，该队列头元素的值为：%d\n",DeQueue(a));
                break;
            case '8':
                QueueRead(a);
            default:
                DestroyQueue(a);
        }
        printf("\n请输入你需要执行的操作：");
        while(getchar()!='\n'){}
    }
    return 0;
}

QueueList InitQueue()
{
    QueueList p;
    QueuePtr r;
    r=(QueuePtr)malloc(sizeof(QNode));
    if(!r)
    {
        printf("申请内存失败！\n");
        exit(1);
    }
    r->next=NULL;
    p.head=p.end=r;
    printf("Success to creat a QueueList!\n");
    return p;
}

void DestroyQueue(QueueList a)
{
    QueuePtr p,q;
    if(a.head==a.end)
    {
        free(a.head);
    }
    p=a.head;
    q=p->next;
    do
    {
        free(p);
        p=q;
        q=q->next;
    }while(p->next);
}

void ClearQueue(QueueList a)
{
    if(QueueEmpty(a))
    {
        printf("队列为空，无法执行当前操作！\n");
        return;
    }
    QueuePtr p,q;
    p=a.head->next;
    q=p->next;
    while(p)
    {
        free(p);
        p=q;
        q=q->next;
    }
}

int QueueEmpty(QueueList a)
{
    if(a.end==a.head)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int QueueLength(QueueList a)
{
    QueuePtr p=a.head;
    int temp=0;
    while(p->next)
    {
        temp++;
    }
    return temp;
}

Elem GetHead(QueueList a)
{
    QueuePtr p;
    p=a.head->next;
    if(p->next)
    {
        printf("OK!\n");
        return p->data;
    }
    else
    {
        printf("ERROR!\n");
        return 0;
    }
}

void EnQueue(QueueList a,Elem b)
{
    QueuePtr p,q;
    p=(QueuePtr)malloc(sizeof(QNode));
    p->data=b;
    q=a.end;
    p->next=q->next;
    q->next=p;
    a.end=p;
    printf("Success to EnQueue!\n");
}

Elem DeQueue(QueueList a)
{
    Elem temp;
    QueuePtr p,q;
    if(a.end==a.head)
    {
        printf("ERROR!\n");
        exit(1);
    }
    p=a.head->next;
    a.head->next=p->next;
    free(p);
    printf("Success to DeQueue!\n");
    return temp;
}

void QueueRead(QueueList a)
{
    if(QueueEmpty(a))
    {
        printf("队列为空！\n");
        return;
    }
    QueuePtr p;
    p=a.head->next;
    while(p)
    {
        printf("%5d",p->data);
    }
}
