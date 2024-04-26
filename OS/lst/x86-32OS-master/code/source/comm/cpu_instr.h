#ifndef CPU_INSTR_H
#define CPU_INSTR_H

#include "types.h"

//使用内联函数形式写关中断函数
static inline void cli(void){
    __asm__ __volatile__("cli");
}

//开中断函数
static inline void sti(void){
    __asm__ __volatile__("sti");
}

//读端口函数
static inline uint8_t inb(uint16_t port){
    //返回参数
    uint8_t rv;
    //内联汇编形式读取端口
    __asm__ __volatile__(
        "inb %[p], %[v]"
        :[v]"=a"(rv) : [p]"d"(port)
        );
    return rv;
    /*注意的是：
    inb al, dx是intel的汇编语法，而下面的
    inb %[p], %[v]是GCC的汇编语法
    两者表示同一指令，但是写法不一样。源，目的操作数位置正好相反
    */
}

//写端口函数
static inline void outb(uint16_t port, uint8_t data){
    /*指令格式为
    outb al(数据), dx(端口)
    */
    __asm__ __volatile__(
        "outb %[v], %[p]"
        ::[v]"a"(data), [p]"d"(port)
    );
    /*注意的是：
    outb al, dx是intel的汇编语法，而下面的
    outb %[v], %[p]是GCC的汇编语法
    两者表示同一指令，但是写法不一样。源，目的操作数位置正好相反
    */
}

//加载GDT表函数,后续的课程会进一步讲解
static inline void lgdt(uint32_t start, uint32_t size){
    //gdt表的结构
    struct{
        uint16_t limit;
        uint16_t start15_0;
        uint16_t start31_16;
    }gdt;
    
    gdt.start31_16 = start >> 16;
    gdt.start15_0 = start & 0xFFFF;
    gdt.limit = size - 1;

    __asm__ __volatile__(
        "lgdt %[g]"
        ::[g]"m"(gdt)
    );
}

//lidt表
static inline void lidt(uint32_t start, uint32_t size){
    struct{
        uint16_t limit;
        uint16_t start15_0;
        uint16_t start31_16;
    }idt;
    
    idt.start31_16 = start >> 16;
    idt.start15_0 = start & 0xFFFF;
    idt.limit = size - 1;

    __asm__ __volatile__(
        "lidt %[g]"
        ::[g]"m"(idt)
    );
}



//读取cr0
static inline uint16_t read_cr0(void){
    uint32_t cr0;
    __asm__ __volatile__(
        "mov %%cr0, %[v]"
        ::[v]"r"(cr0)
    );
    return cr0;
}

//写入cr0
static inline void write_cr0(uint32_t v){
    __asm__ __volatile__(
        "mov %[v], %%cr0"
        ::[v]"r"(v)
    );
}

//远跳转(后续的课程会对跳转函数进行讲解)
static inline void far_jump(uint32_t selector, uint32_t offset){
    uint32_t addr[] = {offset, selector};

    __asm__ __volatile(
        "ljmpl *(%[a])"
        ::[a]"r"(addr)
    );
}

//读端口函数
static inline uint16_t inw(uint16_t port){
    //返回参数
    uint16_t rv;
    // in ax, dx
    __asm__ __volatile__(
        "in %[p], %[v]"
        :[v]"=a"(rv) : [p]"d"(port)
        );
    return rv;
}


static inline void hlt(void) {
    __asm__ __volatile__("hlt");
}

#endif