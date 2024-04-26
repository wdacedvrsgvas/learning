#include <stdio.h>   //输入输出
#include <stdlib.h>  //内存分配
#include <unistd.h>  //进程控制
#include <pthread.h> //线程

void *thread_function(void *arg)
{
    printf("This is a thread.\n");
    pthread_exit(NULL);
}

// 主函数：
int main()
{
    pid_t pid; // 变量pid来存放fork()函数的返回值（子进程的PID）
    //<sys/types.h> 头文件中定义的，通常用于进程控制相关的函数，比如 fork() 和 wait()。
    pthread_t tid; // 变量tid来存放线程ID
    // 在C语言中，pthread_t 是在 <pthread.h> 头文件中定义的。在 POSIX 线程库中，一般使用 pthread_create() 函数创建线程，该函数会返回一个 pthread_t 类型的值，用于表示新创建线程的ID。
    // 创建子进程：
    pid = fork(); // 使用fork()函数创建一个子进程
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);

        // 在这行代码中，perror("fork") 用于打印与最近一次系统调用相关的错误消息，即 fork() 的错误消息。如果 fork() 函数调用失败，它会设置一个全局变量 errno 来指示错误的类型，并将相应的错误消息打印到标准错误流（stderr）中。
        // exit(EXOT_FAILURE) 用于退出程序，并返回一个表示失败的退出状态码。在这里，EXOT_FAILURE 应该是一个定义在程序中的错误码，但是可能是拼写错误，正确的应该是 EXIT_FAILURE，它表示程序非正常退出的标志。
    }
    else if (pid == 0)
    { // 如果fork()成功且返回值为0，这意味着当前执行的是子进程
        // 子进程
        printf("This is the child process.\n");
        exit(EXIT_SUCCESS);
        // 用于正常退出程序，并返回一个表示成功的退出状态码。在 POSIX 环境中，`EXIT_SUCCESS` 是一个宏，表示程序成功执行的标志，通常定义为0。调用 `exit(EXIT_SUCCESS)` 将会使程序终止，并返回状态码0，表示程序成功执行完成。
    }
    else
    { // 返回值大于0，则当前执行的是父进程
        // 父进程
        printf("This is the parent process.\n");
    }
    // 创建线程：
    if (pthread_create(&tid, NULL, thread_function, NULL) != 0)
    { // 创建一个新线程,线程属性（在本例中为NULL，表示默认属性）,及传递给线程函数的参数（在本例中为NULL）
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }
    // 等待线程结束：
    if (pthread_join(tid, NULL) != 0)
    { // 阻塞主线程，直到目标线程执行完毕   2参数是一个指向指针的指针，用于获取目标线程的返回值。如果不关心线程的返回值，可以将该参数设置为 NULL。
      // 调用 pthread_join 函数会阻塞当前线程，直到指定的线程（通过 thread 参数指定）执行结束。一旦目标线程执行结束，当前线程就会解除阻塞，并可以获取目标线程的返回值（如果有）。
        perror("pthread_join");
        exit(EXIT_FAILURE);
    }
    return 0;
}
