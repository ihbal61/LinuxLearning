/*
   #include <unistd.h>

   int dup(int oldfd);
      作用：复制一个新的文件描述符，在文件描述符表中找寻最小未被占用的作为新的拷贝的文件描述符
         fd=3, int fd1 = dup(fd); fd指向A，则fd1也指向表
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(){
   int fd = open("a.txt", O_CREAT | O_RDWR, 0664);

   int fd1 = dup(fd);

   if(fd1 == -1){
      perror("dup");
      return -1;
   }
   
   printf("fd: %d , fd1: %d\n", fd, fd1);
   close(fd);
   char * str = "hello world";
   int res = write(fd1, str, strlen(str));
   if(res == -1){
      perror("write");
      return -1;
   }
   close(fd1);

   return 0;
}
