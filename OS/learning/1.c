void *northbound_car(void *arg)
{
    // 申请进入临界区
    sem_wait(&mutex);

    // 如果有南向北的车在行驶或等待，当前车要等待
    if (south_waiting > 0)
    {
        north_waiting++;
        sem_post(&mutex);
        sem_wait(&north_enter);
        north_waiting--;
    }

    // 进入ab段行驶
    printf("Car going northbound is on the ab segment.\n");

    // 离开临界区
    sem_post(&mutex);

    // 模拟行驶过程
    sleep(1);

    // 申请进入临界区
    sem_wait(&mutex);

    // 离开ab段行驶
    printf("Car going northbound has left the ab segment.\n");

    // 如果有等待的南向北车辆，允许一个南向北车辆进入
    if (south_waiting > 0)
    {
        sem_post(&south_enter);
    }
    else
    {
        // 如果没有等待的南向北车辆，允许下一个北向南车辆进入
        sem_post(&north_enter);
    }

    // 离开临界区
    sem_post(&mutex);

    return NULL;
}
