#include "init.h"
#include "comm/boot_info.h"
#include "cpu/cpu.h"
#include "cpu/irq.h"
#include "dev/time.h"
// #include "os_cfg.h"

// static boot_info_t * init_boot_info;        // 启动信息


void kernel_init(boot_info_t * boot_info){
    // init_boot_info = boot_info;

    cpu_init();
    irq_init();
    time_init();
}


//中断向量表玮IDTR寄存器所指向的IDT表
//当发生中断时，中断处理程序会：1.根据向量表取出表项  2. 根据选择子取GDT表项  3.从GDT表项中取基地址  4.跳转至基地址+偏移量运行


void init_main(void){
    // int a = 3 / 0;
    //irq_enable_global();
    for(;;) {}
}