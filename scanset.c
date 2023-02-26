#include <stdio.h>
#include <malloc.h>
int main(){
	char *s;
	s = (char*)malloc(1024*sizeof(char));
	printf("Enter string: ");
	char* s2 = (char*)malloc(1024*sizeof(char));

	//input ignores n, N and \n because of %*c and the scanset 
	//we can add %d after *c to ask for numeric input 
	//after ignoring every character that comes after n, N
	
	scanf("%[^nN\n]%*c%[^\n]%*c", s, s2);
	printf("%s %s", s, s2);
	printf("\n");

	//This %*c changes behaviour inside printf
	//Here it expects the value of * from us.
	
	for(int i=1; i<=10; i++) printf("%*c\n", i, s[i]);
	
	//This should print a diagonal
	return 0;
}
