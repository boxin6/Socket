#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define BUF_SIZE 1024
using namespace std;
int main(int argc, char* argv[])
{
    if(argc <= 2)
    {
        cout<<"arguments not enough"<<endl;
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    int ret = bind(sockfd, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);


    ret = listen(sockfd, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t client_addrlength = sizeof(client);
    int connfd = accept(sockfd, (struct sockaddr*)&client, &client_addrlength);
    if(connfd < 0)
    {
        cout<<"error"<<endl;
    }
    else
    {
        char buffer[BUF_SIZE];
        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, 0);
        cout<<"got "<<ret<<" bytes of normal data: "<<buffer<<endl;

        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, MSG_OOB);
        cout<<"got "<<ret<<" bytes of oob data: "<<buffer<<endl;

        memset(buffer, '\0', BUF_SIZE);
        ret = recv(connfd, buffer, BUF_SIZE-1, 0);
        cout<<"got "<<ret<<" bytes of normal data: "<<buffer<<endl;
    }
}