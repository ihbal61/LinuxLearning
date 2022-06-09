/*
   #include <unistd.h>
   long fpathconf(int fd, int name);
      作用：获取文件配置值
   long pathconf(const char *path, int name);
*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
int main(){
   int pipefd[2];
   pid_t ret = pipe(pipefd);
   //查看管道容量
   long size = fpathconf(pipefd[0],_PC_PIPE_BUF);

   printf("pipe size : %ld\n", size);

   exit(0);
}