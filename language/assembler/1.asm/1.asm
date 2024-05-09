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