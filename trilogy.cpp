#include <iostream>
#include <vector>
using namespace std;
vector <long long> solution(vector<vector <int>> &A, vector<vector <int>> &B){
	vector <long long> s;
	int i =0, j=0;
	int h = B.size();
	int m = A.size();
	int numofmonst=0;
	while(j<m){
		for(int k = A[j][0]; k <= A[j][1]; k++) numofmonst++;
		j++;
	}
	while(i<h){
		j=0;
		while(j<m){
			if(B[i][0]>=A[j][0] && B[i][0]<=A[j][1] && B[i][1]>A[j][2]) numofmonst--;
			j++;
		}
		s.push_back(numofmonst);
		i++;
	}
	return s;
}

int main(){
	vector <vector <int>> A={{1, 3, 7}, {2, 5, 4}, {4, 8, 6}};
	vector <vector <int>> B={{3,5}, {5, 8}};
	vector <long long> s = solution(A, B);
	cout<<"(";
	for(auto i:s) cout<<i<<", ";
	cout<<"\b\b)"<<endl;
	return 0;
}
