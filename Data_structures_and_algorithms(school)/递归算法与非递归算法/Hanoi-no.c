// 整体设计思路：
// 栈的定义与初始化：首先定义了一个栈结构 Stack，包含一个整型数组和一个表示栈顶的整数。然后定义了三个栈 stack1、stack2 和 stack3，用于存储汉诺塔问题的状态信息。通过 initStack 函数初始化这三个栈。
// 入栈和出栈操作：定义了 push 和 pop 函数，用于向栈中压入元素和从栈中弹出元素。
// 汉诺塔的非递归解决方案：hanoiNonRecursive 函数是整个算法的核心。它采用迭代的方式模拟递归过程。首先将初始状态压入栈1中，然后通过迭代循环来模拟递归的过程，直到所有盘子都移动到目标塔。
// 迭代执行移动：在每一步中，根据奇偶数步来决定移动的方向。如果是奇数步，则将盘子从A移动到C；如果是偶数步，则将盘子从A移动到B。移动过程中，更新栈的状态信息。
// 移动方向的选择：根据当前步数的奇偶性，选择移动的方向。根据移动方向，打印移动信息，并将移动的盘子信息压入栈3中。
// 更新栈信息：在每一步移动后，将更新后的栈信息重新压入栈3中，以备下一次迭代循环使用。
// 核心:递归和栈的关系


#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 64

// 定义栈结构
typedef struct {
    int array[MAX_DISKS];
    int top;
} Stack;

// 初始化栈
void initStack(Stack *stack) {
    stack->top = -1;
}

// 入栈
void push(Stack *stack, int value) {
    stack->array[++stack->top] = value;
}

// 出栈
int pop(Stack *stack) {
    return stack->array[stack->top--];
}

// 汉诺塔的非递归解决方案
void hanoiNonRecursive(int num_disks, char from_rod, char to_rod, char aux_rod) {
    Stack stack1, stack2, stack3;
    int total_moves, move;
    char temp;

    initStack(&stack1);
    initStack(&stack2);
    initStack(&stack3);

    // 初始化栈1，压入初始值，代表还没处理的任务
    push(&stack1, num_disks);
    push(&stack1, from_rod);
    push(&stack1, to_rod);
    push(&stack1, aux_rod);

    total_moves = (1 << num_disks) - 1;

    // 迭代执行移动
    for (move = 1; move <= total_moves; move++) {
        if (move % 2 != 0) {
            // move discs between A and C
            if (stack1.top != -1) {
                aux_rod = pop(&stack1);
                to_rod = pop(&stack1);
                from_rod = pop(&stack1);
                num_disks = pop(&stack1);
            }
        } else {
            // move discs between A and B
            if (stack2.top != -1) {
                to_rod = pop(&stack2);
                aux_rod = pop(&stack2);
                from_rod = pop(&stack2);
                num_disks = pop(&stack2);
            }
        }

        // 根据奇偶移动方向选择
        if (move % 3 == 1) {
            printf("Move disk from %c to %c\n", from_rod, to_rod);
            push(&stack3, num_disks);
        } else if (move % 3 == 2) {
            printf("Move disk from %c to %c\n", from_rod, aux_rod);
            push(&stack3, num_disks);
        } else if (move % 3 == 0) {
            printf("Move disk from %c to %c\n", aux_rod, to_rod);
            push(&stack3, num_disks);
        }

        // 更新栈信息
        push(&stack3, from_rod);
        push(&stack3, aux_rod);
        push(&stack3, to_rod);
        push(&stack3, num_disks);
    }
}

int main() {
    int num_disks = 3; // 汉诺塔的盘数
    hanoiNonRecursive(num_disks, 'A', 'C', 'B'); // A是初始塔，C是目标塔，B是辅助塔
    return 0;
}

