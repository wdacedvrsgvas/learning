
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LinkNode;

// 增加node:1.s->next=p->next 2.p->next=s
// 删除node:p->next=p->next->next

void CreateLisF(LinkNode *&L, ElemType a[], int n)
{
    LinkNode *s;
    int i;
    L = (LinkNode *)malloc(sizeof(LinkNode));
    L->next = NULL;
    for (i = 0; i < n; i++)
    {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        s->data = a[i];
        s->next = L->next;
        L->next = s;
    }
}
// 尾插法:
void CreateListR(LinkNode *&L, ElemType a[], int n)
{
    LinkNode *s, *r;
    int i;
    L = (LinkNode *)malloc(sizeof(LinkNode));
    r = L;
    for (i = 0; i < n; i++)
    {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        s->data = a[i];
        r->next = s;
        r = s;
    }
    r->next = NULL;
}

// 初始化线性表InitList(L)
void InitList(LinkNode *&L)
{
    L = (LinkNode *)malloc(sizeof(LinkNode));
    L->next = NULL;
}

// 销毁线性表DestroyList(L)
void DestroyList(LinNode *&L)
{
    LinkNode *pre = L, *p = L->next;
    while (p != NULL)
    {
        free(pre);
        pre = p;
        p = pre->next;
    }
    free(pre);
}

// 判线性表是否为空表ListEmpty(L)
bool ListEmpty(LinkNode *L)
{
    return (L->next == NULL);
}

// 求线性表的长度ListLength(L)
int ListLength(LinkNode *L)
{
    int n = 0;
    LinkNode *p = L;
    while (p->next != NULL)
    {
        n++;
        p = p->next;
    }
    return (n);
}

// 输出线性表DispList(L)
void DispList(LinkNode *L)
{
    LinkNode *p = L->next;
    while (p != NULL)
    {
        printf("%d", p->data);
        p = p->next;
    }
    printf("\n");
}

// 求线性表L中位置i的数据元素GetElem(L，i，&e)
bool GetElem(LinkNode *L, int i, ElemType &e)
{
    int j = 0;
    LinkNode *p = L;
    while (j < i && p != NULL)
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
        return false;
    else
    {
        e = p->data;
        return true;
    }
}

// 按元素值查找LocateElem(L，e)
int LocateElem(LinkNode *L, ElemType e)
{
    int i = 1;
    LinkNode *p = L->next; // p指向开始结点，i置为1
    while (p != NULL && p->data != e)
    {
        p = p->next;
        i++;
    }
    if (p == NULL)
        return (0);
    else
        return (i);
}

// 插入数据元素ListInsert(&L，i，e)
bool ListInsert(LinkNode *&L, int I, ElemType e)
{
    int j = 0;
    LinkNode *P = L, *s;
    while (j < i - 1 && p != NULL)
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
        return false;
    else
    {
        s = (LinkNode *)malloc(sizeof(LinkNode));
        s->data = e;
        s->next = p->next;
        p->next = s;
        return true;
    }
}

// 删除数据元素ListDelete(&L，i，&e)
bool ListDelete(LinkNode *&L, i, &e)
{
    int j = 0;
    LinkNode *p = L, *q;
    while (j < i - 1 && p != NULL) // 找到第i-1个结点*p
    {
        j++;
        p = p->next;
    }
    if (p == NULL)
        return false;
    else
    {
        q = p->next;   // q指向第i个结点
        if (q == NULL) ////若不存在第i个结点，返回false
            return false;
        e = q->data;
        p->next = q->next;
        free(q);
        return true;
    }
}

// 设计一个算法，删除一个单链表L中元素值最大的结点（假设最大值结点是唯一的）。
void delmaxnode(LinkNode *&L)
{
    LinkNode *p = L->next, *pre = L, *maxp = p, *maxpre = pre;
    while (p != NULL)
    {
        if (maxp->data < p->data)
        {
            maxp = p;
            maxpre = pre;
        }
        pre = p;
        p = p->next;
    }
    maxpre->next = maxp->next;
    free(maxp);
}