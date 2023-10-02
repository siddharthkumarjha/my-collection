#include <bits/stdc++.h>
using namespace std;
int main(){
  unordered_map<char, int> m;
  m['A'] = 1;
  m['B'] = 2;
  m['C'] = 3;
  m['D'] = 4;
  m['E'] = 5;
  string num;
  cin >> num;
  int ans = 0;
  int n=0;
  for(int i=num.length()-1; i>=0; i--)
    ans += (int)(m[num[i]] * pow(5, n++));
  cout << ans << endl;
  return 0;
}
