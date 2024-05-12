
// 栈的顺序存储结构
typedef struct
{
    ElemType data[MaxSize];
    int top; // 栈顶指针
} SqStack;

//   约定top总是指向栈顶元素，初始值为-1
//   当top=MaxSize-1时不能再进栈－栈满
//   进栈时top增1，出栈时top减1

void InitStack(SqStack *&s)
{
    s = (SqStack *)malloc(sizeof(SqStack));
    s->top = -1;
}

void DestroyStack(SqStack *&s)
{
    　　free(s);
}

bool StackEmpty(SqStack *s)
{
    　　return (s->top == -1);
}

bool Push(SqStack *&s，ElemType e)
{
    if (s->top == MaxSize - 1) // 栈满的情况
        return false;
    s->top++;            // 栈顶指针增1
    s->data[s->top] = e; // 元素e放在栈顶指针处
    return true;
}

bool Pop(SqStack *&s，ElemType &e)
{
    if (s->top == -1) // 栈为空的情况，即栈下
        return false;
    e = s->data[s->top]; // 取栈顶指针元素的
    s->top--;            // 栈顶指针减1
    return true;
}

bool GetTop(SqStack *s，ElemType &e)
{
    if (s->top == -1) // 栈为空的情况，即栈
        return false;
    e = s->data[s->top]; // 取栈顶指针元素
    return true;
}

// 共享栈类型：
typedef struct
{
    ElemType data[MaxSize]; // 存放共享
    int top1，top2;         // 两个栈的
} DStack;

// 栈的链式存储结构
typedef struct linknode
{
    ElemType data;         // 数据域
    struct linknode *next; // 指针域
} LinkStNode;

void initStack(LinkStNode *&s)
{
    s = (LiStaInitStackck *)malloc(sizeof(LinkStNode));
    s->next = NULL;
}

void DestroyStack(LinkStNode *&s)
{
    LinkStNode *p = s, *q = s->next;
    while (q != NULL)
    {
        free(p);
        p = q;
        q = p->next;
    }
    free(p); // 此时p指向尾结点，释放
}

bool StackEmpty(LinkStNode *s)
{
    return (s->next == NULL);
}

void Push(LinkStNode *&s，ElemType e)
{
    LinkStNode *p;
    p = (LinkStNode *)malloc(sizeof(LinkStNode));
    p->data = e;
    p->next = s->next;
    s->next = p;
}

bool Pop(LinkStNode *&s，ElemType &e)
{
    LinkStNode *p;
    if (s->next == NULL) // 栈空的情况
        return false;
    p = s->next; // p指向开始结点
    e = p->data;
    s->next = p->next; // 删除*p结点
    free(p);           // 释放*p结点
    return true;
}

bool GetTop(LinkStNode *s，ElemType &e)
{
    if (s->next == NULL) // 栈空的情况
        return false;
    e = s->next->data;
    return true;
}
