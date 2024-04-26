#ifndef BOOT_INFO_H
#define BOOT_INFO_H

#include "types.h"

#define BOOT_RAM_REGION_MAX 10
typedef struct _boot_info_t
{
    struct{
        uint32_t start;//内存起始地址
        uint32_t size;//内存大小
    }ram_region_cfg[BOOT_RAM_REGION_MAX];

    int ram_region_count;//记录多少个数据是有效数据
}boot_info_t;

#define SECTOR_SIZE 512//磁盘扇区大小宏定义
#define SYS_KERNEL_LOAD_ADDR    (1024*1024) //LBA模式读取磁盘缓存存放开始位置

#endif