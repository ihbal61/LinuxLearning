/*
   #include <unistd.h>
   #include <fcntl.h>

   int fcntl(int fd, int cmd, ...);
      参数：
         -fd: 表示需要操作的文件描述符
         -cmd: 表示对文件描述符进行如何操作
            -F_DUPFD:复制文件描述符, 复制的是第一个参数fd, 得到一个新的参数fd1
               int res = fcntl(fd, F_DUPFD);

            -F_GETFL: 获取指定的文件描述符文件状态flag
            获取到的flag和通过open函数传递的flag一致。

            -F_SETFL:设置文件描述符文件状态flag
               必选项：O_RDONLY, O_WRONLY, O_RDWR 不可被修改
               可选项：
               O_APPEND: 表示追加数据
               O_NONBLOCK: 表示设置成非阻塞
                  阻塞和非阻塞：描述的是函数调用的行为
                  -阻塞：调用后，当前进程或线程被放弃，得到这结果之后返回
                  -非阻塞：调用函数后立马返回
               O_ASYNC, O_CREAT, O_DIRECT,  O_NOATIME 
      作用： 
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int main(){
   //复制文件描述符
   // int fd = open("a.txt", O_RDONLY);

   // int fd1 = fcntl(fd, F_DUPFD);
   // if(fd1 == -1){
   //    perror("fcntl");
   //    return -1;
   // }
   // printf("fd: %d , fd1: %d\n", fd, fd1);

   //修改或获取文件状态flag
   int fd = open("a.txt", O_RDWR);
   if(fd == -1){
      perror("open");
      return -1;
   }

   //获取文件flag
   int flag = fcntl(fd, F_GETFL);
   flag |= O_APPEND;
   if(flag == -1){
      perror("fcntl");
      return -1;
   }

   //修改文件flag, 给flag 加入O_APPEND标记
   int res = fcntl(fd, F_SETFL, flag);
   if(res == -1){
      perror("fcntl");
      return -1;
   }
   char * str = "world";
   write(fd, str, strlen(str));

   close(fd);
   return 0;
}