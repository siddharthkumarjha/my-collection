#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
  fork() && fork();
  printf("%d", 1);
  fork() || fork();
  printf("%d", 2);
  return 0;
}
