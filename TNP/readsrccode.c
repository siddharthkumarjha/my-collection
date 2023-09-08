#include<stdio.h>
int main(){
	FILE *fp;
	char ch;
	fp=fopen(__FILE__, "r");
	do{
		ch=fgetc(fp);
		putchar(ch);
	}while(ch != EOF);
	fclose(fp);
}
