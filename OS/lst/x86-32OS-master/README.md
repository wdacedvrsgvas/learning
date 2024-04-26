# 李述铜老师课程手写操作系统学习笔记

#### 介绍
学习李述铜老师手写操作系统课程后的个人笔记

#### 环境架构
1. 编译器：

GCC工具链(GCC是GNU编译器的集合，即一组用于GNU不同语言的编译器，具体可参考官方文档，官方地址：https://gcc.gnu.org/):{
    GCC编译器：用于编译C源代码，将代码转为二进制文件
    GDB调试器：连接PC模拟器调试程序
    Binutils工具集：汇编器、ELF文件解析、反汇编等工具
}

2. IDE:
VSCODE(比较轻量)+CMake

3. 模拟器：
(PC模拟器用于实现对PC运行环境的模拟，这样可以不必使用真机)
在课程中李老师选用的是 qemu模拟器

4. 附加工具：
主要是用于对磁盘映像进行读写，比如dd命令、Winhex、Diskfenius等

#### 环境配置

1.  配置GCC工具链环境变量
将x86_64-elf-tools-windows压缩包解压在C盘
在系统设置->高级系统设置->高级->环境变量->Path中添加
C:\x86_64-elf-tools-windows\bin
(bin文件一般都是工具)
添加好环境变量后按Win+R输入cmd打开命令行窗口
输入x86_64-elf-gcc测试是否配置好GCC环境变量，
如果出现：
x86_64-elf-gcc: fatal error: no input files
compilation terminated.则表示GCC环境变量已经配置好

如果未出现则表示环境变量未配置好，建议从头再来配置一遍


2.  cmake配置

下载cmake安装包或者使用课程中的cmake工具，其中课程中的cmake工具版本号为3.23.1-windows-i386
安装->Add CMake to the system PATH for all users->next->默认路径即可
安装完成后检查一下Path中有没有cmake路径
然后重新启动命令行窗口输入cmake，当出现下列提示后即表示完成cmake环境配置

{Usage

  cmake [options] <path-to-source>
  cmake [options] <path-to-existing-build>
  cmake [options] -S <path-to-source> -B <path-to-build>

Specify a source directory to (re-)generate a build system for it in the
current working directory.  Specify an existing build directory to
re-generate its build system.

Run 'cmake --help' for more information.}


3.  qemu模拟器

可以自己下载或者直接安装资料中的安装包，其中资料中的安装包为：qemu-w32-setup-20170113
配置环境变量与GCC类似，测试配置是否成功：重新打开命令行窗口输入: qemu-system-i386回车稍等一会儿会自动打开qemu窗口即表示配置成功


4. Git工具

通过git工具与远程仓库完成代码的管理，具体教程请参考CSDN网站中相关资料


5. IDEA安装
VSCODE编译器安装好之后再在插件市场下载：
一、c/c++ Extension Pack
微软提供的C/C++扩展开发包
二、C++Intellisense..
c/c++智能提示
三、x86 and x86_Assembly
提供as汇编的语法高亮
四、Material Icon Theme
提供文件夹和文件的显示主题
五、LinkerScript
提供链接脚本的语法高亮
六、Hex Editor
十六进制编辑器
七、Makefile Tools
Makefile工具

#### 使用说明

1.  xxxx
2.  xxxx
3.  xxxx

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  Gitee 官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解 Gitee 上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是 Gitee 最有价值开源项目，是综合评定出的优秀开源项目
5.  Gitee 官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  Gitee 封面人物是一档用来展示 Gitee 会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
