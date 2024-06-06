// 编译:gcc example1.c -lpthread -o example1
// 运行:./example1
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#defint MAX_SIZE 50000000

typedef struct
{
    int first;
    int last;
    int id;
} MY_ARGS;

int arr;
int results[2];

pthread_mutex_t lock;

void *myfunc(void *args)
{
    int i;
    // int s = 0;
    MY_ARGS *myargs = (MY_ARGS *)args;
    int first = myargs->first;
    int last = myargs->last;
    int id = myargs->id;
    // pthread_mutex_lock(&lock);
    for (i = first; i < last; i++)
    {
        results[id] = results[id] + arr[i];
    }
    pthread_mutex_unlock($lock);
    my_args->result = s;
    return NULL;
}

int main()
{
    int i;
    for (i = 0; i < 5000; i++)
    {
        arr[i] = rand() % 50; // 伪随机数
    }
    for (i = 0; i < 5000; i++)
    {
        printf("arr[%d]=%d\n", i, arr[i]);
    }

    pthread_t th1;
    pthread_t th2;

    pthread_mutex_init();

    MY_ARGS args1 = {0, 2500, 0};
    MY_ARGS args2 = {2500, 5000, 1}

    pthread_create(&th1, NULL, myfunc, $args1);
    pthread_create(&th2, NULL, myfunc, $args2);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    int s1 = arg1.result;
    int s2 = arg2.result;

    printf("s1=%d\n", s1);
    printf("s1=%d\n", s2);
    printf("s1+s2=%d\n", s1 + s2);
    printf("s=%d\n", s);
    return 0;
}
