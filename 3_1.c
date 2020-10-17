#include<stdio.h>
#include<stdlib.h>

typedef int Elem;
typedef struct SNode{
	Elem data;
	struct SNode* next;
}SNode,*StackList;

StackList Stack_Initial();
void SPush(StackList,Elem);
Elem SPop(StackList);
int Stack_Length(StackList);
Elem Stack_Gettop(StackList);
void Stack_Clear(StackList);
void Stack_Read(StackList); 
void Stack_Destory(StackList);
int main()
{
	int i,j,k,c;
	Elem ha;
	StackList a=NULL;
	printf("1.����һ����ջ\n2.��ջ\n3.��ջ\n4.���ջ�ĳ���\n5.�õ�ջ��Ԫ�أ��ǳ�ջ��\n6.���ջ\n7.����ջ\n\n��������������ջ���˳�����\n\n");
    printf("\n����������Ҫִ�еĲ�����");
    while(1)
    {
    	printf("�����룺");
    	scanf("%d",&c);
        switch(c)
        {
            case 1:
                a=Stack_Initial();
                a->next=NULL;
                break;
            case 2:
            	if(a)
            	{
            		printf("��������ջԪ�أ�");
					scanf("%d",&ha); 
                	SPush(a,ha);
            	}
            	else
            	{
            		printf("����ʧ�ܣ���ջδ������\n");
            		continue;
				}
                break;
            case 3:
            	if(!a)
            	{
               		printf("����ʧ�ܣ���ջδ������\n");
            		continue;
				}
            	else if(Stack_Length(a)==0)
            	{
            		printf("����ʧ�ܣ���ջΪ�գ�\n");
				}
            	printf("��ջ�ɹ���ջ��Ԫ��Ϊ��%d\n",SPop(a));
                break;
            case 4:
            	if(!a)
            	{
            		printf("����ʧ�ܣ���ջδ������\n");
				}
                printf("ջ����Ϊ%d\n",Stack_Length(a));
                break;
            case 5:
            	if(!a)
            	{
               		printf("����ʧ�ܣ���ջδ������\n");
            		continue;
				}
            	else if(Stack_Length(a)==0)
            	{
            		printf("����ʧ�ܣ���ջΪ�գ�\n");
				}
            	printf("ջ��Ԫ��Ϊ%d\n",Stack_Gettop(a));
                break;
            case 6:
               	if(!a)
            	{
               		printf("����ʧ�ܣ���ջδ������\n");
            		continue;
				}
            	Stack_Clear(a);
                break;
            case 7:
              	if(!a)
            	{
               		printf("����ʧ�ܣ���ջδ������\n");
            		continue;
				}
                Stack_Read(a);
                break;
            default:
                Stack_Destory(a);
                return 0;
        }
        printf("\n����������Ҫִ�еĲ�����");
        while(getchar()!='\n'){}
    }
}

StackList Stack_Initial()
{
	StackList p=malloc(sizeof(SNode));
	p->next=NULL;
	printf("Successful!\n");
	return p;
}
void SPush(StackList a,Elem b)
{
	StackList p=malloc(sizeof(SNode));
	p->data=b;
	p->next=a->next;
	a->next=p;
	printf("Successful!\n");
}
Elem SPop(StackList a)
{
	StackList p;
	Elem temp;
	p=a->next;
	temp=p->data;
	a->next=p->next;
	free(p);
	return temp;
}
int Stack_Length(StackList a)
{
	int temp=0;
	StackList p;
	p=a;
	while(p->next)
	{
		temp++;
		p=p->next;
	}
	return temp;
}
Elem Stack_Gettop(StackList a)
{
	StackList p=a->next;
	return p->data;
}
void Stack_Clear(StackList a)
{
    StackList r=a,p;
    int i,length=Stack_Length(a);
    for(i=0;i<=length;i++)
    {
        p=r->next;
        free(r);
        r=p;
    }
    printf("Successful!\n");
}
void Stack_Read(StackList a)
{
	StackList p;
	p=a;
	printf("��ջ����ջ��Ϊ��\n");
	while(p->next)
	{
		p=p->next;
		printf("%d\n",p->data);
	}
}
void Stack_Destory(StackList a)
{
/*	StackList p,q;
	p=a;
	q=p->next;
	while(p->next)
	{
		p=q;
		q=q->next;
		free(p);
	}
	free(a);*/
    StackList r=a,p;
    int i,length=Stack_Length(a);
    for(i=0;i<=length;i++)
    {
        p=r->next;
        free(r);
        r=p;
    }
    printf("Successful!\n");
}

