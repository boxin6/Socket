#include <sys/socket.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <errno.h>

#define BUFFER_SIZE 1024
using namespace std;
int main(int argc, char* argv[]) 
{
    if(argc <= 2)
    {
        cout<<"Usage: ./client <IP> <port>"<<endl;
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]); //str -> int

    struct sockaddr_in server_address;
    bzero(&server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&server_address.sin_addr);
    server_address.sin_port = htons(port);

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);
    int recvbuf = atoi(argv[3]);
    int len = sizeof(recvbuf);

    setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, len);
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &recvbuf, (socklen_t*)&len);
    cout<<"recvbuf = "<<recvbuf<<endl;

    int ret = bind(sock, (struct sockaddr*)&server_address, sizeof(server_address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client_address;
    socklen_t client_addrlength = sizeof(client_address);
    int connfd = accept(sock, (struct sockaddr*)&client_address, &client_addrlength);
    if(connfd <0)
    {
        cout<<"Error: accept error"<<endl;
    }
    else
    {
        char buffer[BUFFER_SIZE];
        memset(buffer,'\0',BUFFER_SIZE);
        while(recv(connfd,buffer,BUFFER_SIZE-1,0) >0 ){}
        cout<<"got "<<ret<<" bytes of normal data: "<<buffer<<endl;
        close(connfd);

    }
    close(sock);
    return 0;
}