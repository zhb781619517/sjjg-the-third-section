//���м�����ز���
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
    printf("1.����һ���ն���\n2.�������\n3.�ж϶����Ƿ�Ϊ��\n4.�õ����г���\n5.�õ�����ͷԪ�أ��ǳ��ӣ�\n6.���\n7.����\n8.�����ö���\n\n�������������ٶ��в��˳�����\n\n");
    printf("\n����������Ҫִ�еĲ�����");
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
                    printf("����Ϊ��\n");
                }
                else
                {
                    printf("���зǿ�\n");
                }
                break;
            case '4':
                printf("���г���Ϊ%d\n",QueueLength(a));
                break;
            case '5':
                if(QueueEmpty(a))
                {
                    printf("����Ϊ�գ��޷�ִ�е�ǰ������\n");
                }
                else
                {
                    printf("�ö���ͷԪ�ص�ֵΪ��%d\n",GetHead(a));
                }
                break;
            case '6':
                printf("��������������Ԫ�أ�");
                scanf("%d",&ha);
                EnQueue(a,ha);
                break;
            case '7':
                printf("���ӳɹ����ö���ͷԪ�ص�ֵΪ��%d\n",DeQueue(a));
                break;
            case '8':
                QueueRead(a);
            default:
                DestroyQueue(a);
        }
        printf("\n����������Ҫִ�еĲ�����");
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
        printf("�����ڴ�ʧ�ܣ�\n");
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
        printf("����Ϊ�գ��޷�ִ�е�ǰ������\n");
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
        printf("����Ϊ�գ�\n");
        return;
    }
    QueuePtr p;
    p=a.head->next;
    while(p)
    {
        printf("%5d",p->data);
    }
}
