#include <iostream>
void byteorder()
{
    union 
    {
        /* data */
        short value;
        char union_bytes[sizeof(short)];
    }test;
    test.value = 0x0201;
    if((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2))
    {
        std::cout<<"big endian"<<std::endl;
    }
    else if((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1) )
    {
        std::cout<<"little endian"<<std::endl;
    }
    else
    {
        std::cout<<"unknow"<<std::endl;
    }
}
int main()
{
    byteorder();
}
