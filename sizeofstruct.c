#include <stddef.h>
#include<stdio.h>

struct ex{
        int a;
        char b;
        double c;
};

#define sizeof_field(t, f) (sizeof(((t*)0)->f));

int main(){
        size_t size = sizeof_field(struct ex, b);
        printf("Size of mem: %zu\n", size);
        return 0;
}
