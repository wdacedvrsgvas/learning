#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PASSENGERS 20

sem_t driver_sem, conductor_sem;

// `sem_t`是在POSIX标准中定义的一种信号量类型。它是一种用于进程间同步和互斥的机制，可以用于控制多个线程或进程对共享资源的访问。`sem_t`是信号量的抽象数据类型，在不同的操作系统上有不同的实现方式。
// 信号量可以有不同的初始值，并且可以被增加或减少。常用的操作包括`sem_wait()`（等待信号量，如果信号量值大于0，则减少它的值；如果值为0，则进入等待状态），`sem_post()`（增加信号量的值，唤醒等待它的线程或进程），以及`sem_init()`和`sem_destroy()`（分别用于初始化和销毁信号量）等。
// 在C语言中，`sem_t`通常是通过包含头文件`<semaphore.h>`来使用的。不过，需要注意的是，在不同的操作系统和编译环境中，对于信号量的实现方式可能会有所不同。

void *driver(void *arg)
{
    while (1)
    {
        sem_wait(&conductor_sem); // 等待售票员准备好
        printf("司机：启动车辆\n");
        printf("司机：正常行车\n");
        printf("司机：到站停车\n");
        sem_post(&driver_sem); // 通知售票员可以开车门了
    }
    return NULL;
}

void *conductor(void *arg)
{
    while (1)
    {
        printf("售票员：关好车门\n");
        sem_post(&conductor_sem); // 通知司机可以启动车辆了
        sem_wait(&driver_sem);    // 等待司机停车
        printf("售票员：开车门\n");
    }
    return NULL;
}

int main()
{
    pthread_t driver_thread, conductor_thread;

    sem_init(&driver_sem, 0, 0);
    sem_init(&conductor_sem, 0, 1); // 初始值为1，确保售票员先准备好

    pthread_create(&driver_thread, NULL, driver, NULL);
    pthread_create(&conductor_thread, NULL, conductor, NULL);

    pthread_join(driver_thread, NULL);
    pthread_join(conductor_thread, NULL);

    sem_destroy(&driver_sem);
    sem_destroy(&conductor_sem);

    return 0;
}
