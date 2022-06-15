#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
int main(){

   //1.创建共享内存
   int shmid = shmget(100, 4096, IPC_CREAT | 0664);
   printf("shmid : %d\n", shmid);
    //2.和当前进程关联
    void * ptr = shmat(shmid, NULL, 0);

    char * str = "hello, world\n";

    //3.写数据
    memcpy(ptr, str, strlen(str) + 1);

    printf("按任意键继续\n");
    getchar();

    //4.解除关联
    shmdt(ptr);

    //5.删除共享内存
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
