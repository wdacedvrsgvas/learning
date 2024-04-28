typedef struct DNode // 双链表结点类型
{
    ElemType data;
    struct DNode *prior; // 指向前驱结点
    struct DNode *next;  // 指向后继结点
} DLinkNode;
// 插入:s->next = p->next   p->next->prior = s   s->prior = p   p->next = s
// 删除:p->next->next->prior = p    p->next = p->next->next

// 建立双链表  头插法和尾插法
// 头插法建立双链表：由含有n个元素的数组a创建带头结点的双链表L。
void CreateListF(DLinkNode *&L，ElemType a[]，int n)
{
    DLinkNode *s;
    int i;
    L = (DLinkNode *)malloc(sizeof(DLinkNode));
    // 创建头结点
    L->prior = L->next = NULL; // 前后指针域置为NULL
    for (i = 0; i < n; i++)    // 循环建立数据结点
    {
        s = (DLinkNode *)malloc(sizeof(DLinkNode));
        s->data = a[i];      // 创建数据结点*s
        s->next = L->next;   // 将*s插入到头结点之后
        if (L->next != NULL) // 若L存在数据结点，修改       前驱指针
            L->next->prior = s;
        L->next = s;
        s->prior = L;
    }
}

// 尾插法建立双链表：由含有n个元素的数组a创建带头结点的双链表L。
void CreateListR(DLinkNode *&L，ElemType a[]，int n)
{
    DLinkNode *s， *r;
    int i;
    L = (DLinkNode *)malloc(sizeof(DLinkNode)); // 创建头结点
    r = L;                                      // r始终指向尾结点，开始时指向头结点
    for (i = 0; i < n; i++)                     // 循环建立数据结点
    {
        s = (DLinkNode *)malloc(sizeof(DLinkNode));
        s->data = a[i]; // 创建数据结点*s
        r->next = s;
        s->prior = r; // 将*s插入*r之后
        r = s;        // r指向尾结点
    }
    r->next = NULL; // 尾结点next域置为NULL
}

// 双链表的插入算法
bool ListInsert(DLinkNode *&L，int i，ElemType e)
{
    int j = 0;
    DLinkNode *p = L， * s;        // p指向头结点，j设置为0
    while (j < i - 1 && p != NULL) // 查找第i-1个结点
    {
        j++;
        p = p->next;
    }
    if (p == NULL) // 未找到第i-1个结点，返回false
        return false;
    else // 找到第i-1个结点*p，在其后插入新结点*s
    {
        s = (DLinkNode *)malloc(sizeof(DLinkNode));
        s->data = e;         // 创建新结点*s
        s->next = p->next;   // 在*p之后插入*s结点
        if (p->next != NULL) // 若存在后继结点，修改其前驱指针
            p->next->prior = s;
        s->prior = p;
        p->next = s;
        return true;
    }
}

// 双链表的删除算法
bool ListDelete(DLinkNode *&L，int i，ElemType &e)
{
    int j = 0;
    DLinkNode *p = L， * q;        // p指向头结点，j设置为0
    while (j < i - 1 && p != NULL) // 查找第i-1个结点
    {
        j++;
        p = p->next;
    }
    if (p == NULL) // 未找到第i-1个结点
        return false;
    else // 找到第i-1个结点*p
    {
        q = p->next;   // q指向第i个结点
        if (q == NULL) // 当不存在第i个结点时返回false
            return false;
        e = q->data;
        p->next = q->next;   // 从双单链表中删除*q结点
        if (p->next != NULL) // 修改其前驱指针
            p->next->prior = p;
        free(q); // 释放*q结点
        return true;
    }
}

void Reverse(DLinkNode *&L) // 双链表结点逆置
{
    DLinkNode *p = L->next， * q; // p指向开始结点
    L->next = NULL;               // 构造只有头结点的双链表L
    while (p != NULL)             // 扫描L的数据结点
    {
        q = p->next;         // 用q保存其后继结点
        p->next = L->next;   // 采用头插法将*p结点插入
        if (L->next != NULL) // 修改其前驱指针
            L->next->prior = p;
        L->next = p;
        p->prior = L;
        p = q;
    }
}

// 设计判断带头结点的循环双链表L（含两个以上的结点）是否对称相等的算法。
int Equal(DLinkNode *L)
{
    int same = 1;
    DLinkNode *p = L->next;  // p指向第一个数据结点
    DLinkNode *q = L->prior; // q指向最后数据结点
    while (same == 1)
    {
        if (p->data != q->data)
            same = 0;
        else
        {
            if (p == q || p == q->prior)
                break;
            q = q->prior; // q前移
            p = p->next;  // p后
        }
    }
    return same;
}

// 线性表的应用
// 两个表自然连接问题  表：m行、n列。假设所有元素为整数
#define MaxCol 10    // 最大列数
typedef struct Node1 // 定义数据结点类型
{
    ElemType data[MaxCol];
    struct Node1 *next; // 指向后继数据结点
} DList;

typedef struct Node2 // 定义头结点类型
{
    int Row，Col; // 行数和列数
    DList *next;  // 指向第一个数据结点
} HList;
// 交互式创建单链表算法
void CreateTable(HList *&h)
{
    int i，j;
    DList *r， *s;
    h = (HList *)malloc(sizeof(HList)); // 创建头结点
    h->next = NULL;
    printf("表的行数，列数:");
    scanf("%d%d"， & h->Row， & h->Col); // 输入表
    for (i = 0; i < h->Row; i++)         // 输入所有行的数据
    {
        printf("  第%d行:"，i + 1);
        s = (DList *)malloc(sizeof(DList)); // 创建数据
        for (j = 0; j < h->Col; j++)        // 输入一行的数据
            scanf("%d"， & s->data[j]);
        if (h->next == NULL) // 插入第一个数据结点
            h->next = s;
        else
            r->next = s;
        r = s;
    }
    r->next = NULL;
} // 尾结点next域置空

// 销毁单链表算法
void DestroyTable(HList *&h)
{
    DList *pre = h->next， *p = pre->next;
    while (p != NULL)
    {
        free(pre);
        pre = p;
        p = p->next;
    }
    free(pre);
    free(h);
}

// 输出单链表算法
void DispTable(HList *h)
{
    int j;
    DList *p = h->next; // p指向开始行结点
    while (p != NULL)   // 扫描所有行
    {
        for (j = 0; j < h->Col; j++) // 输出一行的数据
            printf("%4d"，p->data[j]);
        printf("\n");
        p = p->next; // p指向下一行结点
    }
}

// 两表条件连接实现
void LinkTable(HList *h1，HList *h2，HList *&h)
{
    int i，j，k;
    DList *p = h1->next， * q， * s， * r;

    printf("连接字段是:第1个表序号，第2个表序号:");
    scanf("%d%d"， & i， & j);

    h = (HList *)malloc(sizeof(HList)); // 创建结果表头结点
    h->next = NULL;                     // 置next域为NULL
    h->Row = 0;                         // 置行数为0
    h->Col = h1->Col + h2->Col;         // 置列数为表1和表2的列数和
    while (p != NULL)                   // 扫描表1
    {
        q = h2->next;     // q指向表2的开始结点
        while (q != NULL) // 扫描表2
        {
            if (p->data[i - 1] == q->data[j - 1]) // 对应字段值相等
            {
                s = (DList *)malloc(sizeof(DList)); // 创建结点
                for (k = 0; k < h1->Col; k++)       // 复制表1的当前行
                    s->data[k] = p->data[k];
                for (k = 0; k < h2->Col; k++) // 复制表2的当前行
                    s->data[h1->Col + k] = q->data[k];
                if (h->next == NULL) // 若插入第一个数据
                    h->next = s;     // 将*s插入到头结点之后
                else                 // 若插入其他数据结点
                    r->next = s;     // 将*s插入到*r结点之后
                r = s;               // r始终指向尾结点
                h->Row++;            // 表行数增1
            }
            q = q->next; // 表2下移一个记录
        }
        p = p->next; // 表1下移一个记录
    }
    r->next = NULL; // 表尾结点next域置空
}
