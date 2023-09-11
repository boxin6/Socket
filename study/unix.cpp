#include <sys/un.h>
struct sockadd_un
{
    sa_family_t sin_family;//地址族 AD——UNIX
    char sun_path[108]; //文件路径名
};
