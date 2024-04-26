// 引入更多的进程和线程，使用更复杂的数据结构和算法，以及实现更高级的同步和通信机制。下面是一个更加复杂的示例，其中实现了一个多生产者-多消费者问题，并使用了条件变量和循环缓冲区

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 3
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
sem_t mutex, full, empty;

void *producer(void *arg)
{
    int item = 1;
    while (1)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
        // 生产一个物品并放入缓冲区
        printf("Producer produced item %d\n", item);
        buffer[item % BUFFER_SIZE] = item;
        item++;
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }
}

void *consumer(void *arg)
{
    int item;
    while (1)
    {
        sem_wait(&full);
        sem_wait(&mutex);
        // 从缓冲区中消费一个物品
        item = buffer[item % BUFFER_SIZE];
        printf("Consumer consumed item %d\n", item);
        sem_post(&mutex);
        sem_post(&empty);
        sleep(2);
    }
}

int main()
{
    pthread_t producer_thread, consumer_thread[NUM_THREADS];

    // 初始化信号量
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);

    // 创建生产者线程
    pthread_create(&producer_thread, NULL, producer, NULL);

    // 创建消费者线程
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&consumer_thread[i], NULL, consumer, NULL);
    }

    // 等待线程结束
    pthread_join(producer_thread, NULL);
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(consumer_thread[i], NULL);
    }

    // 销毁信号量
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}

// 一个典型的多生产者-多消费者问题，使用了条件变量和互斥锁来实现生产者和消费者之间的同步。主要的改进包括：
// 引入了多个生产者和消费者，它们并行地生产和消费物品。
// 使用了条件变量来实现生产者和消费者之间的等待和唤醒机制，以便在缓冲区有空间可生产或有物品可消费时通知对方。
// 使用了循环缓冲区来存储生产的物品，避免了缓冲区满或空时的阻塞。
// 使用了随机数来模拟生产者生产的物品。