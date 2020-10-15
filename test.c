#include<stdio.h>
#include<stdlib.h>
#define N 2             //ͣ������С
#define FEE 10          //ÿСʱ���շ�

typedef struct {
    int num;
    int time;
}Car;                   //ÿ��������������Ϣ

typedef struct {
    Car data;
    struct QNode* next;
}QNode, * QueuePtr;     //���������е�׼��

typedef struct {
    QueuePtr front;
    QueuePtr rear;
    int length;
}*QueueList, QListNode; //��������֮��ĺ����п��Ե�ָ�����

typedef struct {
    Car data[N];
    int num;
}pkNode, * pk;          //ͣ������ջ����

void Push(pk, Car);
void SPop(pk, pk);            //��ǰ��ĳ�ջ����������ջ
void Qpush(QueueList, Car);
void QPop(QueueList, pk);

int main()
{
    pk packing1, packing2;
    QueueList lins = (QueueList)malloc(sizeof(QListNode));
    QueuePtr a = (QueuePtr)malloc(sizeof(QNode));                   //�����յ�������
    a->next = NULL;                                                 //������
    lins->front = lins->rear = a;                                   //�������ͷ��β
    Car b;                                                          //�����н�
    char c;
    packing1 = (pk)malloc(sizeof(pkNode));
    packing2 = (pk)malloc(sizeof(pkNode));                          //����ͣ�����ڴ�
    packing1->num = packing2->num = lins->length = 0;
    int i, j, k;
    while (1)                                                       //����ѭ�����ڲ�break�˳�
    {                                                                                                       //�涨ջ���±�Ϊ���ջ���±�Ϊ0
        j = 0;                                                                                              //������ͷ�����ӣ�β�����
        printf("��ʦ��������������·!\n");
        scanf("%c %d %d", &c, &b.num, &b.time);                     //��������
        if (c == 'A')
        {
            if (packing1->num > 1)
            {
                Qpush(lins, b);                                                     //���ͣ�������ˣ������������������
                printf("λ�ڱ��%dλ�ã���ͣ�������˳�ȥ�󷽿�����\n", lins->length);
            }
            else
            {
                Push(packing1, b);                                                  //���ͣ�����п��࣬�������ջ��
                printf("λ��ͣ����%dλ��\n", packing1->num);
            }
        }
        else if (c == 'D')
        {
            for (i = N-1 ; i >= 0 ; i)
            {
                if (packing1->data[i].num == b.num)                                 //�������ҵ����ƺ���ͬ�����ݣ���������
                {
                    k = b.time - packing1->data[i].time;
                    printf("���ƺ�%d����%dͣ��%d����%dʱ�䣬�շѽ��Ϊ%d\n", packing1->data[i].num, packing1->data[i].time, b.time, k, k * FEE);
                    break;
                }
                else
                {
                    SPop(packing1, packing2);                                       //��ǰ��Ԫ�ط�����ʱջ
                    j++;
                }
            }
            for (; j >= 0; j--)
            {
                SPop(packing2, packing1);                                           //����ʱջԪ�طŻ�ͣ����ջ
            }
            if (lins->front != lins->rear)
            {
                QPop(lins, packing1);                                               //������в��ǿն��У�����ӣ�������Ԫ�ط���ͣ����
            }
            //����packing1�������ָ��Ԫ�ؾͷŵ�packing2��ֱ���ҵ�Ȼ��ȡ����Ȼ���ٰ�packing2�ķŻ�ȥ
        }
        else if (c == 'E')
        {
            printf("������\n");
            break;
        }
        while (getchar() != '\n') {}                                                //��ȥ�ڻ���������Ԫ���뻻�з�
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
