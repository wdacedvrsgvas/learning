//顺序查找的算法如下（在顺序表R[0..n-1]中查找关键字为k的元素，成功时返回找到的元素的逻辑序号，失败时返回0）：    

int SeqSearch(RecType R[],int n,KeyType k)
{     
    int i=0;
    while (i<n && R[i].key!=k)//从表头往后找
	    i++;
    if (i>=n)			//未找到返回0
	    return 0;
    else 
	    return i+1;		//找到返回逻辑序号i+1
}
//ASL(SQ)=(N+1)/2

//折半查找
//折半查找也称为二分查找，要求线性表中的记录必须己按关键字值有序（递增或递减）排列。

//其算法如下（在有序表R[0..n-1]中进行折半查找，成功时返回元素的逻辑序号，失败时返回0）：
int BinSearch(RecType R[],int n,KeyType k)
{  
    int low=0,high=n-1,mid;
    while (low<=high)//当前区间存在元素时循环
    {
        mid=(low+high)/2;
        if (R[mid].key==k)//查找成功返回其逻辑序号mid+1
	        return mid+1;
	    if (k<R[mid].key)	//继续在R[low..mid-1]中查找
	        high=mid-1;
	    else
	      low=mid+1;//继续在R[mid+1..high]中查找
    }return 0;
}

//二分查找过程可用二叉树来描述：　　
//把当前查找区间的中间位置上的记录作为根；左子表和右子表中的记录分别作为根的左子树和右子树。
//外部节点即查找失败对应的节点，是虚拟的n个关键字



//索引存储结构和分块查找
//分块查找介于顺序查找和二分查找之间。


//树表的查找
//二叉排序树
//平衡二叉树
//B-树
//B+树

typedef struct node 
{       
    KeyType key;            //关键字项
    InfoType data;        //其他数据域
    struct node *lchild，*rchild; 	  //左右孩子指针
}BSTNode;

//递归查找算法SearchBST()   已经排序好了
BSTNode *SearchBST(BSTNode *bt，KeyType k)
{  
    if (bt==NULL || bt->key==k) 	  //递归出口
        return bt;
    if (k<bt->key)
        return SearchBST(bt->lchild，k);   //在左子树中递归查找
    else
        return SearchBST(bt->rchild，k);   //在右子树中递归查找
}

//递归算法InsertBST()
int InsertBST(BSTNode *&p，KeyType k)	
{ 
    if (p==NULL)//原树为空， 新插入的记录为根结点
    {     
        p=(BSTNode *)malloc(sizeof(BSTNode));
        p->key=k;p->lchild=p->rchild=NULL;
        return 1;
    }
    else if(k==p->key)//存在相同关键字的结点，返回0
        return 0;
    else if (k<p->key) 
        return InsertBST(p->lchild，k);//插入到左子树中
    else  
        return InsertBST(p->rchild，k);//插入到右子树中
}

BSTNode *CreatBST(KeyType A[]，int n)  
{      
    BSTNode *bt=NULL;    //初始时bt为空树
    int i=0;
    while (i<n) 
    {   
        InsertBST(bt，A[i]);//将A[i]插入二叉排序树T中
        i++;
    }
    return bt;      //返回建立的二叉排序树的根指针
} 
//注意：任何结点插入到二叉排序树时，都是以叶结点插入的。

//删除仅仅有右子树的结点*p

int deletek(BSTNode *&bt，KeyType k)
{     
    if (bt!=NULL)
    {     
        if (k==bt->key)
        {    
            deletep(bt)
            return 1;
              }
              else if (k<bt->key)
                   deletek(bt->lchild，k);s
              else
                   deletek(bt->rchild，k);
        }else
            return 0;}


void deletep(BSTNode *&p)
{     
    BSTNode *q;
    q=p; 
    p=p->rchild;
    free(q);  
}


//平衡二叉树（AVL）
//平衡因子：该结点左子树的高度减去右子树的高度
