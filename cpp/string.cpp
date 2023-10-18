#include <string>
 
/*
 * A test program to evaluate the miss use of pragma pack
 * leading to std::string's strange SEGV problem.
 */
int main(int argc, char** argv)
{
    std::string filename("abc.txt");
    std::string::size_type pos = filename.rfind('.');
    std::string prefix = filename.substr(0, pos);
    printf("prefix=%s\n", prefix.c_str());
 
    return 0;
}
