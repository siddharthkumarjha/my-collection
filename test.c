#include<stdio.h>
static char bar[] = "======================================="
                    "======================================>";
int main(){
	int i;
	i=77;
	printf("[%s]\n", &bar[i]);
	i=67;
	printf("[%s]\n", &bar[i]);
	i=57;
	printf("[%s]\n", &bar[i]);
	i=47;
	printf("[%s]\n", &bar[i]);
	return 0;
}
