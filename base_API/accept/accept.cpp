#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[])
{
    if(argc <= 2)
    {
        cout<<"Usage:"<<argv[0]<<" ./client <IPaddress> <Port>"<<endl;
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int ret = connect(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);
    // 暂停20秒等待接收客户端连接
    sleep(20);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*)&client, &client_addrlength);
    if(connfd < 0)
    {
        cout<<"errno is:"<<errno<<endl;
    }
    else
    {
        //接受连接成功后打印客户端IP和端口号
        char remote[INET_ADDRSTRLEN];;
        cout<<"connected with ip:"<<inet_ntop(AF_INET, &client.sin_addr, remote, sizeof(remote))<<"and port:"<<ntohs(client.sin_port)<<endl;
        close(connfd);
    }
    close(sock);
    return 0;
}