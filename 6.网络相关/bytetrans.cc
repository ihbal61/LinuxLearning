/*
   #include <arpa/inet.h>
      网络通信时，需要将主机字节序转换成网络字节序（大端），另外一段获
   取到数据以后根据情况将网络字节序转换成主机字节序。

   //转换端口
   uint16_t htons(uint16_t hostshort); // 主机字节序 - 网络字节序
   uint16_t ntohs(uint16_t netshort); // 主机字节序 - 网络字节序

   //转IP
   uint32_t htonl(uint32_t hostlong); // 主机字节序 - 网络字节序
   uint32_t ntohl(uint32_t netlong); // 主机字节序 - 网络字节序

   h - host 主机，主机字节序
   to - 转换成什么
   n - network 网络字节序
   s - short unsigned short
   l - long unsigned int
*/
#include <arpa/inet.h>
#include <stdio.h>
int main(){
   
   //htons
   unsigned short a = 0x0102;
   unsigned short b = htons(a);

   unsigned short c = ntohs(b);

   printf("b =  %x\n", b);
   printf("c =  %x\n", c);

   printf("====================================\n");

   //htonl
   char buf[4] = {192, 168, 1, 100};
   u_int32_t num = *(int *)buf;
   int sum = htonl(num);

   unsigned char *p = (char *)&sum;
   printf("%d  %d  %d  %d\n", *p, *(p+1), *(p+2), *(p+3));

   int rnum = ntohl(sum);

   unsigned char *q = (char *)&rnum;
   printf("The IP address is :%d.%d.%d.%d\n", *q, *(q+1), *(q+2), *(q+3));
   
   return 0;
}