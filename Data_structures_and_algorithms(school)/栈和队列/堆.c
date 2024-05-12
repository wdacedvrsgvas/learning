// 队列的顺序存储结构
typedef struct
{
    ElemType data[MaxSize];
    int front, rear; // 队首和队尾
} SqQueue;
// 约定rear总是指向队尾元素
//   元素进队，rear增1
//   约定front指向当前队中队头元素的前一位置
//  元素出队，front增1
//  当rear=MaxSize-1时不能再进队
// 队空条件：front = rear
//  队满条件：rear = MaxSize－1
//  元素e进队：rear++; data[rear]=e;
//  元素e出队：front++; e=data[front];
// 注意：rear指向队尾元素；front指向队头元素的前一个位置。
void InitQueue(SqQueue *&q)
{
    q = (SqQueue *)malloc(sizeof(SqQueue));
    q->front = q->rear = -1;
}

void DestroyQueue(SqQueue *&q)
{
    free(q);
}

bool QueueEmpty(SqQueue *q)
{
    return (q->front == q->rear);
}

bool enQueue(SqQueue *&q, ElemType e)
{
    if (q->rear == MaxSize - 1)
        return false;
    q->rear++;
    q->data[q->rear] = e;
    return true;
}
// 出队列
bool deQueue(SqQueue *&q, ElemType &e)
{
    if (q->front == q->rear)
        // 队空下溢出
        return false;
    q->front++;
    e = q->data[q->front];
    return true;
}

// 环形队列（或循环队列）中实现队列的基本运算
//  这是因为采用rear==MaxSize-1作为队满条件的缺陷。
// 当队满条件为真时，队中可能还有若干空位置。
// 这种溢出并不是真正的溢出，称为假溢出。
// 内存地址一定是连续的，不可能是环形的,逻辑方式实现环形队列
// rear = (rear + 1) % MaxSize
// front = (front + 1) % MaxSize
// 队空条件：front = rear
// 队满条件：(rear+1)%MaxSize = front
// 进队e操作：rear=(rear+1)%MaxSize;  将e放在rear处
// 出队操作：front=(front+1)%MaxSize; 取出front处元素e;

// 对于环形队列来说，如果知道队头指针和队列中元素个数，则可以计算出队尾指针。也就是说，可以用队列中元素个数代替队尾指针。
typedef struct
{
    ElemType data[MaxSize];
    int front; // 队头指针
    int count; // 队列中元素个数
} QuType;
// 队空条件：count＝0
//  队满条件：count＝MaxSize
//  进队e操作：rear=(rear+1)%MaxSize; 将e放在rear处
//  出队操作：front=(front+1)%MaxSize;取出front处元素e;
void InitQueue(QuType *&qu) // 初始化队运算算法
{
    qu = (QuType *)malloc(sizeof(QuType));
    qu->front = 0;
    qu->count = 0;
}

bool EnQueue(QuType *&qu, ElemType x) // 进队运算算法
{
    int rear;                 // 临时队尾指针
    if (qu->count == MaxSize) // 队满上溢出
        return false;
    else
    {
        rear = (qu->front + qu->count) % MaxSize; // 求队尾位置
        rear = (rear + 1) % MaxSize;              // 队尾循环增1
        qu->data[rear] = x;
        qu->count++; // 元素个数增1
        return true;
    }
}

bool DeQueue(QuType *&qu, ElemType &x) // 出队运算算法
{
    if (qu->count == 0) // 队空下溢出
        return false;
    else
    {
        qu->front = (qu->front + 1) % MaxSize; // 队头循环增1
        x = qu->data[qu->front];
        qu->count--; // 元素个数减1
        return true;
    }
}

bool QueueEmpty(QuType *qu) // 判队空运算算法
{
    return (qu->count == 0);
}

// 队列的链式存储结构
//  链队组成:
//          （1）存储队列元素的单链表结点
//          （2） 指向队头和队尾指针的链队头结点
// 单链表中数据结点类型DataNode定义
typedef struct qnode
{
    ElemType data; // 数据元素
    struct qnode *next;
} DataNode;
// 链队中头结点类型LinkQuNode定义如下：
typedef struct
{
    DataNode *front; // 指向单链表队头结点
    DataNode *rear;  // 指向单链表队尾结点
} LinkQuNode;
// 4要素
//  队空条件：front=rear=NULL
//   队满条件：不考虑
//   进队e操作：将包含e的结点插入到单链表表尾
//   出队操作：删除单链表首数据结点
void InitQueue(LinkQuNode *&q)
{
    q = (LinkQuNode *)malloc(sizeof(LinkQuNode));
    q->front = q->rear = NULL;
}
void DestroyQueue(LinkQuNode *&q)
{
    DataNode *p = q->front， * r; // p指向队头
    if (p != NULL)                // 释放数据结点占用空间
    {
        r = p->next;
        while (r != NULL)
        {
            free(p);
            p = r;
            r = p->next;
        }
    }
    free(p);
    free(q); // 释放链队结点占用空间
}
