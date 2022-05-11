/*
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <unistd.h>

   int stat(const char *pathname, struct stat *statbuf);
      作用：获取一个文件相关的一些信息
      参数：
         -pathname: 需要操作的文件的路径
         -statbuf: 结构体变量，传出参数，用于保存获取到的信息
      返回值：
         -成功：返回0
         -失败：返回1，并设置错误编号errno
   int fstat(int fd, struct stat *statbuf);
   int lstat(const char *pathname, struct stat *statbuf);
      作用：获取一个文件相关的一些信息
      参数：
         -pathname: 需要操作的文件的路径
         -statbuf: 结构体变量，传出参数，用于保存获取到的信息
      返回值：
         -成功：返回0
         -失败：返回1，并设置错误编号errno

*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
int main(){
   struct stat statbuf;
   
   int res = stat("a.txt",&statbuf);

   if(res == -1){
      perror("stat");
      return -1;
   }

   printf("size:%ld\n", statbuf.st_size);

   return 0;
}