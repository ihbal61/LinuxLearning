#include <cstdio>
#include <ctype.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <errno.h>

int main(int argc, char *argv[]) {

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

    //int optval = 1;
    //setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

   int ret = bind(sockfd, (sockaddr *)&sckaddr, sizeof(sckaddr));
   if(ret < 0) {
      perror("bind");
      //printf("bind failed: %d\n", errno);
      return -1;
   }

   //监听
   ret = listen(sockfd, 128);
   if(ret < 0){
    perror("listen");
      //printf("listen failed: %d\n", errno);
      return -1;
   }

    // 接收客户端连接
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);
    int cfd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
    if(cfd == -1) {
        perror("accpet");
        return -1;
    }
    // 获取客户端信息
    char cliIp[16];
    inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, cliIp, sizeof(cliIp));
    unsigned short cliPort = ntohs(cliaddr.sin_port);

    // 输出客户端的信息
    printf("client's ip is %s, and port is %d\n", cliIp, cliPort );

    // 接收客户端发来的数据
    char recvBuf[1024] = {0};
    while(1) {
        int len = recv(cfd, recvBuf, sizeof(recvBuf), 0);
        if(len == -1) {
            printf("failed to read: %d", errno);
            return -1;
        } else if(len == 0) {
            printf("client closed...\n");
            break;
        } else if(len > 0) {
            printf("read buf = %s\n", recvBuf);
        }

        // 小写转大写
        for(int i = 0; i < len; ++i) {
            recvBuf[i] = toupper(recvBuf[i]);
        }

        printf("after buf = %s\n", recvBuf);

        // 大写字符串发给客户端
        ret = send(cfd, recvBuf, strlen(recvBuf) + 1, 0);
        if(ret == -1) {
            perror("send");
            //printf("failed to send: %d", errno);
            return -1;
        }
    }
    
    close(cfd);
    close(sockfd);

    return 0;
}
