#ifndef IRQ_H
#define IRQ_H

// 中断号码

//除零中断序号
#define IRQ0_DE             0

#define IRQ1_DB             1
#define IRQ2_NMI            2
#define IRQ3_BP             3
#define IRQ4_OF             4
#define IRQ5_BR             5
#define IRQ6_UD             6
#define IRQ7_NM             7
#define IRQ8_DF             8
#define IRQ10_TS            10
#define IRQ11_NP            11
#define IRQ12_SS            12
#define IRQ13_GP            13
#define IRQ14_PF            14
#define IRQ16_MF            16
#define IRQ17_AC            17
#define IRQ18_MC            18
#define IRQ19_XM            19
#define IRQ20_VE            20

#define IRQ0_TIMER          0x20

//中断向量表IDT
void irq_init (void);



//中断产生时，栈的结构体
typedef struct _exception_frame_t {
    //栈中各个寄存器的值
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t num, error_code;
    uint32_t eip, cs, eflags;
}exception_frame_t;

//除零中断
void exception_handler_divider (void);

//异常处理类型
typedef void (*irq_handler_t) (exception_frame_t * frame);

//声明不同的类型异常处理函数
void exception_handler_unknown (void);
void exception_handler_divider (void);
void exception_handler_Debug (void);
void exception_handler_NMI (void);
void exception_handler_breakpoint (void);
void exception_handler_overflow (void);
void exception_handler_bound_range (void);
void exception_handler_invalid_opcode (void);
void exception_handler_device_unavailable (void);
void exception_handler_double_fault (void);
void exception_handler_invalid_tss (void);
void exception_handler_segment_not_present (void);
void exception_handler_stack_segment_fault (void);
void exception_handler_general_protection (void);
void exception_handler_page_fault (void);
void exception_handler_fpu_error (void);
void exception_handler_alignment_check (void);
void exception_handler_machine_check (void);
void exception_handler_smd_exception (void);
void exception_handler_virtual_exception (void);


int irq_install (int irq_num, irq_handler_t handler);


// PIC控制器相关的寄存器及位配置
#define PIC0_ICW1			0x20
#define PIC0_ICW2			0x21
#define PIC0_ICW3			0x21
#define PIC0_ICW4			0x21
#define PIC0_OCW2			0x20
#define PIC0_IMR			0x21

#define PIC1_ICW1			0xa0
#define PIC1_ICW2			0xa1
#define PIC1_ICW3			0xa1
#define PIC1_ICW4			0xa1
#define PIC1_OCW2			0xa0
#define PIC1_IMR			0xa1

#define PIC_ICW1_ICW4		(1 << 0)		// 1 - 需要初始化ICW4
#define PIC_ICW1_ALWAYS_1	(1 << 4)		// 总为1的位
#define PIC_ICW4_8086	    (1 << 0)        // 8086工作模式

#define PIC_OCW2_EOI		(1 << 5)		// 1 - 非特殊结束中断EOI命令


#define IRQ_PIC_START		0x20

void irq_enable(int irq_num);
void irq_disable(int irq_num);
void irq_disable_global(void);
void irq_enable_global(void);

void pic_send_eoi (int irq_num);
#endif