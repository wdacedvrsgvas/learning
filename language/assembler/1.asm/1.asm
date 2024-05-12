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

;无条件转移指令（jmp） 条件转移指令（jnz jz..） 循环指令（loop） 过程 中断（int）
;操作符offset
;将s处的一条指令复制到s0处
assume cs:codesg
codesg segment
    ;s：这是一个标号（label），用于标记代码中的位置。在这个例子中，它是一个简单的标号，没有实际的代码，只是用来作为参考。
    s:  mov ax, bx           ;（mov ax,bx 的机器码占两个字节）
        mov si, offset s     ;这行代码将标号s的偏移地址（offset）加载到si寄存器中。在汇编语言中，偏移地址表示了在段中的位置。
        mov di, offset s0    ;获得标号s0的偏移地址

        mov ax, cs:[si] ;这行代码从cs（代码段）中，根据si寄存器中的偏移地址，读取一个字（16位），并将其加载到ax寄存器中。
        mov cs:[di], ax
    s0: nop                     ;（nop的机器码占一个字节）
        nop      ;nop：这是“no operation”的缩写，即空操作指令，它不做任何事情，只是占据一个字节的空间。
 codesg ends
 ends
; s 标号并不代表存储数据的地址，而是代码中的一个标记，用于标识某个位置。
; 因此，mov ax, cs:[si] 指令并不是从 s 标号所代表的地址处读取数据，而是从 si 寄存器中存储的 s 标号的偏移地址所指向的内存地址处读取数据。

; 由于在提供的代码中，并没有明确给出 s 标号所指向的具体数据，所以无法确定 mov ax, cs:[si] 指令到底读取了什么内容。
; 因此，这行指令读取的是 s 标号所代表的偏移地址处的数据，但是具体是什么数据取决于程序执行时 s 标号所代表的位置的内容

;​ jmp short 标号 jmp near ptr 标号 jcxz 标号 loop 标号   等几种汇编指令，它们对 IP的修改
;1、依据位移进行转移的jmp指令
;jmp short 标号（段内短转移）
;指令“jmp short 标号”的功能为(IP)=(IP)+8位位移，转到标号处执行指令
;（1）8位位移 = “标号”处的地址 - jmp指令后的第一个字节的地址；
;（2）short指明此处的位移为8位位移；
;（3）8位位移的范围为-128~127，用补码表示
;（4）8位位移由编译程序在编译时算出。



jmp short s指令的读取和执行过程如下： 
(1) (CS)=076C,(IP)=0000，执行完 mov ax,0 后CS:IP指向了 EB 03 (jmp short s机器码)； 
(2) 读取指令码 EB 03 进入指令缓冲器； 
(3) (IP) = (IP) + 所读取指令的长度 = (IP) + 2 = 5，CS:IP指向了add ax,1； 
(4) CPU执行指令缓冲器中的指令 EB 03 ； 
(5) 指令执行后 IP+位移 =(IP) + 3 = 8，CS:IP(076C:0008) 指向->inc ax

assume cs:codesg
codesg segment
    start:mov ax,0
        jmp short s ;s不是被翻译成目的地址
        add ax, 1
      s:inc ax ;程序执行后， ax中的值为 1 
codesg ends
end start
;CPU不需要这个目的地址就可以实现对IP的修改。这里是依据位移进行转移
;jmp short s指令的读取和执行过程：
; (CS)=0BBDH，(IP)=0006，上一条指令执行结束后CS:IP指向EB 03（jmp short s的机器码）；
; 读取指令码EB 03进入指令缓冲器；
; (IP) = (IP) + 所读取指令的长度 = (IP) + 2 = 0008，CS:IP指向add ax,1；
; CPU指行指令缓冲器中的指令EB 03；
; 指令EB 03执行后，(IP)=000BH，CS:IP指向inc ax
; jmp near ptr 标号 （段内近转移）
; 指令“jmp near ptr 标号”的功能为：(IP) = (IP) + 16位位移。

;2、转移的目的地址在指令中的jmp指令
; jmp far ptr 标号（段间转移或远转移）
; 指令 “jmp far ptr 标号” 功能如下：
; (CS) = 标号所在段的段地址；
; (IP) = 标号所在段中的偏移地址。
; far ptr指明了指令用标号的段地址和偏移地址修改CS和IP。
assume cs:codesg
codesg segment
   start: mov ax, 0
		  mov bx, 0
          jmp far ptr  s ;s被翻译成转移的目的地址0B01 BD0B
          db 256 dup (0) ;转移的段地址：0BBDH，偏移地址：010BH
    s:    add ax,1
          inc ax
codesg ends
end start

;3、转移地址在寄存器或内存中的jmp指令




;call和ret指令
assume cs:code,ss:stack

stack segment
    db 16 dup(0)
stack ends

code segment
            mov ax,4c00h
            int 21H   ;退出到DOS
    main:   
            mov ax,stack
            mov ss,ax
            mov sp,16
            mov ax,0
            push ax   ;压栈
        ret         ;pop ip, ->cs:ip cs:0 ,让程序跳到入口处上面
code ends
end main