#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main(){
   //获取当前的工作目录
   char buf[128];
   getcwd(buf, sizeof(buf));
   printf("当前的工作目录是：%s\n", buf);

   //修改工作目录
   int res = chdir("/home/chandler61/lesson/lesson10");
   if(res == -1){
      perror("chdir");
      return -1;
   }

   //新目录下创建一个新的文件
   int fd = open("abc.txt", O_CREAT | O_RDWR);
   if(fd == -1){
      perror("open");
      return -1;
   }
   close(fd);

   //获取当前的工作目录
   char buf1[128];
   getcwd(buf1, sizeof(buf1));
   printf("当前的工作目录是：%s\n", buf1);

}