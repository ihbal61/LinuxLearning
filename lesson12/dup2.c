/*
   #include <unistd.h>

   int dup2(int oldfd, int newfd);
      作用：重定向文件描述符
      oldfd 指向 a.txt, newfd 指向 b.txt
      调用函数成功后: newfd 和 b.txt 做close, newfd 指向了 a.txt
      oldfd 必须是一个有效的文件描述符
      oldfd 和 newfd值相同，相当于未操作
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(){
   int fd = open("a.txt", O_CREAT | O_RDWR, 0664);

   if(fd == -1){
      perror("open");
      return -1;
   }

   int fd1 = open("b.txt", O_CREAT | O_RDWR, 0664);

   if(fd1 == -1){
      perror("open");
      return -1;
   }
   
   printf("fd: %d , fd1: %d\n", fd, fd1);
   
   int fd2 = dup2(fd, fd1);

   if(fd2 == -1){
      perror("dup2");
      return -1;
   }

   //通过fd1写数据，实际操作的是a.txt
   char * str = "hello, dup2";
   int res = write(fd1, str, strlen(str));

   if(res == -1){
         perror("write");
         return -1;
   }

   printf("fd: %d , fd1: %d, fd2: %d\n", fd, fd1, fd2);
   close(fd);
   close(fd1);
   close(fd2);
   return 0;
}
