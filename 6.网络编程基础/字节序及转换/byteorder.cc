/*
   字节序：字节在内存中的存储顺序
      -小端字节序：数据的高位字节存储在内存的高位地址，低位字节存储在内存的低位地址
      -大端字节序：数据的高位字节存储在内存的低位地址，低位字节存储在内存的高位地址

      网络字节顺序是 TCP/IP 中规定好的一种数据表示格式，它与具体的 CPU 类型、操作系统等无关，
   从而可以保证数据在不同主机之间传输时能够被正确解释，网络字节顺序采用大端排序方式。
*/

//通过代码检测当前主机的字节序
#include <stdio.h>
#include <bits/socket.h>
 
int main(){

   union{
      /* data */
      short value;              //2字节
      char bytes[sizeof(short)]; //char[2]
   }test;
   
   test.value = 0x0102;
   if((test.bytes[0]) == 1 && (test.bytes[1] == 2)){
      printf("大端字节序\n");
   }else if((test.bytes[0]) == 2 && (test.bytes[1] == 1)){
      printf("小端字节序\n");
   }else{
      printf("unkown\n");
   }

   return 0;

}