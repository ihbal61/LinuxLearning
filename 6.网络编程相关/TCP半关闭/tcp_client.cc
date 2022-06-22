#include <cstdio>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <errno.h>

int main() {

    // 创建socket
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        printf("create socket failed: %d\n", errno);
        return -1;
    }

    sockaddr_in seraddr;
    inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr.s_addr);
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(9999);

    // 连接服务器
    int ret = connect(fd, (sockaddr *)&seraddr, sizeof(seraddr));

    if(ret == -1){
        printf("connection failed: %d\n", errno);
        return -1;
    }

    while(1) {
        char sendBuf[1024] = {0};
        fgets(sendBuf, sizeof(sendBuf), stdin);

        write(fd, sendBuf, strlen(sendBuf) + 1);

        // 接收
        int len = read(fd, sendBuf, sizeof(sendBuf));
        if(len == -1) {
            printf("failed to read: %d", errno);
               return -1;
        } else if(len > 0) {
            printf("recv server data: %s\n", sendBuf);
        } else if(len == 0) {
            // 表示服务器端断开连接
            printf("server closed...");
            break;
        }
    }

    close(fd);

    return 0;
}
