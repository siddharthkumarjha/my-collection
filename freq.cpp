#include <bits/stdc++.h>
using namespace std;
void freq(vector <int> arr){
  map<int, int>m;
  for(auto it : arr){
    if(m[it]) m[it]++;
    else m[it]=1;
  }
  cout << "Number\tFreq\n";
  for(auto& it : m) cout << it.first << "\t" << it.second << endl;
}
int main(){
  vector<int> arr = {1, 1, 2, 3, 1};
  freq(arr);
  return 0;
}
