// 基于比较的排序算法:插入排序,交换排序,选择排序,归并排序
// 不基于比较的排序算法:基数排序

// 在排序过程中，若整个表都是放在内存中处理，排序时不涉及数据的内、外存交换，则称之为内排序；

// 理想:
// 决策树是一棵有n!个叶结点的二叉树
//  叶结点个数=n!
//  总结点个数=n0+n2=2n!-1(n2 = n0-1)
//  h=log2(总结点个数+1)=log2(2n!) ≈ nlog2n
//  平均关键字比较次数=h-1
//  移动次数也是同样的数量级，即这样的算法平均时间复杂度为O(nlog2n)。

// n个记录采用基于比较的排序方法：
// 最好的平均时间复杂度为O(nlog2n) 。　
// 最好情况是排序序列正序，此时的时间复杂度为O(n)。

// 内排序算法的稳定性
// 如果待排序的表中，存在有多个关键字相同的记录，经过排序后这些具有相同关键字的记录之间的相对次序保持不变，则称这种排序方法是稳定的。

// 若待排序的表中元素已按关键字排好序，称此表中元素为正序；
// 反之，若待排序的表中元素的关键字顺序正好和排好序的顺序相反，称此表中元素为反序。

// 数据元素类型定义:
typedef int KeyType; // 定义关键字类型
typedef struct       // 记录类型
{
    KeyType key;   // 关键字项
    InfoType data; // 其他数据项,类型为InfoType
} RecType;         // 排序的记录类型定义

// 1.插入排序
//  主要的插入排序方法：
//  （1）直接插入排序
//  （2）折半插入排序
//  （3）希尔排序
// 基本思路:有序区<-一个一个地插入-无序区
// 不一定是全局有序（整体有序）  全局有序区的元素在后面排序中不再发生位置的改变

// 1.1直接插入排序
// 初始时，有序区只有一个元素R[0]
// i＝1~n-1，共经过n-1趟排序
void InsertSort(RecType R[]，int n)
{
    int i, j;
    RecType tmp;
    for (i = 1; i < n; i++)
    {
        if (R[i].key<R[i-1].key])	//反序时
        {
            tmp = R[i];
            j = i - 1;
            do // 找R[i]的插入位置
            {
                R[j + 1] = R[j]; // 将关键字大于R[i].key的记录后移
                j--;
            } while (j >= 0 && R[j].key > tmp.key)
                R[j + 1] = tmp; // 在j+1处插入R[i]
        }
    }
}
// 算法分析    最好：O(n)  最坏：O(n2)  最坏：O(n2)

// 1.2折半插入排序
void BinInsertSort(RecType R[], int n)
{
    int i, j, low, high, mid;
    RecType tmp;
    for (i = 1; i < n; i++)
    {
        if (R[i].key<R[i-1].key])		//反序时
        {
            tmp = R[i]; // 将R[i]保存到tmp中
            low = 0;
            high = i - 1;
            while (low <= high) // 在R[low..high]中查找插入的位置
            {
                mid = (low + high) / 2; // 取中间位置
                if (tmp.key < R[mid].key)
                    high = mid - 1; // 插入点在左半区
                else
                    low = mid + 1; // 插入点在右半区
            } // 找位置high
            for (j = i - 1; j >= high + 1; j--) // 记录后移
                R[j + 1] = R[j];
            R[high + 1] = tmp; // 插入tmp
        }
    }
}
// 算法分析
// 折半插入排序：在R[0..i-1]中查找插入R[i]的位置，折半查找的平均关键字比较次数为log2(i+1)-1，平均移动元素的次数为i/2+2，所以平均时间复杂度为：
// 平均时间复杂度  O(n2)

// 1.3希尔排序
// 基本思路
//   d=n/2
//  将排序序列分为d个组，在各组内进行直接插入排序
//  递减d=d/2，重复② ，直到d=1
// 算法最后一趟对所有数据进行了直接插入排序，所以结果一定是正确的。
void ShellSort(RecType R[], int n)
{
    int i, j, d;
    RecType tmp;
    d = n / 2; // 增量置初值
    while (d > 0)
    {
        for (i = d; i < n; i++)
        { // 对相隔d位置的元素组直接插入排序
            tmp = R[i];
            j = i - d;
            while (j >= 0 && tmp.key < R[j].key)
            {
                R[j + d] = R[j];
                j = j - d;
            }
            R[j + d] = tmp;
        }
        d = d / 2; // 减小增量
    }
}
// 直接插入排序 :
// for (i = 1; i < n; i++)
// {
//     tmp = R[i];
//     j = i - 1;
//     while (j >= 0 && tmp.key < R[j].key)
//     {
//         R[j + 1] = R[j];
//         j = j - 1;
//     }
//     R[j + 1] = tmp;
// }
// 时间复杂度约为O(n^1.3)
// 为什么希尔排序比直接插入排序好？

// 2.交换排序
//  常见的交换排序方法：
//  （1）冒泡排序（或起泡排序）
//  （2）快速排序z

// 3.选择排序
//  （1）简单选择排序（或称直接选择排序）
//  （2）堆排序

// 4.归并排序

// Merge()：一次二路归并，将两个相邻的有序子序列归并为一个有序序列。
void Merge(RecType R[], int low, int mid, int high)
{
    RecType *R1;
    int i = low, j = mid + 1, k = 0;
    // k是R1的下标，i、j分别为第1、2段的下标
    R1 = (RecType *)malloc((high - low + 1) * sizeof(RecType));
    while (i <= mid && j <= high)
        if (R[i].key <= R[j].key) // 将第1段的记录放R1中
        {
            R1[k] = R[i];
            i++;
            k++;
        }
        else
            　　　　 //将第2段中的记录放入R1中
            {
                R1[k] = R[j];
                j++;
                k++;
            }
    while (i <= mid) // 将第1段余下部分复制到R1
    {
        R1[k] = R[i];
        i++;
        k++;
    }
    while (j <= high) // 将第2段余下部分复制到R1
    {
        R1[k] = R[j];
        j++;
        k++;
    }
    for (k = 0，i = low; i <= high; k++，i++)
        R[i] = R1[k];
    free(R1);
}

// MergePass()：一趟二路归并（段长度为length ）。
void MergePass(RecType R[], int length, int n)
{
    int i;
    for (i = 0; i + 2 * length - 1 < n; i = i + 2 * length)
        Merge(R, i, i + length - 1，i + 2 * length - 1);
    if (i + length - 1 < n)                 // 余下两个子表，后者长度小length
        Merge(R，i，i + length - 1，n - 1); // 归并这两子表
}

// MergeSort()：二路归并排序算法：
void MergeSort(RecType R[]，int n)
{
    int length;
    for (length = 1; length < n; length = 2 * length)
        MergePass(R，length，n);
}
//[log2n]趟

// 归并算法分析
//   每一趟归并的时间复杂度为 O(n)
//   总共需进行[log2n]趟趟。
//  二路归并排序的时间复杂度为Ο(nlog2n)。
