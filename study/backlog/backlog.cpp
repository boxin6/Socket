#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
static bool stop = false;// 停止服务
static void handlie_trem(int sig)/*处理信号*/
{
    stop = true;
}
int main(int argc, char* argv[])
{
    signal(SIGTERM,handlie_trem);
    if(argc <= 3)
    {
        cout<<"Usage: ./server <ip> <port> <backlog>"<<endl<<basename(argv[0]);
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);
    int backlog = atoi(argv[3]);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    struct sockaddr_in address;//  创建IPV4 SOCKET地址
    bzero(&address, sizeof(address)); 
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);//  端口转换

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);


    ret = listen(sock, backlog);
    assert(ret != -1);

    // 等待连接
    while(!stop)
    {
        sleep(1);
        // cout<<"waiting for connecting..."<<endl;
    }

    close(sock);// 关闭套接字
    return 0;
}
