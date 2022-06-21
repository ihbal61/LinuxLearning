#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <signal.h>

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

int main(){

   struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recyleChild;
    // 注册信号捕捉
    sigaction(SIGCHLD, &act, nullptr);

   //创建socket
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

   std::cout << "Server started, listen on for any connection request" << std::endl;

   //循环等待客户端连接
   while(1){
      sockaddr_in cliaddr;
      socklen_t len = sizeof(cliaddr);

      //接收连接
      int cfd = accept(sockfd, (sockaddr*)&cliaddr, &len);
      if(cfd == -1){
         if(errno == EINTR){
            continue;
         }
         printf("connection failed: %d\n", errno);
         return -1;
      }

      //每个连接进来， 创建一个子进程跟客户端通信
      pid_t pid = fork();
      if(pid == 0){   
         //子进程
         //获取客户端的信息
         char cliIp[16];
         inet_ntop(PF_INET, &cliaddr.sin_addr.s_addr, cliIp, sizeof(cliIp));
         unsigned short cliPort = ntohs(cliaddr.sin_port);

         printf("client ip is: %s, port is: %d\n", cliIp, cliPort);
         
         //通信
         char recvBuf[1024];
         while(1){
            //先读
            int len = read(cfd, &recvBuf, sizeof(recvBuf));
            if(len == -1){
               printf("failed to read: %d", errno);
               return -1;
            }else if(len > 0){
               printf("recv client data: %s\n", recvBuf);
            }else{
               printf("client closed...\n");
               break;
            }
            //后写
            write(cfd, recvBuf, strlen(recvBuf) + 1);
            
         }
         close(cfd);
         exit(0);//退出当前子进程
      }

   }

   close(sockfd);


   return 0;
}