#include <sys/types.h>
#include <sys/socket.h>
int main()
{
    socket(AF_INET, SOCK_STREAM, 0);
    bind(0, 0, 0);
    return 0;
}