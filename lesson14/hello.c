/*
    多进程下gdb调试默认调试父进程
    常用指令：
        -set follow-fork-mode parent/child : 设置跟踪父进程/子进程，默认跟踪父进程
        -set detach-on-fork on/off: 设置调试模式，默认为on，off时调试到当前进程在fork之后挂起
        -info inferiors: 查看调试的进程
        -inferior number：切换调试进程
        -detach inferiors id: 使进程脱离gdb调试
*/
#include <stdio.h>
#include <unistd.h>

int main() {

    printf("begin\n");

    if(fork() > 0) {

        printf("我是父进程：pid = %d, ppid = %d\n", getpid(), getppid());

        int i;
        for(i = 0; i < 10; i++) {
            printf("i = %d\n", i);
            sleep(1);
        }

    } else {

        printf("我是子进程：pid = %d, ppid = %d\n", getpid(), getppid());
        
        int j;
        for(j = 0; j < 10; j++) {
            printf("j = %d\n", j);
            sleep(1);
        }

    }

    return 0;
}