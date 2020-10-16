#include<stdio.h>
#include<stdlib.h>
#define N 2             //停车场大小
#define FEE 10          //每小时的收费

typedef struct {
    int num;
    int time;
}Car;                   //每辆车所包含的信息

typedef struct QNode {
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

void QPush(QueueList, Car);
Car QPop(QueueList);
void SPush(pk, Car);
Car SPop(pk);

int main()
{
    pk packing1, packing2;
    QueueList Q = (QueueList)malloc(sizeof(QListNode));
    QueuePtr a = (QueuePtr)malloc(sizeof(QNode));                   //建立空的链队列
    //Q->next = NULL;                                                 //初定向
    Q->front = Q->rear = a;                                   //赋予队列头和尾
    Car b, c;                                                          //输入中介
    char d;
    packing1 = (pk)malloc(sizeof(pkNode));
    packing2 = (pk)malloc(sizeof(pkNode));                          //申请停车场内存
    packing1->num = packing2->num = Q->length = 0;
    int i, j, k, h;
    while (1)
    {
        j=0;
        printf("请输入：\n");
        scanf("%c %d %d", &d, &b.num, &b.time);
        if (d == 'E')
        {
            printf("结束\n");
            break;
        }
        else if (d == 'A')
        {
            if (packing1->num > N - 1)
            {
                QPush(Q, b);
                printf("车牌%d，时间%d，便道位置%d\n",b.num,b.time,Q->length);
            }
            else
            {
                SPush(packing1, b);
                printf("车牌%d，时间%d，停车场位置%d\n",b.num,b.time,packing1->num);
            }
        }
        else if (d == 'D')
        {
            for(i=N-1;i>=0;i++)
            {
                if(packing1->data[i].num==b.num)
                {
                    k=b.time-packing1->data[i].time;
                    printf("开始时间%d，结束时间%d，经过的时间%d，收费%d\n",packing1->data[i].time,b.time,k,k*FEE);
                    h=b.num;
                    SPop(packing1);
                    break;
                }
                else
                {
                    c=SPop(packing1);
                    SPush(packing2,c);
                    j++;
                }
            }
            for(;j>0;j--)
            {
            	printf("hhh\n");
                c=SPop(packing2);
                SPush(packing1,c);
            }
            if(Q->length)
            {
                c=QPop(Q);
                c.time=h;
                SPush(packing1,c);
                printf("车牌号为%d的车辆从便道进入停车场%d处，进入停车场的时间为%d\n",c.num,packing1->num,h);
            }
        }
        while(getchar()!='\n'){}
    }
    return 0;
}

void QPush(QueueList a, Car b)          //尾部入，头部出
{
    QueuePtr temp=malloc(sizeof(QNode));
    temp->data.num=b.num;
    temp->data.time=b.time;
    temp->next=a->rear->next;
    a->rear->next=temp;
    a->rear=temp;
    a->length++;
}

Car QPop(QueueList a)
{
    Car temp;
    temp.num=a->front->data.num;
    temp.time=a->front->data.time;
    a->length--;
    return temp;
}

void SPush(pk a, Car b)
{
    a->data[a->num].num=b.num;
    a->data[a->num].time=b.time;
    a->num++;
}

Car SPop(pk a)
{
    Car temp;
    temp.num=a->data[a->num].num;
    temp.time=a->data[a->num].time;
    a->num--;
    return temp;
}
