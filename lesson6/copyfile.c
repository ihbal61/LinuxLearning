/*
    #include<unistd.h>
    ssize_t read(int fd, void *buf, size_t count);
        参数：
            -fd: 文件描述符，open得到，通过该文件描述符操作某个文件
            -buf：需要读取数据并存放的地方，数组的地址（传出参数）
            -count：指定的数组的大小，buffer容量
        返回值：
            -成功：
                >0 : 返回实际读取的字节大小，
                =0：文件已经读取完毕
            -失败：-1，并且设置error
    
    #include <unistd.h>

    ssize_t write(int fd, const void *buf, size_t count);
        参数：
            -fd: 文件描述符，open得到，通过该文件描述符操作某个文件
            -buf：需要往磁盘写入的数据
            -count：要写入的数据的实际的大小
        返回值：
            -成功：
                返回实际写入的字节大小，
            -失败：-1，并且设置error
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(){
    //1.open english.txt
    int srcfd = open("english.txt", O_RDONLY);
    if(srcfd == -1){
        perror("open");
        return -1;
    }
    //2.create a new file
    int destfd = open("copy.txt", O_WRONLY | O_CREAT,0664);
    if(srcfd == -1){
        perror("open");
        return -1;
    }
    //3.read write action
    char buf[1024] ={0};
    int len = 0;
    while((len = read(srcfd, buf, sizeof(buf))) > 0){
        write(destfd, buf, sizeof(buf));
    }
    
    //close file
    close(destfd);
    close(srcfd);
}