//__asm__ 是GCC的内联汇编的关键字，用于插入汇编代码
//该代码用于告诉GCC生成16位的代码
__asm__(".code16gcc");

#include "loader.h"

//定义内存检测信息变量
// static boot_info_t boot_info;
//去掉static因为此时boot_info会在loader_32.c中去使用
boot_info_t boot_info;



//通过内联汇编的形式编写输出字符串函数
static void show_msg(const char *msg){
    char ch;
    while ((ch=*msg++)!='\0'){
        //原本仅需asm即可，但是编译器会自动对asm的内联汇编代码进行优化产生不可预知的错误
        //因此asm改为__asm__ __volatile__就可以告诉gcc不优化该段内联汇编代码
        __asm__ __volatile__(
            "mov $0xe, %%ah\n\t"
            "mov %[c], %%al\n\t"
            "int $0x10"::[c]"r"(ch)
        );
    } 
}

//内存检测函数
static void detect_memory(void){
    SMAP_entry_t smap_entry;
    uint32_t contID = 0;
    uint32_t signature,bytes;
    show_msg("try to detect memory:");//打印提示信息表示开始检测内存
    boot_info.ram_region_count = 0;//设置初值为0

    //通过内联汇编逐渐填满Boot_info中的记录信息的结构体数组变量
    for(int i = 0;i<BOOT_RAM_REGION_MAX;i++){
        SMAP_entry_t *entry = &smap_entry;
        __asm__ __volatile__(
            "int $0x15"
            :"=a"(signature),"=c"(bytes),"=b"(contID)
            :"a"(0xE820),"b"(contID),"c"(24),"d"(0x534D4150),"D"(entry)
        );
        //每执行一次内联汇编语句就判断一次结果是否为0x534D4150,如果不是则表示该结果错误
        if(signature!=0x534D4150){
            //使用signature来判断是因为signature存储的是EAX的值
            show_msg("failed\r\n");
            return;//错误就结束循环退出函数
        }
        if(bytes > 20 && (entry->ACPI & 0x0001) == 0){
            continue;//如果ACPI的值为0时表示该条数据应该被忽略
        }

        if(entry->Type == 1){
            boot_info.ram_region_cfg[boot_info.ram_region_count].start = entry->BaseL;
            boot_info.ram_region_cfg[boot_info.ram_region_count].size = entry->LengthL;
            boot_info.ram_region_count++;
        }

        if(contID == 0){
            break;
        }
    }
    show_msg("ok.\r\n");
}

//gdt表的配置信息,现在先照写，后续课程会更新为什么这么写
uint16_t gdt_table[][4] = {
    {0, 0, 0, 0},
    {0xFFFF, 0x0000, 0x9a00, 0x00cf},
    {0xFFFF, 0x0000, 0x9200, 0x00cf},

};


//进入保护模式函数
static void enter_protected_mode(void){
    //1.关中断
    cli();

    //2.开A20地址线
    uint8_t v = inb(0x92);
    outb(0x92, v | 0x2);

    //3.加载GDT表
    lgdt((uint32_t)gdt_table, sizeof(gdt_table));

    //4.开启保护模式的使能位
    uint32_t cr0 = read_cr0();
    write_cr0(cr0 | (1<<0));

    //5.远跳转，清空流水线
    far_jump(8, (uint32_t)protect_mode_entry);
}

void loader_entry(void){
    show_msg("...loading...\n\r");
    detect_memory();
    enter_protected_mode();
    for(;;){}
}