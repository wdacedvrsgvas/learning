// 串（或字符串）是由零个或多个字符组成的有限序列
// 子串：一个串中任意个连续字符组成的子序列（含空串）称为该串的子串  包含空和一个
// 真子串是指不包含自身的所有子串

// 串的顺序存储
// 非紧缩格式和紧缩格式

// 非紧缩格式
#define MaxSize 100
typedef struct
{
    char data[MaxSize];
    int length;
} SqString;
// 建立顺序串
void StrAssign(SqString &s, char cstr[])
{
    int i;
    for (i = 0; cstr[i] != '\0'; i++)
        s.data[i] = cstr[i];
    s.length = i;
}
// 将串t复制给串s
void StrCopy(SqString &s, SqString t)
{
    int i;
    for (i = 0; i < t.length; i++)
        s.data[i] = t.data[i];
    s.length = t.length;
}
// 判串相等
bool StrEqual(SqString s, SqString t)
{
    bool same = true;
    int i;
    if (s.length != t.length) // 长度不相等时返回0
        same = false;
    else
        for (i = 0; i < s.length; i++)
            if (s.data[i] != t.data[i])
            {
                same = false;
                break;
            }
    return same;
}
// 求串长
int StrLength(SqString s)
{
    return s.length;
}
// 串连接
SqString Concat(SqString s, SqString t)
{
    SqString str;
    int i;
    str.length = s.length + t.length;
    for (i = 0; i < s.length; i++) // s.data[0..s.length-1]str
        str.data[i] = s.data[i];
    for (i = 0; i < t.length; i++) // t.data[0..t.length-1]str
        str.data[s.length + i] = t.data[i];
    return str;
}
// 求子串
SqString SubStr(SqString s, int i, int j)
{
    SqString str;
    int k;
    str.length = 0;
    if (i <= 0 || i > s.length || j < 0 || i + j - 1 > s.length)
        return str;                     // 参数不正确时返回空串
    for (k = i - 1; k < i + j - 1; k++) // s.data[i..i+j]str
        str.data[k - i + 1] = s.data[k];
    str.length = j;
    return str;
}
// 将串s2插入到串s1的第i（1≤i≤StrLength(s)+1）个字符中
SqString InsStr(SqString s1, int i, SqString s2)
{
    int j;
    SqString str;
    str.length = 0;
    if (i <= 0 || i > s1.length + 1) // 参数不正确时返回空串
        return str;
    for (j = 0; j < i - 1; j++) // 将s1.data[0..i-2]str
        str.data[j] = s1.data[j];
    for (j = 0; j < s2.length; j++) // s2.data[0..s2.length-1]str
        str.data[i + j - 1] = s2.data[j];
    for (j = i - 1; j < s1.length; j++) // s1.data[i-1..s1.length-1]str
        str.data[s2.length + j] = s1.data[j];
    str.length = s1.length + s2.length;
    return str;
}
// 从串s中删去第i（1≤i≤StrLength(s)）个字符开始的长度为j的子串，并返回产生的新串。
SqString DelStr(SqString s, int i, int j)
{
    int k;
    SqString str;
    str.length = 0;
    if (i <= 0 || i > s.length || i + j > s.length + 1)
        return str;             // 参数不正确时返回空串
    for (k = 0; k < i - 1; k++) // s.data[0..i-2]str
        str.data[k] = s.data[k];
    for (k = i + j - 1; k < s.length; k++)
        str.data[k - j] = s.data[k];
    str.length = s.length - j;
    return str;
}
// 在串s中，将第i（1≤i≤StrLength(s)）个字符开始的j个字符构成的子串用串t替换，并返回产生的新串
SqString RepStr(SqString s, int i, int j, SqString t)
{
    int k;
    SqString str;
    str.length = 0;
    if (i <= 0 || i > s.length || i + j - 1 > s.length)
        return str;             // 参数不正确时返回空串
    for (k = 0; k < i - 1; k++) // s.data[0..i-2]str
        str.data[k] = s.data[k];
    for (k = 0; k < t.length; k++) // t.data[0..t.length-1]str
        str.data[i + k - 1] = t.data[k];
    for (k = i + j - 1; k < s.length; k++)
        str.data[t.length + k - j] = s.data[k];
    str.length = s.length - j + t.length;
    return str;
}
// 输出串s的所有元素值
void DispStr(SqString s)
{
    int i;
    if (s.length > 0)
    {
        for (i = 0; i < s.length; i++)
            printf("%c", s.data[i]);
        printf("\n");
    }
}

// 串的链式存储
typedef struct snode
{
    char data;
    struct snode *next;
} LinkStrNode;
// 将一个字符串常量cstr赋给串s，即生成一个其值等于cstr的串s
void StrAssign(LiString *&s, char cstr[])
{
    int i;
    LiString *r, *p;
    s = (LiString *)malloc(sizeof(LiString));
    r = s; // r始终指向尾节点
    for (i = 0; cstr[i] != '\0'; i++)
    {
        p = (LiString *)malloc(sizeof(LiString));
        p->data = cstr[i];
        r->next = p;
        r = p;
    }
    r->next = NULL;
}
// 将串t复制给串s
void StrCopy(LiString *&s, LiString *t)
{
    LiString *p = t->next, *q, *r;
    s = (LiString *)malloc(sizeof(LiString));
    r = s;            // r始终指向尾节点
    while (p != NULL) // 将t的所有节点复制到s
    {
        q = (LiString *)malloc(sizeof(LiString));
        q->data = p->data;
        r->next = q;
        r = q;
        p = p->next;
    }
    r->next = NULL;
}
// 判串相等
bool StrEqual(LiString *s, LiString *t)
{
    LiString *p = s->next, *q = t->next;
    while (p != NULL && q != NULL && p->data == q->data)
    {
        p = p->next;
        q = q->next;
    }
    if (p == NULL && q == NULL)
        return true;
    else
        return false;
}
// 求串长
int StrLength(LiString *s)
{
    int i = 0;
    LiString *p = s->next;
    while (p != NULL)
    {
        i++;
        p = p->next;
    }
    return i;
}
