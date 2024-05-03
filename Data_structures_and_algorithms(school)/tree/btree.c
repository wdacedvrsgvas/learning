#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef struct node
{
    ElemType data;
    struct node *lchild;
    struct node *rchild;
} BTNode;
// A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))
void CreateBTree(BTNode *&b, char *str)
{
    BTNode *St[MaxSize], *p;
    int top = -1, k, j = 0;
    char ch;
    // 变量 k 是用来表示当前处理的节点是左子树还是右子树的状态
    // 在解析字符串表示的二叉树时，需要一种机制来区分当前处理的节点是左子树的节点还是右子树的节点。因为在这种表示法中，通过括号和逗号来表示树的结构，但是没有直接的标记来区分左右子树。
    b = NULL;
    ch = str[j];
    while (ch != '\0')
    {
        switch (ch)
        {
        case '(':
            top++;
            St[top] = p;
            k = 1;
            break; // 开始处理左子树
        // 将栈顶指针 top 增加，并且将当前节点 p 入栈 St，并且将状态 k 设置为1，表示下一个节点将是左子树的节点
        case ')':
            top--;
            break; // 子树处理完毕
        // 将栈顶指针 top 减少，表示左子树的处理已经结束，我们将转到处理其右子树。
        case ',':
            k = 2;
            break; // 开哈处理右子树
        // 当遇到','时，表示当前节点的左子树已经处理完毕，接下来将处理右子树。我们将状态 k 设置为2，表示下一个节点将是右子树的节点。
        default:
            p = (BTNode *)malloc(sizeof(BTNode));
            p->data = ch;
            p->lchild = p->rchild = NULL;
            if (b == NULL) // 若b为空,p置为二叉树的根结点
                b = p;
            // 如果当前树为空，即根节点尚未设置，则将当前节点 p 设为根节点。
            else
            {
                switch (k)
                // 如果当前树不为空，则根据之前设置的状态 k，将当前节点连接到栈顶节点的左子树或右子树
                {
                case 1:
                    St[top]->lchild = p;
                    break;
                case 2:
                    St[top]->rchild = p;
                    break;
                }
            }
        }
        j++;
        ch = str[j];
    }
}

void DestroyBTree(BTNode *&b)
{
    if (b != NULL)
    {
        DestroyBTree(b->lchild);
        DestroyBTree(b->rchild);
        free(b);
    }
}

BTNode *FindNode(BTNode *b, ElemType x)
{
    BTNode *p;
    if (b == NULL)
        return NULL;
    else if (b->data == x)
        return b;
    else
    {
        p = FindNode(b->lchild, x);
        if (p != NULL)
            return p;
        else
            return FindNode(b->rchild, x);
    }
}

BTNode *LchildNode(BTNode *p) // 返回p结点的左孩子结点指针
{
    return p->lchild;
}

BTNode *RchildNode(BTNode *p)
{
    return p->rchild;
}

int BTHeight(BTNode *b)
{
    int lchildh, rchildh;
    if (b == NULL)
        return (0);
    else
    {
        lchildh = BTHeight(b->lchild);
        rchildh = BTHeight(b->rchild);
        return (lchildh > rchild) ? (lchildh + 1) : (rchildh + 1);
    }
}

void DisBTree(BTNode *b)
{
    if (b != NULL)
    {
        printf("%c", b->data);
        if (b->lchild != NULL || b->rchild != NULL)
        {
            printf("(");
            DispBTree(b->lchild);
            if (b->rchild != NULL)
                printf(",");
            DisBTree(b->rchild);
            printf(")");
        }
    }
}













