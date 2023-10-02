#include <bits/stdc++.h>
using namespace std;
int main(){
  int num;
  cin >> num;
  if(to_string(num).length() < 3) cout << 0;
  else{
    int ans = 0;
    for(int i=248; i<=num; i++){
      string t = to_string(i);
      size_t f2 = t.find('2');
      size_t f4 = t.find('4');
      size_t f8 = t.find('8');
      if(f2 == string::npos || f4 == string::npos || f8 == string::npos) continue;
      else{
        map<char, int> m;
        m['2'] = count(t.begin()+f2, t.end(), '2');
        m['4'] = count(t.begin()+f4, t.end(), '4');
        m['8'] = count(t.begin()+f8, t.end(), '8');
        if(m['2'] == m['4'] && m['4'] == m['8']){
          ans++;
          cout << t << " ";
        }
      }
    }
    cout << endl;
    cout << ans << endl;
  }
  return 0;
}
