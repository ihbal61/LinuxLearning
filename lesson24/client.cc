// TCP通信的客户端
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

void recyleChild(int arg) {
    while(1) {
        int ret = waitpid(-1, NULL, WNOHANG);
        if(ret == -1) {
            // 所有的子进程都回收了
            break;
        }else if(ret == 0) {
            // 还有子进程活着
            break;
        } else if(ret > 0){
            // 被回收了
            printf("子进程 %d 被回收了\n", ret);
        }
    }
}

int main() {

    // 1.创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        printf("create socket failed: %d\n", errno);
        return -1;
    }

    // 2.连接服务器端
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    inet_pton(AF_INET, "192.168.0.102", &serveraddr.sin_addr.s_addr);
    serveraddr.sin_port = htons(9999);
    int ret = connect(fd, (sockaddr *)&serveraddr, sizeof(serveraddr));

    if(ret == -1) {
        printf("connection failed: %d\n", errno);
        return -1;
    }
    
    // 3. 通信
    char recvBuf[1024];
    int i = 0;
    while(1) {
        
        sprintf(recvBuf, "data : %d\n", i++);
        
        // 给服务器端发送数据
        write(fd, recvBuf, strlen(recvBuf)+1);

        int len = read(fd, recvBuf, sizeof(recvBuf));
        if(len == -1) {
            printf("failed to read: %d", errno);
               return -1;
        } else if(len > 0) {
            printf("recv server data: %s\n", recvBuf);
        } else if(len == 0) {
            // 表示服务器端断开连接
            printf("server closed...");
            break;
        }

        sleep(1);
    }

    // 关闭连接
    close(fd);

    return 0;
}