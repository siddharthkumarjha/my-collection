#include <bits/stdc++.h>
using namespace std;
int main(){
        string s;
        cin >> s;
        int count=0;
        int n = s.length();
        for(int i=0; i<=n-4; i++){
                string temp = s.substr(i, 4);
                //cout<<i<<"_"<<temp<<" ";
                map<char, int>m;
                int irq=0;
                for(int j=0; j<4; j++)m[temp[j]]++;
                for(auto it : m){
                        if(it.second > 1){
                                irq = 1;
                                break;
                        }
                }
                if(!irq) count++;
        }
        cout<<count<<endl;
        return 0;
}
