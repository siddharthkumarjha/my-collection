#include <bits/stdc++.h>
using namespace std;
int spcl(string s){
  int count = 0;
  int n=s.length();
  for(int i=0; i<n; i++){
    if((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9') || s[i] == ' ') continue;
    count++;
  }
  return count;
}
int main(){
  string s = "ABBS +=* aa **as a**.,<>/? sdjfoihf 9098137";
  int sp = spcl(s);
  cout << "The number of special chars are: " << sp << endl;
  return 0;
}
