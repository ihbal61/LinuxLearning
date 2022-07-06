#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

int main() {

    // 1.判断有名管道文件是否存在
    int ret = access("fifo1", F_OK);
    if(ret == -1) {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        ret = mkfifo("fifo1", 0664);
        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    ret = access("fifo2", F_OK);
    if(ret == -1) {
        // 文件不存在
        printf("管道不存在，创建对应的有名管道\n");
        ret = mkfifo("fifo2", 0664);
        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    // 2.以只读的方式打开管道fifo1
    int fdr = open("fifo1", O_RDONLY);
    if(fdr == -1) {
        perror("open");
        exit(0);
    }
    printf("打开管道fifo1成功，等待读取...\n");
    // 3.以只写的方式打开管道fifo2
    int fdw = open("fifo2", O_WRONLY);
    if(fdw == -1) {
        perror("open");
        exit(0);
    }
    printf("打开管道fifo2成功，等待写入...\n");

    char bufs[128],bufg[128];
    pid_t pid = fork();
    // 4.循环的写读数据
    while(1) {
        //父子进程分别用各自的管道，可以实现实时不阻塞通信
        if(pid > 0){
            //父进程只读
            memset(bufg, 0, 128);
            ret = read(fdr, bufg, 128);
            if(ret <= 0) {
                perror("read");
                break;
            }
            printf("buf: %s\n", bufg);
            
        }else if(pid ==0){
            //子进程只写
            memset(bufs, 0, 128);
            // 获取标准输入的数据
            fgets(bufs, 128, stdin);
            ret = write(fdw, bufs, strlen(bufs));
            if(ret == -1) {
                perror("write");
                exit(0);
            }
        }else{
            perror("fork");
            exit(0);
        }
        // 5.读管道数据

    }
    // char buf[128];

    // // 4.循环的读写数据
    // while(1) {
    //     // 5.读管道数据
    //     memset(buf, 0, 128);
    //     ret = read(fdr, buf, 128);
    //     if(ret <= 0) {
    //         perror("read");
    //         break;
    //     }
    //     printf("buf: %s\n", buf);

    //     memset(buf, 0, 128);
    //     // 获取标准输入的数据
    //     fgets(buf, 128, stdin);
    //     // 写数据
    //     ret = write(fdw, buf, strlen(buf));
    //     if(ret == -1) {
    //         perror("write");
    //         exit(0);
    //     }
    // }

    // 6.关闭文件描述符
    close(fdr);
    close(fdw);

    return 0;
}