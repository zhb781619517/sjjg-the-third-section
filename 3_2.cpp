#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define N 2
#define FEE 10

typedef int Status;

typedef struct{
	int id;
	int startTime;
	int endTime;
	int location;
}SElemType;

typedef struct{
	SElemType data[N+1];
	int num;
}SqStack;

typedef struct{
	int id;
	int location;
}QElemType;

typedef struct QNode{
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitStack(SqStack &S){
	//����һ����ջ
	S.num=0;
	return OK;
}

Status GetTop(SqStack S,SElemType &e){
	//��ջ���գ�����e����ջ��Ԫ��
	int i=S.num;
	if(S.num==0) return ERROR;
	e.id=S.data[i].id;
	e.location=i;
	e.startTime=S.data[i].startTime;
	return OK; 
}

Status Push(SqStack &S,SElemType e){
	//�����µ�Ԫ��e��Ϊ�µ�ջ��Ԫ��
	S.num+=1;
	int i=S.num;
	S.data[i].id=e.id;
	S.data[i].startTime=e.startTime;
	S.data[i].location=i;
	return OK;
}

Status Pop(SqStack &S,SElemType &e){
	//��ջ���գ���ɾ��ջ��Ԫ�أ�����e����
	if(S.num==0) return ERROR;
	int i=S.num;
	e.id=S.data[i].id;
	e.location=i;
	e.startTime=S.data[i].startTime;
	S.num-=1;
	return OK; 
}

Status InitQueue(LinkQueue &Q){
	//����һ���ն��� 
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(OVERFLOW);
	Q.rear->data.location=0;
	Q.front->next=NULL;
	return OK;
}

Status EnQueue(LinkQueue &Q,QElemType e){
	//����Ԫ��e��Ϊ�µĶ�βԪ�� 
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK; 
}

Status DeQueue(LinkQueue &Q,QElemType &e){
	//�����в��գ���ɾ��Q�Ķ�ͷԪ�ز���e������ֵ
	if(Q.front==Q.rear) return ERROR;
	QueuePtr p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;
	free(p);
	return OK;
}

Status ArriveQueue(LinkQueue &Q,QElemType e){
	//������ 
	if(Q.front->next==NULL){
		e.location=1;
	}else{
		int loc=Q.rear->data.location;
		e.location=loc+1;
	}
	EnQueue(Q,e);
	printf("����%d�������������ڱ���ϵ�λ��Ϊ��%d\n",e.id,e.location);
	return OK;
}

Status ArriveStack(SqStack &S,SElemType e){
	//����ͣ����
	Push(S,e);
	printf("����%d����ͣ������������ͣ������λ��Ϊ��%d\n",e.id,S.num);
	return OK;
}

Status DepartQueue(LinkQueue &Q,QElemType &e){
	//�뿪���,����ͣ����
	DeQueue(Q,e);
	QueuePtr p=Q.front->next;
	while(p!=NULL){
		p->data.location--;
		p=p->next;
	}
	printf("����%d�뿪�������ͣ����\n",e.id);
	return OK;
}

Status DepartStack(SqStack &S,SqStack &S2,SElemType e,float price){
	//�뿪ͣ����
	SElemType t;
	SElemType tt;
	GetTop(S,tt);
	while(tt.id!=e.id){
		//ͣ������Χ�ĳ���ʻ������һ��ջ��ΪҪ��ȥ�ĳ�����· 
		Pop(S,t);
		Push(S2,t);
		GetTop(S,tt);
	}
	Pop(S,t);
	int totalTime=e.endTime-t.startTime;
	float totalPrice=totalTime*price;
	printf("����%d�뿪ͣ����������ͣ��ʱ��Ϊ��%d,��������ɷ���Ϊ��%.2f\n",t.id,totalTime,totalPrice);
	while(S2.num!=0){
		//��·�ĳ����ص�ͣ������λ�ü�1 
		Pop(S2,t);
		t.location--;
		Push(S,t);
	}
	return OK;
}

int main(){
	SqStack S;
	SqStack S2;
	LinkQueue Q;
	InitQueue(Q);
	int id,time;
	char c;
	int n;
	float price;
	SElemType es;
	QElemType eq;
	InitStack(S);
	InitStack(S2);
	price=FEE;
	while(1){
		printf("�����복����Ϣ��\n");
		scanf("%c%d%d%*c",&c,&id,&time);
		es.id=id;
		if(c=='E'){
			break;
		}else if(c=='A'){
			if(S.num>=N){
				//ͣ������������������ 
				eq.id=id;
				ArriveQueue(Q,eq);
			}else{
				//��������ͣ���� 
				es.id=id;
				es.startTime=time;
				ArriveStack(S,es);
			}
		}else if(c=='D'){
			es.id=id;
			es.endTime=time;
			if(Q.front==Q.rear){
				//�����û�г��� 
				DepartStack(S,S2,es,price);
			}else{
				//������г������ó���ʻ��ͣ���������ϵĳ�ʻ��ͣ���� 
				DepartStack(S,S2,es,price);
				DepartQueue(Q,eq);
				es.id=eq.id;
				es.startTime=time;
				ArriveStack(S,es);
			}
		}else{
			printf("�����������������롣\n");
		}
	}
	return 0;
}

