;在代码段中使用栈
assume cs:code

code segment
    dw 0123h,0456h,0789h,0abch,0defh,0fedh,0cbah,0987h
    dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 ;作为栈使用
start:
    mov ax,cs ;将栈段寄存器设置cs上
    mov ss,ax
    mov sp,30h ;设置栈顶ss:sp -> 到栈底 cs:48

    mov bx,0
    mov cx,8
  s:mov ax,cs:[bx]
    push ax
    add bx,2
    loop s

    mov cx,8
    mov bx,0
 s1:pop ax
    mov ss:[bx],ax
    add bx,2
    loop s1

    mov ax,4c00h
    int 21h

code ends
end start


;将数据、代码、栈放入不同的段
assume cs:code ds:data ss:stack

;数据段
data segment
    dw 0123h,0456h,0789h,0abch,0defh,0fedh,0cbah,0987h
data ends

;堆栈段
stack segment
    dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
data ends

;代码段
stack segment
start:
    mov ax,data ;关联ds段
    mov ds,sx
    mov ax,stack ;关联ss段
    mov ss,ax
    mov sp,32 ;设置栈顶

    mov bx,0
    mov cx,8
  s:push [bx]
    add bx,2
    loop s

    mov cx,8
    mov bx,0
 s1:pop [bx]
    add bx,2
    loop s1

    mov ax,4c00h
    int 21h

code ends
end start

;不同的寻址方式的灵活应用
;将datasg段中每个单词改为大写字母
assume cs:codesg,ds:datasg,ss:stacksg

datasg segment 
    db 'ibm             '    ;16
    db 'dec             '
    db 'dos             '
    db 'vas             '  ;看成二维数组
datasg ends

stacksg segment ;定义一个段，用来做栈段，容量为16个字节
    dw 0,0,0,0,0,0,0,0
stacksg ends

codesg segment
    start:  mov ax,stacksg
            mov ss,ax
            mov sp,16
            mov ax,datasg
            mov ds,ax
            mov bx,0   ;初始ds:bx

            ;cx为默认循环计数器，二重循环只有一个计数器，所以外层循环先保存cx值，再恢复，我们采用栈保存
            mov cx,4
    s0:     push cx   ;将外层循环的cx值入栈
            mov si,0
            mov cx,3
    s:      mov al,[bx+si]
            and al,11011111b ;每个字符转为大写字母
            mov [bx+si],al
            inc si
            loop s

            add bx,16 ;下一行
            pop cx   ;恢复cx值
            loop s0  ;外层循环的loop指令将cx中的计数值减1

            mov ax,4c00h
            int 21H

codesg ends
end start

;bx和si、bx和di、bp和si、bp和di

;不关心数据的值是多少 地方：CPU内部、内存、端口
;立即数（idata）
mov ax, 1                 ;对于直接包含在机器指令中的数据（执行前在CPU的指令缓冲器中）
add bx, 2000h             ;在汇编语言中称为：立即数（idata）
or bx, 00010000b
mov al, 'a'
;寄存器
mov ax, bx     ;指令要处理的数据在寄存器中，在汇编指令中给出相应的寄存器名。
mov ds, ax 
push bx 
mov ds:[0], bx 
push ds 
mov ss, ax
mov sp, ax
;段地址（SA）和偏移地址（EA）
;指令要处理的数据在内存中，在汇编指令中可用[X]的格式给出EA，SA在某个段寄存器中。
mov ax, [0]
mov ax, [di]
mov ax, [bx+8]
mov ax, [bx+si]
mov ax, [bx+si+8]   ;以上段地址默认在ds中

mov ax, [bp]
mov ax, [bp+8]
mov ax, [bp+si]
mov ax, [bp+si+8]   ;以上段地址默认在ss中

mov ax, ds:[bp]
mov ax, es:[bx]
mov ax, ss:[bx+si]
mov ax, cs:[bx+si+8] ;显式给出存放段地址的寄存器

;div是除法指令
;利用除法指令计算100001/100。
;100001D = 186A1H
mov dx, 1
mov ax, 86A1H ;(dx)*10000H+(ax)=100001
mov bx, 100
div bx

;利用除法指令计算1001/100
mov ax, 1001
mov bl, 100
div b1

db 3 dup (0)       ;定义了3个字节，它们的值都是0，相当于db 0，0，0。
db 3 dup (0, 1, 2) ;定义了9个字节，它们是0、1、2、0、1、2、0、1、2，相当于db 0，1，2，0，1，2，0，1，2。
db 3 dup ('abc', 'ABC') ;定义了18个字节，它们是abcABCabcABCabcABCC，相当于db 'abc', 'ABC' ,'abc' , 'ABC, 'abc', 'ABC'。

