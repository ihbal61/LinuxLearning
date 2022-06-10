#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>

// 作业:使用内存映射实现没有关系的进程间的通信。
int main() {

   // 1.打开一个文件
   int fd = open("test.txt", O_RDWR);
   int size = lseek(fd, 0, SEEK_END);  // 获取文件的大小

   // 2.创建内存映射区
   void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   if(ptr == MAP_FAILED) {
      perror("mmap");
      exit(0);
   }

   wait(NULL);
   // 父进程
   char buf[64];
   strcpy(buf, (char *)ptr);
   printf("read data : %s\n", buf);
   
    // 关闭内存映射区
    munmap(ptr, size);

    return 0;
}