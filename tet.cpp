#include<iostream>
#include<vector>
using namespace std;
vector <int> search(vector <vector <int>> arr, int t){
	int row = arr.size();
	int i=0, col=row-1;
	vector <int> ans = {-1, -1};
	while(i < row && col >= 0){
		if(arr[i][col] == t){
			ans[0] = i;
			ans[1] = col;
			break;
		}
		else if(arr[i][col] > t) col--;
		else i++;
	}
	return ans;
}
int main(){
	vector <vector <int>> arr = { {1, 2, 5}, {3, 4, 9}, {6, 7, 10}};
	vector <int> ans = search(arr, 10);
	for(auto& i : arr){
		for(auto j : i){
			cout<<j<<" ";
		}
		cout << "\n";
	}
	cout << "The position recieved is: (" << ans[0] << " ," << ans[1] << ")" << endl;
	return 0;
}
