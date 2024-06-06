// 包含了多个进程和线程，并且演示了更多的同步和通信技术

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
        printf("consumer consumed item %d\n", item);
        sem_post(&mutex);
        sem_post(&empty);
        sleep(2);
    }
}
//使用了信号量来实现对共享缓冲区的互斥访问以及生产者和消费者之间的同步
//实现了多个消费者线程，它们共享同一个缓冲区
//通过无限循环使得生产者和消费者线程可以持续地生产和消费物品
//使用了sleep()函数来模拟生产和消费的时间

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
    pthread_join(producer_thrrad, NULL);
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(ocnsumer_thread[i], NULL);
    }

    // 销毁信号量
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}