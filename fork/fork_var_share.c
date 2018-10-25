//
// Created by vagrant on 8/19/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int golobal_a = 0;

int main()
{
    int local_a = 0;
    pthread_mutex_t local_mutex_a;
    pthread_mutex_t local_mutex_b;
    pid_t pid;

    pthread_mutex_init(&local_mutex_a, NULL);
    pthread_mutex_init(&local_mutex_b, NULL);
    pid = fork();

    if(pid > 0) {
        printf("father %d, child %d\n", getpid(), pid);
        local_a = 1;
        golobal_a = 1;
        sleep(1);
        printf("father local_a %d, addr %p, golobal_a %d, addr %p\n", local_a, &local_a, golobal_a, &golobal_a);

        pthread_mutex_lock(&local_mutex_a);
        printf("father lock mutex a %p\n", &local_mutex_a);
        sleep(1);
        pthread_mutex_lock(&local_mutex_b);
        printf("father lock mutex b %p\n", &local_mutex_b);
        pthread_mutex_unlock(&local_mutex_b);
        pthread_mutex_unlock(&local_mutex_a);
    } else if (pid == 0) {
        printf("child %d\n", getpid());
        local_a = 2;
        golobal_a = 2;
        sleep(1);
        printf("child local_a %d, addr %p, golobal_a %d, addr %p\n", local_a, &local_a, golobal_a, &golobal_a);

        pthread_mutex_lock(&local_mutex_b);
        printf("child lock mutex b %p\n", &local_mutex_b);
        sleep(1);
        pthread_mutex_lock(&local_mutex_a);
        printf("child lock mutex a %p\n", &local_mutex_a);
        pthread_mutex_unlock(&local_mutex_a);
        pthread_mutex_unlock(&local_mutex_b);
    } else{
        printf("fork fail\n");
    }

    return 0;
}
