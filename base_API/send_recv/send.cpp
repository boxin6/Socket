#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
int main(int argc, char* argv[])
{
    if (argc <= 2)
    {
        std::cout << "usage: ./client.out ip port" << std::endl;
        return 1;
    }
    const char* ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server_address;
    bzero(&server_address,sizeof(server_address));
    server_address.sin_family = AF_INET;
    inet_pton(AF_INET,ip,&server_address.sin_addr);
    server_address.sin_port = htons(port);

    int sockfd = socket(PF_INET,SOCK_STREAM,0);
    assert(sockfd >= 0);
    if(connect(sockfd,(struct sockaddr*)&server_address,sizeof(server_address)) < 0)
    {
        cout<<"connect failed"<<endl;
    }
    else
    {
        const char* oob_data = "7Y";
        const char* normal_data = "miss";
        send(sockfd,normal_data,strlen(normal_data),0);
        send(sockfd,oob_data,strlen(oob_data),MSG_OOB);
        send(sockfd,normal_data,strlen(normal_data),0);

    }
}