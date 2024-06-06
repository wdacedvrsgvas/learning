

// `sem_t`是在POSIX标准中定义的一种信号量类型。它是一种用于进程间同步和互斥的机制，可以用于控制多个线程或进程对共享资源的访问。`sem_t`是信号量的抽象数据类型，在不同的操作系统上有不同的实现方式。
// 信号量可以有不同的初始值，并且可以被增加或减少。常用的操作包括`sem_wait()`（等待信号量，如果信号量值大于0，则减少它的值；如果值为0，则进入等待状态），`sem_post()`（增加信号量的值，唤醒等待它的线程或进程），以及`sem_init()`和`sem_destroy()`（分别用于初始化和销毁信号量）等。
// 在C语言中，`sem_t`通常是通过包含头文件`<semaphore.h>`来使用的。不过，需要注意的是，在不同的操作系统和编译环境中，对于信号量的实现方式可能会有所不同。

// 1.用PV操作实现司机售票员进程同步

// 目的：了解进程同步的概念，理解信号量机制的原理，掌握运用信号量解决进程同步问题的方法，进而学会运用进程的同步与互斥。

// 设计要求：编程序模拟车站售票厅内进程同步问题，售票厅任何时刻最多可容纳20名购票者进入，否则需要在外面等待。每个购票者可看成一个进程。

// 2.用pv操作实现生产者消费者进程同步。
// 这两个问题都涉及到经典的进程同步问题，分别是生产者-消费者问题和司机-售票员问题。在Unix/Linux环境下，可以使用信号量（Semaphore）来实现进程同步。下面我会分别给出用PV操作实现这两个问题的一般步骤：

// ### 司机售票员进程同步

// 1. **初始化信号量**
//    - 创建一个信号量，代表售票厅内剩余的座位数量，初始值为20（最多可容纳20名购票者）。

// 2. **售票员进程**
//    - 售票员首先尝试获取信号量，如果信号量的值大于0（还有座位），则允许购票者进入。
//    - 如果信号量的值为0（售票厅已满），售票员等待，直到有购票者离开售票厅。

// 3. **购票者进程**
//    - 购票者首先尝试获取信号量，如果信号量的值大于0（还有座位），则购票成功，信号量减1。
//    - 如果信号量的值为0（售票厅已满），购票者等待，直到有其他购票者离开售票厅。

// 4. **购票完成**
//    - 购票者购票成功后，离开售票厅，释放信号量（加1）。
//    - 售票员在购票者离开后，售票厅座位数加1，释放信号量（加1）。

// ### 生产者消费者进程同步

// 1. **初始化信号量**
//    - 创建两个信号量，分别代表产品数量和缓冲区空闲空间。
//    - 产品数量信号量的初始值为0，表示缓冲区中暂时没有产品。
//    - 缓冲区空闲空间信号量的初始值为缓冲区的大小，表示初始时缓冲区是空的。

// 2. **生产者进程**
//    - 生产者首先尝试获取缓冲区空闲空间信号量，如果有空间则可以生产。
//    - 生产者将产品放入缓冲区，然后释放产品数量信号量（加1）。

// 3. **消费者进程**
//    - 消费者首先尝试获取产品数量信号量，如果有产品则可以消费。
//    - 消费者从缓冲区取出产品，然后释放缓冲区空闲空间信号量（加1）。

// 4. **生产与消费**
//    - 生产者生产产品后，缓冲区的产品数量加1，消费者可以消费。
//    - 消费者消费产品后，缓冲区的产品数量减1，生产者可以继续生产。

// 以上是一般的思路，你可以根据具体的编程环境（比如C语言中的POSIX信号量）来实现这些步骤。
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_SEATS 20

sem_t available_seats;

void *ticket_seller(void *arg)
{
    while (1)
    {
        // 尝试获取可用座位
        sem_wait(&available_seats);
        printf("Ticket sold! Available seats: %d\n", MAX_SEATS - available_seats);
        sleep(1);                   // 模拟购票过程
        sem_post(&available_seats); // 释放座位
        sleep(1);                   // 模拟售票员处理时间
    }
    return NULL;
}

int main()
{
    pthread_t seller_thread;
    // 初始化信号量，初始值为 MAX_SEATS，表示有 MAX_SEATS 个座位可用
    sem_init(&available_seats, 0, MAX_SEATS);

    // 创建售票员线程
    pthread_create(&seller_thread, NULL, ticket_seller, NULL);

    // 主线程等待售票员线程结束
    pthread_join(seller_thread, NULL);

    // 销毁信号量
    sem_destroy(&available_seats);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define PRODUCER_DELAY 1
#define CONSUMER_DELAY 2

int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg)
{
    int item = 0;
    while (1)
    {
        // 生产一个产品
        sleep(PRODUCER_DELAY);
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[item] = item;
        printf("Producer produced item %d\n", item);
        item = (item + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void *consumer(void *arg)
{
    int item;
    while (1)
    {
        // 消费一个产品
        sleep(CONSUMER_DELAY);
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[item];
        printf("Consumer consumed item %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main()
{
    pthread_t producer_thread, consumer_thread;

    // 初始化信号量和互斥锁
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // 创建生产者和消费者线程
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    // 主线程等待生产者和消费者线程结束
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    // 销毁信号量和互斥锁
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
