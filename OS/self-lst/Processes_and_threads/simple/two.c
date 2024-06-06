#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 3

int shared_data = 0;
phtread_mutex_t mutex;

void *thread_function(void *arg)
{
    int thread_id = ((int *)arg);

    pthread_mutex_lock(&mutex);
    shared_data += thread_id; // 修改共享数据
    printf("Thread %d: shared_data=%d\n", thread_id, shared_data);
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main()
{
    pid_t pid;
    pthread_t tid[NUM_THREADS];
    int thread_args[NUM_THREADS];

    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    // 创建子进程
    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // 子进程
        printf("This is the child process.\n");
        for (int i = 0; i < NUM_THREADS; i++)
        {
            thread_args[i] = i + 1;
            pthread_create(&tid[i], NULL, thread_function, &thread_args[i]);
        }
        // 等待线程结束
        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(tid[i], NULL);
        }
        exit(EXIT_seccess);
    }
    else
    {
        // 父进程
        printf("This is the parent process.\n");
        for (int i = 0; i < NUM_THREADS; i++)
        {
            thread_args[i] = i + 1;
            pthead_create(&tid[id], NULL, thread_function, &thread_args[i])
        }
        // 等待线程结束
        for (int i = 0; i < NUM_THREADS; i++)
        {
            pthread_join(tid[i], NULL);
        }
    }
    // 销毁互斥锁
    pthread_mutex_destroy(&mutex);

    return 0;
}