#include<stdio.h>
#include<stdlib.h>
#define N 2             //停车场大小
#define FEE 10          //每小时的收费

typedef struct {
    int num;
    int time;
}Car;                   //每辆车所包含的信息

typedef struct {
    Car data;
    struct QNode* next;
}QNode, * QueuePtr;     //建立链队列的准备

typedef struct {
    QueuePtr front;
    QueuePtr rear;
    int length;
}*QueueList, QListNode; //链队列在之后的函数中可以的指针调用

typedef struct {
    Car data[N];
    int num;
}pkNode, * pk;          //停车场的栈类型

void Push(pk, Car);
void SPop(pk, pk);            //把前面的出栈，放入后面的栈
void Qpush(QueueList, Car);
void QPop(QueueList, pk);

int main()
{
    pk packing1, packing2;
    QueueList lins = (QueueList)malloc(sizeof(QListNode));
    QueuePtr a = (QueuePtr)malloc(sizeof(QNode));                   //建立空的链队列
    a->next = NULL;                                                 //初定向
    lins->front = lins->rear = a;                                   //赋予队列头和尾
    Car b;                                                          //输入中介
    char c;
    packing1 = (pk)malloc(sizeof(pkNode));
    packing2 = (pk)malloc(sizeof(pkNode));                          //申请停车场内存
    packing1->num = packing2->num = lins->length = 0;
    int i, j, k;
    while (1)                                                       //永真循环，内部break退出
    {                                                                                                       //规定栈顶下标为最后，栈底下标为0
        j = 0;                                                                                              //队列在头部出队，尾部入队
        printf("洪师傅，尝试切他中路!\n");
        scanf("%c %d %d", &c, &b.num, &b.time);                     //输入数据
        if (c == 'A')
        {
            if (packing1->num > 1)
            {
                Qpush(lins, b);                                                     //如果停车场满了，则将其放入便道即队列中
                printf("位于便道%d位置，待停车场有人出去后方可入内\n", lins->length);
            }
            else
            {
                Push(packing1, b);                                                  //如果停车场有空余，则将其放入栈顶
                printf("位于停车场%d位置\n", packing1->num);
            }
        }
        else if (c == 'D')
        {
            for (i = N-1 ; i >= 0 ; i)
            {
                if (packing1->data[i].num == b.num)                                 //遍历来找到车牌号相同的数据，并做处理
                {
                    k = b.time - packing1->data[i].time;
                    printf("车牌号%d，由%d停到%d，共%d时间，收费金额为%d\n", packing1->data[i].num, packing1->data[i].time, b.time, k, k * FEE);
                    break;
                }
                else
                {
                    SPop(packing1, packing2);                                       //将前置元素放入临时栈
                    j++;
                }
            }
            for (; j >= 0; j--)
            {
                SPop(packing2, packing1);                                           //将临时栈元素放回停车场栈
            }
            if (lins->front != lins->rear)
            {
                QPop(lins, packing1);                                               //如果队列不是空队列，则出队，将出队元素放入停车场
            }
            //遍历packing1如果不是指定元素就放到packing2，直到找到然后取出，然后再把packing2的放回去
        }
        else if (c == 'E')
        {
            printf("结束！\n");
            break;
        }
        while (getchar() != '\n') {}                                                //除去在缓冲区的杂元素与换行符
    }
}

void Push(pk a, Car b)
{
    a->data[a->num].num = b.num;
    a->data[a->num].time = b.time;
    a->num++;
}
void SPop(pk a1, pk a2)
{
    Push(a2, a1->data[a1->num]);
    a1->num--;
}
void Qpush(QueueList a, Car b)
{
    QueuePtr temp = (QueuePtr)malloc(sizeof(QNode));
    temp->data.num = b.num;
    temp->data.time = b.time;
    temp->next = a->rear->next;
    a->rear->next = temp;
    a->length++;
}

void QPop(QueueList a, pk b)
{
    QueuePtr p, q;
    a->length--;
    p = a->front;
    q = p->next;
    p->next = q->next;
    Push(b, q->data);
    a->length--;
}
