#include <sys/socket.h>
struct sockadd_in
{
    sa_family_t sin_family; //地址族 AF——INET
    u_int16_t sin_port; //端口号，用网络字节序表示
    struct in_addr sin_addr; //ipv4结构体
    
};

struct in_addr
{
    u_int32_t s_addr; //ipv4地址，用网络字节序表示
};

struct sockaddr_in6
{
    sa_family_t sin6_family; //地址族 af_inet6
    u_int16_t sin6_port;    //端口号，用网络字节序表示
    u_int32_t sin6_flowinfo;    //流信息，设置为0
    struct in6_addr sin6_addr; //IPV6结构体
    u_int32_t sin6_scope_id;    //scope ID 处于实验阶段

};

struct in6_addr
{
    unsigned char sa_addr[16];//ipv6地址，用网络字节序表示
};


