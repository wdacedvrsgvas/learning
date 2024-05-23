#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 640
struct node // 定义分区
{
    int address, size;
    struct node *next;
} typedef struct node RECT;
/*-----函数定义-----*/
RECT *assignment(RECT *heada, RECT *back1); // 分配分区
// 针对首次适应算法回收分区
void firstfit(RECT *head, RECT *heada, RECT *back1);
void bestfit(REcT *head, RECT *back1);  // 针对最佳适应算法回收分区，待扩充
int backcheck(REcT *head, REcT *backl); // 合法性检查
void print(RECT *head);                 // 输出已分配分区表或空闲分区
/*-----变量定义-------*/
RECT *head, *heada, *back, *assignl, *p;
int applicationl, maxblocknum;
char way; // 用于定义分配方式：首次适应、最佳适应、最坏适应。目前未使用 int main()
char choose;
int check;
RECT *allocated;
head - malloc(sizeof(RECT));
p = malloc(sizeof(REcT));
head->size - MAX;
head->address = 0;
head->next = p;
maxblocknum = 1;
p->size = MAXx;
p->address = 0;
P->next = NULL;
print(head);
// 建立空闲分区表的初始状态//输出空闲分区表的初始状态
// printf("Enter the allocation way (best or first (b/f))ln");
// scanf("%c",&way); way='f';
heada = malloc(sizeof(REcT));
heada->size = 0;
heada->address - 0;
heada->next - NULL; // print(heada);
// 建立已分配分区表的初始状态//输出空闲分区表的初始状态

while (1)

    printf("Enter the allocate or reclaim (a/r),or press other key to exit./n");
scanf("%c", &choose);
if (tolower(choose) = -'a") printf("Input application:In");
    // 选择分配或回收//a为分配
    // 输人申请的空间大小
    scanf("%d", &applicationl);
    assignl = assignment（head, application1)
    ； //调用分配函数以分配内存
        if (assignl->address == -1) 1 /
        分配不成功
            printf("Too large application! Allocation fails! Inln");
// 分配成功
else
    printf("Allocation Success! ADDRESs=%5dln", assign1->address);
printf("\n*********Unallocated Table**********\n");
// 输出
print(head);
printf("\n*********Allocated Table***
           * **\n ");
              print(heada);
       elseif(tolower(choose) = -'r')
           back = malloc(sizeof(RECT));
       printf("Input address and size:In");
       // 回收内存
       scanf("%d%d", &back->address, &back->size); // 输人回收地址和大小
       check = backcheck(head, back); if (check == 1) if (tolower(way) = -'f')
           firstfit(head, heada, back);
       // 首次适应算法回收
       printf("n*********Unallocated Table***
              print(head);
              // 输出
★* **★\n "）;
              printf("\n*********AllocatedTable*************\n");
              print(heada);) while (tolower(choose) == 'a' lltolower(choose) = -'r');
       exit(o);
       J // main() end.
           -- -
           内存分配函数-- *
               RECT * assignment(RECT * head, int application) REcT * after,
       *before, *assign;
       assign = malloc(sizeof(RECT)); assign->size = application; assign->next - NULL;
       if (application > head->size ll application < 0) / / 申请分配空间 cs 扫描全能王 assign->address = -1; else before - head;
       after - head->next;
       while (after->size < application)
           before -
       before->next;
       after - after->next;
       if (after->size == application)
       // 申请无效
       // 遍历链表，查找合适的节点
       // 若节点大小等于申请大小，则完全分配
       if (after->size = -head->size) maxblocknum--;
       before->next = after->next;
       assign->address = after->address; free(after);
       else if (after->size = -head->size) maxblocknum--;
       after->size = after->size - application； // 大于申请空间时，截取相应大小并分配 assign->address=after->address+after->size;
                                       if（maxblocknum ==
                     0)
        before
    - head;
head->size = 0;
maxblocknum = 1;
while (before !-NULL)
    if (before->size > head->size)
        head->size = before->size;
maxblocknum = 1;
// 修改最大数和头节点
else if (before->size = --head->size)
    maxblocknum++;
before - before->next;
assignl = assign;
1 / 修改已分配分区表，添加节点 after = heada;
while (after->next !-NULL)
    after = after->nexti after->next = assign;
heada->size++;
61 第 5 章内存管理
    cs
        扫描全能王 62 计算机操作系统实验指导（Linux版）（附微课视频） return assignl;
// 返回分配给用户的地址
- 首次适应算法 -
    *void firstfit(RECT *head, RECT *heada, RECT *backl)
        REcT *before,
    *after, *back2;
int insert, del;
back2 = malloc(sizeof(REcT));
back2->address = backl->address;
back2->size = backl->size;
back2->next - back1->next;
before = head;
after = head->next;
insert = 0;
while (!insert)
    // 将回收区插人空闲分区表
    if ((after == NULL) Il((backl->address <= after->address) && (backl->address >= before->address)))
        before->next = backl;
back1->next = after;
insert = l;
else T
    before = before->next;
after = after->next;
if（backl->address == before->address + before->size） // 与上一内存块合并
                                            before->size = before->size + backl->size;
before->next = back1->next;
free(backl);
backl = before;
if ((after != NULL) && (after->address = -backl->address + backl->size))
    // 与下一内存块合并
    backl->size = backl->size + after->size;
backl->next = after->next;
free(after);
if (head->size < backl->size)
    head->size = backl->size;
maxblocknum = 1l;
// 修改最大块值和最大块个数
cs
    扫描全能王 else if (head->size = -backl->size) maxblocknum++;
// 修改已分配分区表，删除相应节点 before=heada;
after - heada->next;
del = o;
while（！delllafter！ = NULL） // 将回收区从已分配分区表中删除
                        if ((after->address == back2->address) && (after->size = -back2->size))
                            before->next = after->next;
free(after);
del = l;
else before = before->next;
after = after->next;
heada->size--;
打印输出链表
void print(REcT *output)
    REcT *before;
int index;
before = output->next;
index = 0;
if (output->next = -NULL)
    printf("No part for print!n");
else
    printf("index****address****end*****size**** In");
while (before !-NULL)
printf("
-ln");
printf("%-9d%- 9d%- 9d%- 9dln", index, before->address, before->
address+ before->size-l,before->size);
printf("-index++;
before-before->next;
/*检查回收块的合法性，back1为要回收节点的地址*/ int backcheck(RECT *head,RECT *backl)
/n"）;
cs
63 第 5章内存管理
扫描全能王
64 计算机操作系统实验指导（Linux版）（附微课视频）
RECT *before; int check=l;
if(backl->address<0Iback1->size<0）check=0；//地址和大小不能为负数 before-head->next;
while((before!=NULL)&&check)
//地址不能和空闲分区表中的节点重叠
if(backl->address<before->address)&& (back1->address+back1->size>before->address)ll(back1->address>=before->address)&& (backl->address<before->address+before->size)))
check=0; else
before-before->next;
if(check==0)printf("Errorinput!n"); return check;