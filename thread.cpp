#include <cstdio>
#include <thread>
#include <vector>

/* The contents of this program will result in extremely high CPU usage with only way to stop as killing the terminal. :) */

int main(void)
{
        std::vector<std::jthread> t;
        auto lambda = [](void) -> void {
                uint64_t i = 0;
                while (true) 
                {
                        std::printf("%lu ", i++);                
                }
        };
        while (true) 
        {
                t.push_back(std::jthread(lambda));        
        }
        return 0;
}
