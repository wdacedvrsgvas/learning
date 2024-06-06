#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define getjcb(type) (type *)malloc(sizeof(type))
#define getsub(type) (type *)malloc(sizeof(type))

int num,num2;         //需要调度的作用数和要回收的区域数
int m=0;             //当前已分配的内存块数
int flag;             //成功分配的标志
int isup,isdown;      //回收区存上下
int is=0;

struct jcb{
    char name[10];
    char state;
    int ntime;
    int size;
    int addr;
    struct jcb *link;
}*ready=NULL,*p,*q,*as=NULL;
    typedef struct jcb JCB;

struct subarea{
    char name[10];
    int addr;
    int size;
    char state;
    struct subarea *link;
}*sub=NULL,*r,*s,*cur;
    typedef struct subarea SUB;

void sort()
{
    JCB *first;
    if(ready==NULL) ready=p;
    else{
        first=ready;
        while(first->link!=NULL)
        first=first->link;
        first->link=p;
        p->link=NULL;
    }
}

void sort3()
{
    JCB *fir;
    if(as==NULL) as=q;
    else{
        fir=as;
        while(fir->link!=NULL)
        fir=fir->link;
        fir->link=q;
        q->link=NULL;
    }
    m++;
}

void input()
{
    int i;
    printf("\n请输入需要调度的作业数:")
    scanf("%d",&num);
    for(i=0;i<num;i++)
    {
        print("\n作用号No.%d:\n",i);
        p=getjcb(JCB);
        printf("\n请输入作业名：");
        scanf("%s",p->name);
        printf("\n请输入作业大小：");
        scanf("%d",&p->size);
        printf("\n请输入作业到达时间：");
        scanf("%d",&p->ntime);
        p->state='w';
        p->link=NULL;
        sort();
    }
    printf("\n按任意键继续......\n");
    getchar();
}

void input2()
{
    JCB *k;
    int has;
    q=getjcb(JCB);
    printf("\n请输入回收区域名：");
    scanf("%s",q->name);
    p=as;
    while(p!=NULL)
    {
        if(strcmp(p->name,q->name)==0)
        {
            q->addr=p->addr;
            q->size=p->size;
            has=1;
            if(p==as) as=p->link;
            else
            {
                k=as;
                while(k->link!=p)
                k=k->link;
                k->link=p->link;
            }
        printf("输入该作业首地址:%d\n",q->addr);
        printf("输入该作业大小:%d\n",q->size);
        q->link=NULL;
        break;
        }
        else
        {
            p=p->link;
            has=0;
        }
    }
    if(has==0)
    {
        print("\n输入作业名有误，请重新输入！\n");
        input2();
    }   
}


