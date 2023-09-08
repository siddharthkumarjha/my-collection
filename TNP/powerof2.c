#include <stdio.h>
void printb(unsigned n)
{
    unsigned i;
    for (i = 1 << 31; i > 0; i = i / 2)
        (n & i) ? printf("1") : printf("0");
    printf("\n");
}
int ispoweroftwo(int n){
	printb(n);
	printb(n-1);
	printb((n&(n-1)));
	return (n && !(n & (n-1)));
	/*n will check if n==0 and !(n & (n-1)) will check if n is a power of 2 or not */
}
int main(){
	int n;
	scanf("%d", &n);
	printf("Is %d a power of 2? %s\n", n, ispoweroftwo(n)?"Yes":"No");
	return 0;
}
