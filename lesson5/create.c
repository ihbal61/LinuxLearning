/*    
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    //创建一个新的文件
    int open(const char *pathname, int flags, mode_t mode);
        参数:
            -pathname:要创建的文件的路径
            -flags:对文件的操作权限和其他设置
                -必选项：O_RDONLY（只读）, O_WRONLY（只写）, or O_RDWR（可读写）：这三种情况互斥
                -可选项：O_CREAT 文件不存在，创建新文件
                -mode：八进制的数，表示创建出的新的文件的操作权限，比如：0775
            最终权限：mode & ~umask
            0777 -> 111111111
        &   0775 -> 111111101
        ----------------------
                    111111101   -> 0775
        按位与：0与任何数都为0
        umask 作用就是抹去某些权限

        flags参数时一个int类型的数据，占4个字节，32位。
        flags 32位，每一位都是一个标志位。
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
int main(){
    //创建一个新的文件
    int fd = open("create.txt",O_RDWR | O_CREAT, 0777);// |代表按位异或，增加新的标志
    if(fd == -1){
        perror("open");
    }
    close(fd);
    return 0;
}