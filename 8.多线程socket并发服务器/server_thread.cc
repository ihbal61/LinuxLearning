#include <cstdio>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <errno.h>
#include <iostream>

struct sockInfo {
    int fd; // 通信的文件描述符
    sockaddr_in addr;
    pthread_t tid;  // 线 程号
};

sockInfo sockinfos[128];

void * working(void * arg) {
    // 子线程和客户端通信   cfd 客户端的信息 线程号
    // 获取客户端的信息
    sockInfo * pinfo = (sockInfo *)arg;

    char cliIp[16];
    inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, cliIp, sizeof(cliIp));
    unsigned short cliPort = ntohs(pinfo->addr.sin_port);
    printf("client ip is : %s, port is %d\n", cliIp, cliPort);

    // 接收客户端发来的数据
    char recvBuf[1024];
    while(1) {
        int len = read(pinfo->fd, &recvBuf, sizeof(recvBuf));

        if(len == -1) {
            printf("failed to read: %d", errno);
            return nullptr;
        }else if(len > 0) {
            printf("recv client : %s\n", recvBuf);
        } else if(len == 0) {
            printf("client closed....\n");
            break;
        }
        write(pinfo->fd, recvBuf, strlen(recvBuf) + 1);
    }
    close(pinfo->fd);
    return NULL;
}

int main() {

    // 创建socket
    int sockfd = socket(PF_INET, SOCK_STREAM, 0);

   if(sockfd < 0) {
        printf("create socket failed: %d\n", errno);
        return -1;
    }

    //绑定端口
   sockaddr_in sckaddr;
   sckaddr.sin_family = PF_INET;
   sckaddr.sin_addr.s_addr = INADDR_ANY;
   sckaddr.sin_port = htons(9999);
   int ret = bind(sockfd, (sockaddr *)&sckaddr, sizeof(sckaddr));
   if(ret < 0) {
      printf("bind failed: %d\n", errno);
      return -1;
   }

   //监听
   ret = listen(sockfd, 128);
   if(ret < 0){
      printf("listen failed: %d\n", errno);
      return -1;
   }

    // 初始化数据
    int max = sizeof(sockinfos) / sizeof(sockinfos[0]);
    for(int i = 0; i < max; i++) {
        bzero(&sockinfos[i], sizeof(sockinfos[i]));
        sockinfos[i].fd = -1;
        sockinfos[i].tid = -1;
    }

    std::cout << "Server started, listen on for any connection request" << std::endl;

    // 循环等待客户端连接，一旦一个客户端连接进来，就创建一个子线程进行通信
    while(1) {

        sockaddr_in cliaddr;
        socklen_t len = sizeof(cliaddr);
        // 接受连接
        int cfd = accept(sockfd, (sockaddr*)&cliaddr, &len);

        sockInfo * pinfo;
        for(int i = 0; i < max; i++) {
            // 从这个数组中找到一个可以用的sockInfo元素
            if(sockinfos[i].fd == -1) {
                pinfo = &sockinfos[i];
                break;
            }
            if(i == max - 1) {
                sleep(1);
                i--;
            }
        }

        pinfo->fd = cfd;
        memcpy(&pinfo->addr, &cliaddr, len);

        // 创建子线程
        pthread_create(&pinfo->tid, NULL, working, pinfo);

        pthread_detach(pinfo->tid);
    }

    close(sockfd);
    return 0;
}
