/*
   #include <unistd.h>
   int access(const char *pathname, int mode);
      作用：判断某个文件是否有某个权限，或判断某个文件是否存在
      参数：
         -pathname:判断的文件路径
         -mode:
            F_OK:是否文件存在
            R_OK:是否有读权限
            W_OK:是否有写权限
            X_OK:是否有执行权限
      返回值：
         成功：0
         失败：-1，并设置errno
*/
#include<unistd.h>
#include<stdio.h>
int main(){
   int res = access("a.txt", F_OK);
   if(res == -1){
      perror("F_OK");
   }
   printf("File existed!!!\n");
   return 0;
}