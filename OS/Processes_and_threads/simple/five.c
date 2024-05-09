

// `sem_t`是在POSIX标准中定义的一种信号量类型。它是一种用于进程间同步和互斥的机制，可以用于控制多个线程或进程对共享资源的访问。`sem_t`是信号量的抽象数据类型，在不同的操作系统上有不同的实现方式。
// 信号量可以有不同的初始值，并且可以被增加或减少。常用的操作包括`sem_wait()`（等待信号量，如果信号量值大于0，则减少它的值；如果值为0，则进入等待状态），`sem_post()`（增加信号量的值，唤醒等待它的线程或进程），以及`sem_init()`和`sem_destroy()`（分别用于初始化和销毁信号量）等。
// 在C语言中，`sem_t`通常是通过包含头文件`<semaphore.h>`来使用的。不过，需要注意的是，在不同的操作系统和编译环境中，对于信号量的实现方式可能会有所不同。

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_PASSENGERS 20

sem_t ticket_office_capacity; // 售票厅容量信号量
sem_t ticket_office_mutex;    // 售票厅互斥信号量

void *driver(void *arg)
{
    while (1)
    {
        sem_wait(&ticket_office_mutex); // 获取售票厅互斥信号量
        printf("司机：启动车辆\n");
        printf("司机：正常行车\n");
        printf("司机：到站停车\n");
        sem_post(&ticket_office_mutex); // 释放售票厅互斥信号量
        usleep(1000000);                // 模拟司机的行车过程
    }
    return NULL;
}

void *conductor(void *arg)
{
    while (1)
    {
        sem_wait(&ticket_office_mutex); // 获取售票厅互斥信号量
        printf("售票员：关好车门\n");
        sem_post(&ticket_office_mutex);    // 释放售票厅互斥信号量
        sem_post(&ticket_office_capacity); // 增加售票厅容量信号量
        usleep(1000000);                   // 模拟售票员的操作
        sem_wait(&ticket_office_mutex);    // 获取售票厅互斥信号量
        printf("售票员：开车门\n");
        sem_post(&ticket_office_mutex); // 释放售票厅互斥信号量
        usleep(1000000);                // 模拟售票员的操作
    }
    return NULL;
}

void *passenger(void *arg)
{
    while (1)
    {
        sem_wait(&ticket_office_capacity); // 等待售票厅容量信号量
        sem_wait(&ticket_office_mutex);    // 获取售票厅互斥信号量
        printf("购票者：购票\n");
        sem_post(&ticket_office_mutex); // 释放售票厅互斥信号量
        usleep(1000000);                // 模拟购票者的购票过程
    }
    return NULL;
}

int main()
{
    pthread_t driver_thread, conductor_thread, passenger_threads[MAX_PASSENGERS];

    sem_init(&ticket_office_capacity, 0, MAX_PASSENGERS); // 初始化售票厅容量为最大购票者数量
    sem_init(&ticket_office_mutex, 0, 1);                 // 初始化售票厅互斥信号量

    pthread_create(&driver_thread, NULL, driver, NULL);
    pthread_create(&conductor_thread, NULL, conductor, NULL);
    for (int i = 0; i < MAX_PASSENGERS; i++)
    {
        pthread_create(&passenger_threads[i], NULL, passenger, NULL);
    }

    pthread_join(driver_thread, NULL);
    pthread_join(conductor_thread, NULL);
    for (int i = 0; i < MAX_PASSENGERS; i++)
    {
        pthread_join(passenger_threads[i], NULL);
    }

    sem_destroy(&ticket_office_capacity);
    sem_destroy(&ticket_office_mutex);

    return 0;
}
