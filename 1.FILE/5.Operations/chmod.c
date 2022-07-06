/*
   #include <sys/stat.h>
   int chmod(const char *pathname, mode_t mode);
      作用：修改文件权限
      参数：
         -pathname: 需要修改的文件路径
         -mode: 八进制的数，表示需要修改的权限值
      返回值：
         成功：0
         失败：-1，并设置errno
*/
#include <sys/stat.h>
#include <stdio.h>
int main(){
   int res = chmod("a.txt", 0777);

   if(res == -1){
      perror("chmod");
      return -1;
   }
   return 0;
}