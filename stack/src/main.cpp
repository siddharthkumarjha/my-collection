#include <stacktrace>
#include <iostream>
int main(void)
{
    std::cout << std::stacktrace::current() << std::endl;
}
