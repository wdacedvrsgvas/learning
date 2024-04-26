#include "os_cfg.h"
.text
.global _start
.extern kernel_init
.extern init_main
# start函数相当于
# void start (boot_info_t * boot_info)
_start:
# 根据函数调用的反汇编文件写出调用函数的汇编语法
; push %ebp # 通过栈的形式
; mov %esp,%ebp
; mov 0x8(%ebp),%eax # 跳过返回地址取到参数boot_info

; # mov 4(%esp),%eax 这种方法也可以将参数给到eax，因为该处需要返回，即用不到ebp指针的指向

; # kernel_init(boot_info)
; push %eax

# 第三种方法
push 4(%esp)
call kernel_init
jmp $KERNEL_SELECTOR_CS, $gdt_reload

gdt_reload:
mov $KERNEL_SELECTOR_DS, %ax
mov %ax, %ds
mov %ax, %ss
mov %ax, %es
mov %ax, %fs
mov %ax, %gs
mov $(stack + KERNEL_STACK_SIZE), %esp
jmp init_main

.bss
.comm stack, KERNEL_STACK_SIZE


# 类似于 #define x名字的函数    参数。。。
.macro exception_handler name num with_err_code

.text
.extern do_handler_\name
.global exception_handler_\name
exception_handler_\name:

# 判断是否有错误码
.if \with_err_code == 0
    push $0
.endif

push $\num
# 中断产生后对中断进行处理之前首先保护现场
pusha  # 利用该指令对段寄存器进行保存
push %ds
push %es
push %fs
push %gs

push %esp
call do_handler_\name
# 将参数出栈
add $(1 * 4), %esp 
# 通过将esp指针加四的操作也可以实现出栈功能

# 恢复现场
pop %gs
pop %fs
pop %es
pop %ds
popa

add $(2 * 4), %esp 
iret

.endm

exception_handler unknown, -1, 0
exception_handler divider, 0, 0
exception_handler Debug, 1, 0
exception_handler NMI, 2, 0
exception_handler breakpoint, 3, 0
exception_handler overflow, 4, 0
exception_handler bound_range, 5, 0
exception_handler invalid_opcode, 6, 0
exception_handler device_unavailable, 7, 0
exception_handler double_fault, 8, 1
exception_handler invalid_tss, 10, 1
exception_handler segment_not_present, 11, 1
exception_handler stack_segment_fault, 12, 1
exception_handler general_protection, 13, 1
exception_handler page_fault, 14, 1
exception_handler fpu_error, 16, 0
exception_handler alignment_check, 17, 1
exception_handler machine_check, 18, 0
exception_handler smd_exception, 19, 0
exception_handler virtual_exception, 20, 0

// 硬件中断
exception_handler timer, 0x20, 0