/* Given 2 eggs and 100 floors, the task is to find the minimum number of trials needed, in the worst case, to find the floor below which all floors are safe. A floor is safe if dropping an egg from it does not break the egg */
// Answer is 14
// First attempt at x floor
// if it breaks, try remaining (x-1) floors
// Since the last floor to be tried is 100th floor, sum of series should be 100 for optimal value of x
// x + (x-1) + (x-2) + ... + 1 = 100
//x(x+1)/2 = 100
//x=13.651
//Therefore, we start trying from 14th floor
//if egg breaks we try one by one remaining floors

#include<stdio.h>
int twoeggdrop(int k){
	return ceil(-1.0 + sqrt(1 + 8*k)/2);
}
