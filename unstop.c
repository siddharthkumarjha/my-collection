#include <stdio.h>

/* should detect triplets
 * like 1 2 3, are triplets but 3 2 1 are not
 *
 * eg:
 * 9
 * 19 90 22 1 33 3 4 3 5
 * 0
 * Here 1 3 4 is a triplet
 */
int main(){
	int i=0, j=1, k=2;
	int n;
	scanf("%d",&n);
	int arr[n];
	for(i=0; i<n; i++){
		scanf("%d", (arr+i));
	}
	i=0;
	int ans=0;
	while(k<n && j<(n-1) && i<(n-2)){
		if(arr[i] < arr[j] && arr[j] < arr[k]){
			ans=1;
			break;
		}
		if(arr[i] < arr[j]) j++;
		else i++;
		if(arr[j] < arr[k]) k++;
		else j++;
	}
	printf("\n%d",ans);
	return 0;
}
