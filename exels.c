#include <unistd.h>
int main(){
  execve("/bin/ls", (char*[]){"ls", "-lh", NULL}, (char*[]){NULL});
  return 0;
}
