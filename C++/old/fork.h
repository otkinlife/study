//
// Created by 贾凯超 on 2019/3/23.
//
#include <unistd.h>

#ifndef STUDY_FORK_H
#define STUDY_FORK_H

#endif //STUDY_FORK_H
class forkTest {
public:
    int test();
    int test2();
};
int forkTest::test() {
    int flag = 0;
    pid_t pId = fork();
    //如果pId 是 -1 说明创建子进程失败
    if (pId == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pId == 0) { // 如果pId是0说明是子进程
        int myPid = getpid();
        int parentPid = getppid();
        printf("Child:SelfID=%d ParentID=%d \n", myPid, parentPid);
        flag = 123;
        printf("Child:flag=%d %p \n", flag, &flag);
        int count = 0;
        do{
            count ++;
            sleep(1);
            printf("Child count=%d \n", count);
            if (count >= 5) {
                break;
            }
        }while (1);
        return EXIT_SUCCESS;
    } else { // 如果pId不是0说明是父进程
        printf("Parent:SelfID=%d MyChildPID=%d \n", getpid(), pId);
        flag = 456;
        printf("Parent:flag=%d %p \n", flag, &flag); // 连地址都一样,说明是真的完全拷贝,但值已经是不同的了..
        int count = 0;
        do{
            count ++;
            sleep(1);
            printf("Parent count=%d \n", count);
            if (count >= 2) {
                break;
            }
        }while (1);
    }
    return EXIT_SUCCESS;
}

int forkTest::test2() {
    int flag = 0;
    pid_t pId = fork();
    //如果pId 是 -1 说明创建子进程失败
    if (pId == -1) {
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if (pId == 0) { // 如果pId是0说明是子进程
        cout << getpid() << endl;
        cout << "这里是子进程" << endl;
        cout << ++flag << endl;
        return EXIT_SUCCESS;
    } else { // 如果pId不是0说明是父进程
        cout << getpid() << endl;
        cout << "这里是父进程" << endl;
        cout << flag << endl;
    }
    return EXIT_SUCCESS;
}
//////////////////////////////////////////////////////////////
#include <iostream>
// 必须的头文件
#include <pthread.h>
#include <string.h>

using namespace std;

#define NUM_THREADS 5

// 线程的运行函数
void* say_hello(void *args)
{
    cout << "Hello " << *((string *)args) << endl;
    return 0;
}

int main()
{
    // 定义线程的 id 变量，多个变量使用数组
    pthread_t tids[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i)
    {
        string name = "jkc";
        //参数依次是：创建的线程id，线程参数，调用的函数，传入的函数参数
        int ret = pthread_create(&tids[i], NULL, say_hello, (void *)&(name));
        if (ret != 0)
        {
            cout << "pthread_create error: error_code=" << ret << endl;
        }
    }
    //等各个线程退出后，进程才结束，否则进程强制结束了，线程可能还没反应过来；
    pthread_exit(NULL);
}