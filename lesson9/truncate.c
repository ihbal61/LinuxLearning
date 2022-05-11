/*
   #include <unistd.h>
   #include <sys/types.h>

   int truncate(const char *path, off_t length);
      作用：缩减或扩展文件至指定大小
      参数：
         -path: 需要修改的文件路径
         -length: 需要最终文件变成的大小
      返回值：
         成功：0
         失败：-1，并设置errno
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
int main(){
   int res = truncate("a.txt", 0);

   if(res == -1){
      perror("truncate");
      return -1;
   }

   return 0;
}