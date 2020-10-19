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
	//构造一个空栈
	S.num=0;
	return OK;
}

Status GetTop(SqStack S,SElemType &e){
	//若栈不空，则用e返回栈顶元素
	int i=S.num;
	if(S.num==0) return ERROR;
	e.id=S.data[i].id;
	e.location=i;
	e.startTime=S.data[i].startTime;
	return OK; 
}

Status Push(SqStack &S,SElemType e){
	//插入新的元素e作为新的栈顶元素
	S.num+=1;
	int i=S.num;
	S.data[i].id=e.id;
	S.data[i].startTime=e.startTime;
	S.data[i].location=i;
	return OK;
}

Status Pop(SqStack &S,SElemType &e){
	//若栈不空，则删除栈顶元素，并用e返回
	if(S.num==0) return ERROR;
	int i=S.num;
	e.id=S.data[i].id;
	e.location=i;
	e.startTime=S.data[i].startTime;
	S.num-=1;
	return OK; 
}

Status InitQueue(LinkQueue &Q){
	//构造一个空队列 
	Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.front) exit(OVERFLOW);
	Q.rear->data.location=0;
	Q.front->next=NULL;
	return OK;
}

Status EnQueue(LinkQueue &Q,QElemType e){
	//插入元素e作为新的队尾元素 
	QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
	if(!p) exit(OVERFLOW);
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK; 
}

Status DeQueue(LinkQueue &Q,QElemType &e){
	//若队列不空，则删除Q的队头元素并用e返回其值
	if(Q.front==Q.rear) return ERROR;
	QueuePtr p=Q.front->next;
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;
	free(p);
	return OK;
}

Status ArriveQueue(LinkQueue &Q,QElemType e){
	//进入便道 
	if(Q.front->next==NULL){
		e.location=1;
	}else{
		int loc=Q.rear->data.location;
		e.location=loc+1;
	}
	EnQueue(Q,e);
	printf("车辆%d进入便道，车辆在便道上的位置为：%d\n",e.id,e.location);
	return OK;
}

Status ArriveStack(SqStack &S,SElemType e){
	//进入停车场
	Push(S,e);
	printf("车辆%d进入停车场，车辆在停车场的位置为：%d\n",e.id,S.num);
	return OK;
}

Status DepartQueue(LinkQueue &Q,QElemType &e){
	//离开便道,进入停车场
	DeQueue(Q,e);
	QueuePtr p=Q.front->next;
	while(p!=NULL){
		p->data.location--;
		p=p->next;
	}
	printf("车辆%d离开便道进入停车场\n",e.id);
	return OK;
}

Status DepartStack(SqStack &S,SqStack &S2,SElemType e,float price){
	//离开停车场
	SElemType t;
	SElemType tt;
	GetTop(S,tt);
	while(tt.id!=e.id){
		//停车场外围的车辆驶出到另一个栈，为要离去的车辆让路 
		Pop(S,t);
		Push(S2,t);
		GetTop(S,tt);
	}
	Pop(S,t);
	int totalTime=e.endTime-t.startTime;
	float totalPrice=totalTime*price;
	printf("车辆%d离开停车场，车辆停留时间为：%d,车辆需缴纳费用为：%.2f\n",t.id,totalTime,totalPrice);
	while(S2.num!=0){
		//让路的车辆回到停车场，位置减1 
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
		printf("请输入车辆信息：\n");
		scanf("%c%d%d%*c",&c,&id,&time);
		es.id=id;
		if(c=='E'){
			break;
		}else if(c=='A'){
			if(S.num>=N){
				//停车场满，车辆进入便道 
				eq.id=id;
				ArriveQueue(Q,eq);
			}else{
				//车辆进入停车场 
				es.id=id;
				es.startTime=time;
				ArriveStack(S,es);
			}
		}else if(c=='D'){
			es.id=id;
			es.endTime=time;
			if(Q.front==Q.rear){
				//便道上没有车辆 
				DepartStack(S,S2,es,price);
			}else{
				//便道上有车辆，该车辆驶离停车场后便道上的车驶入停车场 
				DepartStack(S,S2,es,price);
				DepartQueue(Q,eq);
				es.id=eq.id;
				es.startTime=time;
				ArriveStack(S,es);
			}
		}else{
			printf("输入有误，请重新输入。\n");
		}
	}
	return 0;
}

