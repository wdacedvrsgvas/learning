
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
