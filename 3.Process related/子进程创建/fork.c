/*
   #include <sys/types.h>
   #include <unistd.h>

   pid_t fork(void);
      作用：创建一个子进程
      返回值：
         fork()的返回值会返回两次，一次在父进程中，另一次在子进程中。
         成功：父进程返回子进程pid，子进程返回0
         失败：父进程返回-1, 子进程未被创建，并且设置errno
            errno: 
               -EAGAIN: 系统进程数达到上限
               -ENOMEM: 系统内存不足
         如何区分父子进程：通过fork()的返回值。
      虚拟地址空间分布：
         fork()之后，子进程用户区数据区的内容完全拷贝父进程，内核区也会拷贝，但是pid不同；
         子进程，父进程之间的局部变量等数据各自独立，操作某一个不会影响另一个

      父子进程之间的关系：
         区别：
            1.fork()函数的返回值不同
               父进程：>0, 返回子进程pid
               子进程：=0
            2.pcb 中的一些数据也有区别
               当前进程的id pid
               当前进程的父进程的id pid
               信号集
         联系：
            某些状态下：在子进程创建出来，还没有进行任何写操作
               -用户区的数据
               -文件描述符表
         父子进程之间变量是否是共享的？
            -刚开始的时候是一样的，修改后就不共享
            -读时共享，写时拷贝
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(){
   int num = 10;
   //创建子进程
   pid_t pid = fork();

   //判断是父进程还是子进程
   if(pid > 0){
      printf("%d\n", pid);
      //如果大于0，返回的是子进程的进程号,当前是父进程
      printf("I'm parent process, pid : %d, ppid : %d\n", getpid(), getppid());

      printf("num = : %d\n", num);
      num += 10;
      printf("num = : %d\n", num);

   }else if(pid == 0){
      //当前是子进程
      printf("I'm child process, pid : %d, ppid : %d\n", getpid(), getppid());
      printf("num = : %d\n", num);
      num += 100;
      printf("num = : %d\n", num);
   }
   
   //for循环输出一组数
   for(int i = 0; i < 5; i++){
      printf("i : %d, pid : %d\n", i, getpid());
      sleep(1);
   }

   return 0;
}
/*
   实际上，更准确来说，Linux的fork()使用是通过写时拷贝(copy-on-write) 实现。写时拷贝是一种可以推迟甚至避免拷贝数据的技术。
   内核此时并不复制整个进程的地址空间，而是让父子进程共享一段地址空间，只有需要写入时才会复制地址空间，从而使各个进程拥有各自的地址空间，也就是说，资源的复制是在需要写入的时候才会进行，在此之前，只有以只读方式共享。
   注：fork()后父子进程共享文件，fork()产生的子进程与父进程相同的文件文件描述符指向相同的文件表，引用计数增加，共享文件偏移指针。
*/