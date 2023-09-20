#include <arpa/inet.h>
#include <iostream>
#include <stdlib.h>
#include <sys/socket.h>
using namespace std;
//in_addr_t inet_addr(const char *strptr); 十进制表示的IPV4转化为网络字节序整数表示的IPV4地址
//int inet_aton(const char *strptr, struct in_addr *inp); 同上，结果存入inp
//char *inet_ntoa(struct in_addr in);  将网络字节序转为点分制，存在静态变量，返回静态变量地址
//int inet_pton(int af,const char* src,void* dst) 点分十进制转为网络字节序
//const char* inet_ntop(int af,const void* src,char* dst,size_t size) 网络字节序
int main()
{
    char* szValue1={"1.2.3.4"};
    char* szValue2={"192.168.1.1"};
    struct in_addr in1,in2;
    in1.s_addr = inet_addr(szValue1);
    cout<<in1.s_addr<<endl;
    in2.s_addr = inet_addr(szValue2);
    cout<<in2.s_addr<<endl;
    cout<<inet_ntoa(in1)<<endl;
    cout<<inet_ntoa(in2)<<endl;
    unsigned int rst[2];
    inet_pton(AF_INET,"192.168.0.1",rst);
    cout<<rst<<endl;
}