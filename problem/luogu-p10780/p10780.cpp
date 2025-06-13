#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr ll mod=10007;
inline void read_mod(ll&x){
    char ch=getchar();x=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))x=((x*10)+(ch^48))%mod,ch=getchar();
}
ll n;
int main(){
    read_mod(n);
    cout<<(n*(n+1)*(n+2)/6)%mod;
    return 0;
}