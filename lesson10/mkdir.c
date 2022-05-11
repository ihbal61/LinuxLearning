/*
   #include <sys/stat.h>
   #include <sys/types.h>

   int mkdir(const char *pathname, mode_t mode);
      作用：创建一个目录
      参数：
         -path: 需要创建的目录的路径
         -mode: 权限，八进制的数
      返回值：
         成功：0
         失败：-1，并设置errno
*/
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
int main(){
   int res = mkdir("aa", 0777);
   if(res == -1){
      perror("mkdir");
      return -1;
   }
   return 0;
}