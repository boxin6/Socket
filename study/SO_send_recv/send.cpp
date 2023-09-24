#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 512
using namespace std;
int main(int argc, char* argv[])
{
    if(argc <= 2)
    {
        cout<<"usage: ./client <ip> <port>"<<endl;
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_address.sin_addr);
    server_address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int sendbuf = atoi(argv[3]);
    int len = sizeof(sendbuf);
    //先设置TCP发送缓冲区大小，然后进行读取
    setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, len);
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbuf, (socklen_t*)&len);
    cout<<"the t cp send buffer size is: "<<sendbuf<<endl;

    if(connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) != -1)
    {
        char buffer[BUFFER_SIZE] = "YY悦悦";
        //memset(buffer,'a',BUFFER_SIZE);
        send(sock, buffer, BUFFER_SIZE, 0);
        cout<<"send "<<" bytes of normal data: "<<buffer<<endl;
    }

    close(sock);
    return 0;
    
}