/*
   模拟实现ls -l
   -rw-rw-r-- 1 chandler61 chandler61 11 5月  10 21:30 a.txt
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h> 
#include <grp.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]){
   //模拟实现ls -l
   //判断传入参数是否正确
   if(argc < 2){
      printf("%s filename\n", argv[0]);
      return -1;
   }
   //通过stat函数获取用户传入文件的信息
   struct stat st;
   int res = stat(argv[1], &st);
   if(res == -1){
      perror("stat");
      return -1;
   }
   //获取文件类型与文件权限
   char perms[11] = {0};//用于保存文件类型与文件权限
   switch(st.st_mode & S_IFMT){
      case S_IFLNK: perms[0] = '1';break;
      case S_IFDIR: perms[0] = 'd';break;
      case S_IFREG: perms[0] = '-';break;
      case S_IFBLK: perms[0] = 'b';break;
      case S_IFCHR: perms[0] = 'c';break;
      case S_IFSOCK: perms[0] = 's';break;
      case S_IFIFO: perms[0] = 'p';break;
      default: perms[0] = '?';break;
   }
   //判断文件的访问权限

   //文件所有者
   perms[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
   perms[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
   perms[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';

   //文件所在组权限
   perms[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
   perms[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
   perms[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';

   //其他人权限
   perms[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
   perms[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
   perms[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';

   //获取硬链接数
   int linkNum = st.st_nlink;

   //文件所有者名称
   char * fileUser = getpwuid(st.st_uid) -> pw_name;

   //文件所在组
   char * fileGrp = getgrgid(st.st_gid) -> gr_name;

   //文件大小,_off_t = long int
   __off_t fileSize = st.st_size;

   //获取修改的时间
   char * time = ctime(&st.st_mtime);
   char mtime[512] = {0};
   strncpy(mtime, time, strlen(time) - 1);//将time 0-strlen(time) - 1的部分拷贝给mtime,目的是去除换行符

   char buf[1024];
   sprintf(buf,"%s %d %s %s %ld %s %s",perms, linkNum, fileUser, fileGrp, fileSize, mtime, argv[1]);

   printf("%s\n", buf);
   return 0;
}