/*
   //打开一个目录
   #include <sys/types.h>
   #include <dirent.h>
   DIR *opendir(const char *name);
      参数：
         -name: 需要打开的文件夹名
      返回值：
         DIR* 类型，理解为目录流

   //读取目录中的数据
   #include <dirent.h>
   struct dirent *readdir(DIR *dirp);
      参数：
         -dirp: opendir的返回值
      返回值：
         struct dirent, 代表读取到的文件的信息
         读取到了末尾或者读取失败，返回NULL，设置errno

   //关闭目录
   #include <sys/types.h>
   #include <dirent.h>
   int closedir(DIR *dirp);
      参数：opendir的返回值
      返回值：
*/
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getFileNum(const char * path);

//读取某个目录下的所有普通文件的个数
int main(int argc, char * argv[]){
   if(argc < 2){
      printf("%s path\n", argv[0]);
   }

   int num = getFileNum(argv[1]);
   printf("文件总数为：%d\n", num);
}
//用于获取目录下所有普通文件个数
int getFileNum(const char * path){
   //1.open folder
   DIR * dir = opendir(path);
   if(dir == NULL){
      perror("opendir");
      exit(0);
   }
   struct dirent * ptr;

   //记录文件数
   int total = 0;

   while((ptr = readdir(dir)) != NULL){
      //获取名称
      char * dname = ptr -> d_name;


      //忽略. 和..
      if(strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0){
         continue;
      }

      //判断是普通文件还是目录
      if(ptr -> d_type == DT_DIR){
         //目录，需要递归读取
         char newPath[256];
         sprintf(newPath, "%s/%s", path, dname);
         total += getFileNum(newPath);
      }

      if(ptr -> d_type == DT_REG){
         //普通文件
         ++total;
      }

   }

   //关闭目录
   closedir(dir);
   
   return total;
}