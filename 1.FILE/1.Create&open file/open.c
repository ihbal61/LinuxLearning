/*    
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    //打开一个已经存在的文件
    int open(const char *pathname, int flags);
        参数：
            pathname:要打开的文件路径
            flags：对文件的操作权限设置及其他设置
            O_RDONLY（只读）, O_WRONLY（只写）, or O_RDWR（可读写）：这三种情况互斥
        返回值：
            返回一个新的文件描述符，调用失败会返回-1
    errno:属于Linux系统函数库，库里面的一个全局变量，记录的是最近的错误号

    #include<stdio.h>
    void perror(const char *s);
       参数 s：用户描述，比如hello，最后输出的内容时 hello:xxx
    作用：打印error对应的错误描述

    //创建一个新的文件
    int open(const char *pathname, int flags, mode_t mode);
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(){
    int fd = open("a.txt",O_RDONLY);
    if(fd == -1){
        perror("open");
    }
    close(fd);
    return 0;
}