  	// 16位代码，务必加上
  	.code16
 	.text
	.global _start
	
	# 声明函数为外部声明的函数
	.extern loader_entry
_start:
	jmp loader_entry

	.code32 # 声明生成32位的代码
	.text	# 表示下面的为代码
	.global protect_mode_entry # 将函数声明为全局的
	.extern load_kernel # 跳转到C代码环境去
protect_mode_entry:
	# 远跳转过来之后清空流水线
	mov $16, %ax # 为什么设置为16之后的课程会解释
	mov %ax, %ds
	mov %ax, %ss
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	jmp $8, $load_kernel # 为什么为8，之后的课程会解释
	jmp .