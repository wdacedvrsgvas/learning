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

