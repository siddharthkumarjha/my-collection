#include <stdio.h>
#include <unistd.h>
int main(){
	int i;
	const char progress[] = "|/-\\";

	for (i = 0; i < 100; i += 10) {
	  printf("Processing: %3d%%\r",i); /* \r returns the caret to the line start */
	  fflush(stdout);
	  sleep(1);
	}
	printf("\n"); /* goes to the next line */
	fflush(stdout);

	printf("size of progress %d\n", sizeof(progress));
	printf("Processing: ");

	for (i = 0; i < 100; i += 10) {
	  int n = (i/10)%4;
	  printf("%d%c\b\b", n, progress[n]); /* \b goes one back */
	  fflush(stdout);
	  sleep(1);
	}
	printf("\n"); /* goes to the next line */
	fflush(stdout);
	return 0;
}
