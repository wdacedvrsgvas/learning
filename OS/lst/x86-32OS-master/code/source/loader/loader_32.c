//不需要__asm__(".code32gcc")，因为编译器默认32位

#include "loader.h"
#include "comm/elf.h"

//使用LBA48位模式读磁盘函数，参数分别为 读取位置，读多少个，读取到的数据缓存存放位置
static void read_disk(uint32_t sector, uint32_t sector_count, uint8_t *buf){
    /*设置LBA模式的参数
    */
    outb(0x1F6, 0xE0);//选择读取硬盘

    outb(0x1F2, (uint8_t)(sector_count >> 8));
    /*
    下面的0x1Fx分别表示LBA参数的从低到高的位数
    */
    outb(0x1F3, (uint8_t) (sector >> 24));
    outb(0x1F4, 0);
    outb(0x1F5, 0);
    
    outb(0x1F2, (uint8_t)sector_count);
    outb(0x1F3,(uint8_t)(sector));
    outb(0x1F4, (uint8_t)(sector >> 8));
    outb(0x1F5, (uint8_t)(sector >> 16));

    outb(0x1F7, 0x24);

    uint16_t * data_buf = (uint16_t *)buf;
    while(sector_count--){
        while((inb(0x1F7) & 0x88) != 0x8){}//通过状态寄存器可知当第三位为1时表示就绪，可以写数据或者读数据
        //开始读一个扇区数据,并将数据写入缓存
        for(int i = 0; i < SECTOR_SIZE /2 ;i++){
            *data_buf++ = inw(0x1F0);//从0x1F0读
        }
    }
}



//加载elf文件
static uint32_t reload_elf_file(uint8_t * file_buffer) {
    Elf32_Ehdr * elf_hdr = (Elf32_Ehdr *)file_buffer;
    //检查是不是Elf文件
    if((elf_hdr->e_ident[0] != 0x7F) || (elf_hdr->e_ident[1] != 'E')
        || (elf_hdr->e_ident[2] != 'L') || (elf_hdr->e_ident[3] != 'F')){
            //如果满足判断则说明不是ELF文件
            return 0;
    }
    
    //判断完为ELF文件，现在需要
    for(int i = 0;i<elf_hdr->e_phnum;i++){
        Elf32_Phdr * phdr = (Elf32_Phdr *)(file_buffer + elf_hdr->e_phoff) + i;
        if(phdr->p_type != PT_LOAD) {
            //如果不等于，说明文件是不可加载的类型
            continue;
        }

        uint8_t * src = file_buffer + phdr->p_offset;
        uint8_t * dest = (uint8_t *)phdr->p_paddr;
        for(int j = 0;j<phdr->p_filesz;j++){
            *dest++ = *src++;
        }

        //对取得bss初始化
        dest = (uint8_t *)phdr->p_paddr + phdr->p_filesz;
        for(int j = 0;j<phdr->p_memsz - phdr->p_filesz; j++){
            *dest++ = 0;
        }
    }

    return elf_hdr->e_entry;
}

static void die (int code) {
    for(;;){};
}

void load_kernel(void){
    //测试磁盘读取,内核从100个扇区开始读是为了给loader预留足够的位置，读500个扇区是留足够的内存给kernel使用
    read_disk(100, 500, (uint8_t*)SYS_KERNEL_LOAD_ADDR);



    uint32_t kernel_entry = reload_elf_file((uint8_t*)SYS_KERNEL_LOAD_ADDR);
    if(kernel_entry==0){
        die(-1);
    }
    ((void (*)(boot_info_t *))kernel_entry)(&boot_info);
    for(;;){}
}