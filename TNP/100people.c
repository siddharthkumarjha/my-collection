/* 100 people standing in a circle in an order 1 to 100. No. 1 has a sword. He kills the next person (i.e. no 2)
 *
 * Round1: 1, 3, 5, ..., 99
 * Round2: 1, 5, 9, 13, ..., 97
 * Round3: 1, 9, 17, ..., 97
 * Round4: 9, 25, 41, 57, 73, 89
 * Round5: 9, 41, 73
 * Round6: 9, 73
 * Round7: 73
 *
 * Step1: For a given value of N, find the "power of 2" immediately greater than N. Let's call it M
 * Step2: Subtract N from (p-1). Let's call it M, M=(p-1)-N
 * Step3: Multiply M by 2, i.e., M*2
 * Step4: Subtract M*2 from p-1, Let's call it R, R=(p-1)-(M*2)
 * Step5: So the person with number R will survive till last
 */
#include <stdio.h>
int nextpowerof2(int n){
	unsigned int p=1;
	if(n && !(n&(n-1))) return n;
	while(p<n) p <<=1;
	printf("\np=%d\n", p);
	return p;
}
int main(){
	int N,M,p,R;
	printf("Enter no of people ");
	scanf("%d", &N);
	p=nextpowerof2(N);
	M=(p-1)-N;
	R=(p-1)-(M*2);
	printf("The person who survived till last %d\n", R);
	return 0;
}
