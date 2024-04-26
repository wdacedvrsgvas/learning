typedef struct 
{
    ElemType data[MaxSize];
    int length;
}SqList;                          //顺序表类型  

//typedef int ElemType;

void CreateList(SqList*&L,ElemType a[],int n)
{
    int i;
    L=(SqList*)malloc(sizeof(SqList));   //为指针变量动态的分配一片连续的存储空间
    for(i=0;i<n;i++)
        L->data[i]=a[i];
    L->length=n;
}