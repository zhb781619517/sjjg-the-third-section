//队列 及其相关操作 
#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Elem;

typedef struct QNode {
	Elem data;
	struct QNode *next;
} QNode,* QueuePtr;

typedef struct {
	QueuePtr head;
	QueuePtr end;
} QueueList;

void DestroyQueue(QueueList);
void ClearQueue(QueueList*);
int QueueEmpty(QueueList);
int QueueLength(QueueList);
Elem GetHead(QueueList);
void EnQueue(QueueList*,Elem);
Elem DeQueue(QueueList);
void QueueRead(QueueList);

int main() {
	char c;
	Elem ha;
	QueueList a;
	QueuePtr r;
	printf("1.建立一个空队列\n2.清除队列\n3.判断队列是否为空\n4.得到队列长度\n5.得到队列头元素（非出队）\n6.入队\n7.出队\n8.读出该队列\n\n输入其他键销毁队列并退出程序\n\n");
	printf("\n请输入你需要执行的操作：");
	while((c=getchar())!='\n') {
		switch(c) {
			case '1':
				r=(QueuePtr)malloc(sizeof(QNode));
				r->next==NULL;
				a.end=a.head=r;
				if(a.end==a.head) {
					printf("Successful!\n");
				}
				break;
			case '2':
				ClearQueue(&a);
				break;
			case '3':
				if(QueueEmpty(a)) {
					printf("队列为空\n");
				} else {
					printf("队列非空\n");
				}
				break;
			case '4':
				printf("队列长度为%d\n",QueueLength(a));
				break;
			case '5':
				if(QueueEmpty(a)) {
					printf("队列为空，无法执行当前操作！\n");
				} else {
					printf("该队列头元素的值为：%d\n",GetHead(a));
				}
				break;
			case '6':
				printf("请输入你想插入的元素：");
				scanf("%d",&ha);
				EnQueue(&a,ha);
				break;
			case '7':
				printf("出队成功，该队列头元素的值为：%d\n",DeQueue(a));
				break;
			case '8':
				QueueRead(a);
				break;
			default:
				DestroyQueue(a);
		}
		printf("\n请输入你需要执行的操作：");
		while(getchar()!='\n') {}
	}
	return 0;
}

void DestroyQueue(QueueList a) {
	QueuePtr p=a.end,q;
	while(p!=NULL) {
		q=p;
		p=p->next;
		free(q);
	}
	printf("Successful!\n");
}
void ClearQueue(QueueList *a) {
/*	QueuePtr p=a->end->next,q;
	while(p!=NULL) {
		q=p;
		p=p->next;
		free(q);
	}
	a->end=a->head;
	printf("Successful!\n");*/
	while(a->end==a->head) {
		DeQueue(*a);
	}
	a->end=a->head;
	printf("Successful!\n");
}
int QueueEmpty(QueueList a) {
	if(a.end==a.head) {
		return TRUE;
	} else {
		return FALSE;
	}
}
int QueueLength(QueueList a) {
	int temp=0;
	QueuePtr p=a.end;
	while(p!=a.head) {
		temp++;
		p=p->next;
	}
	return temp;
}
Elem GetHead(QueueList a) {
	return a.head->data;
}
void EnQueue(QueueList *a,Elem b) {
	QueuePtr p=malloc(sizeof(QNode));
	p->data=b;
	p->next=a->head->next;
	a->head->next=p;
	a->head=p;
}
Elem DeQueue(QueueList a) {
	QueuePtr p=a.end->next;
	Elem temp;
	temp=a.end->next->data;
	a.end->next=p->next;
	free(p);
	return temp;
}
void QueueRead(QueueList a) {
	QueuePtr p=a.end;
	while(p!=a.head) {
		p=p->next;
		printf("%d\t",p->data);
	}
	printf("\nSuccessful!\n");
}
