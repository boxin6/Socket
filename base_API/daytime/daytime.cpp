#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>
#include <unistd.h>
#include <assert.h>
using namespace std;
int main(int argc, char *argv[])
{
    assert(argc == 2);
    char *host = argv[1];
    struct hostent *hostinfo = gethostbyname(host);//获取目标主机地址信息
    assert(hostinfo);
    struct servent* servinfo = getservbyname("daytime","tcp");
    assert(servinfo);
    cout<<"daytime port: "<<ntohs(servinfo->s_port)<<endl;

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = servinfo->s_port;
    address.sin_addr = *((struct in_addr*)hostinfo->h_addr);

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    int result = connect(sockfd,(struct sockaddr*)&address,sizeof(address));
    assert(result != -1);

    char buff[128];
    result = read(sockfd,buff,sizeof(buff));
    assert(result > 0);
    buff[result] = '\0';
    cout<<buff<<endl;
    close(sockfd);
    return 0;
    
}