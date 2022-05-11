/*
   #include <unistd.h>
   int chown(const char *pathname, uid_t owner, gid_t group);
      作用：修改文件权限
      参数：
         -pathname: 需要修改的文件路径
         -owner: 文件所有者id
         -group: 文件所在组id
      返回值：
         成功：0
         失败：-1，并设置errno
*/
#include <unistd.h>
#include <stdio.h>
int main(){
   int res = chown("a.txt", 1000, 1000);

   if(res == -1){
      perror("chown");
      return -1;
   }

   return 0;
}