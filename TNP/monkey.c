/* A monkey wants to climb a tree, but the problem is that he is not a good climber. After climbing N distance he slips by M distance. So he didn't know how many exact steps he needs to climb the tree. Help him to find the number of 
 *
 * Input: 10 3 2
 * Output: 8.0
 * Monkey will jump 3 distancr and slides 2 distance, so at one jump he can cover up to 1 distance
 */
#include<stdio.h>
#include<math.h>
int main(){
	double h,m,n,result;
	scanf("%lf%lf%lf", &h, &n, &m);
	result=ceil((h-n)/(n-m));
	result=result+(h-result*(n-m))/n;
	printf("%.2lf", result);
	return 0;
}
