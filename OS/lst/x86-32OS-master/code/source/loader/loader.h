#ifndef LOADER_H
#define LOADER_H

#include "comm/boot_info.h"
#include "comm/types.h"
#include "comm/cpu_instr.h"

void protect_mode_entry(void);

//定义结构体存储通过中断获得的内存信息
typedef struct SMAP_entry
{
    uint32_t BaseL;//base address uint64_t
    uint32_t BaseH;
    uint32_t LengthL;//length uint64_t
    uint32_t LengthH;
    uint32_t Type;//entry Type，值为1时表明为我们可用的RAM空间
    uint32_t ACPI;//extended,bit0=1时表明此条目应当被忽略
}__attribute__((packed))SMAP_entry_t;

extern boot_info_t boot_info;

#endif