#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1#define FALSE 0
#define INVALID -l
#define total_instruction 320
#define total_vp 32 

typedef struct
{
    int pn; 
    int pfn;
    int counter;
    int time;
}p1_type;
p1_type pi[total_vp];

typedef struct pfc_struct
{
    int pn; 
    int pfn;
    struct pfc_struct *next;
}pfc_type;
pfc_type pfc[total_vp]; 
pfc_type *freepf_head; 
pfc_type *busypf_head; 
pfc_type *busypf_tail; 
int disaffect;
int a[total_instruction];
int page[total_instruction];
int offset[total_instruction];
void initialize();
void FIFO();
void LUR();
void OPT();
int main()
{
    int s,i,j;
    srand(10*getpid());
    s=(float)319*rand()/32767/32767/2+1;
    for(i=0;i<total_instruction;i+=4)
    {
        if(s<0||s>319)
        {
            printf("When i==%d,Error,s==%d\n",i,s);
            exit(0);
        }
        a[i]=s;
        a[i+1]=a[i]+1;
        a[i+2]=(float)a[i]*rand()/32767/32767/2; 
        a[i+3]=a[i+2]+1;
        s=(f1oat)(318-a[i+2])*rand())/32767/32767/2+a[i+2]+2;
        if((a[i+2]>318)/(s>319))
            printf("a[%d+2],a number which is: %d and s==%dln",i,a[i+2],s);
    }
    for(i=0;i<total_instruction;i++)
    {
        page[i]=a[i]/i0; 
        offset[i]=a[i]%10;
    }
    //用户工作区从4个页面变换到32个页面 
    for(i=4;i<=32;i++)
    {
        printf("%2d page frames",i); 
        FIFO(i);
        printf("\n");
    }

    void initialize(int total_pf) 
    {
        int i;
        diseffect=0;
        for(i=0;i<total vp;i++) 
        {
            pl[i].pn=i;
        }
        
    }
    diseffect=0;
    for(i=0;i<total vp;i++) pl[i].pn=i;
    pl[i]·pfn=INVALID; pl[i].counter=0; pl[i].time=-l;
    for(i=0;i<total pf-l;i++) pfc[i].next=&pfc[i+1]; pfc[i].pfn=i;
    pfc[total pf-1].next-NULL;
    pfc[total_pf-1].pfn=total pf-l; freepf head=&pfc[o];
}

