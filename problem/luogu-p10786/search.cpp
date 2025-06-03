#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline constexpr ll num(ll x)noexcept{return x*(x-1)/2;}

ll arr[10];ll M[8]={4,4,5,10,100,1000,1000,1000};
inline bool dfs(ll r,ll x,int dep)noexcept{
    assert(r>=0);
    if(dep==8)return x<=1;
    for(int i=2;i<=M[dep];i++){
        auto b=x%i,a=x/i-b;
        if(b*num(i+1)+a*num(i)>r)continue;
        if(dfs(r-b*num(i+1)-a*num(i),a+b,dep+1))return arr[dep]=i,true; 
    }
    return false;
}
int main(){
    bool ok=dfs(1099944,1000000+1,0);
    if(ok){
        for(int i=0;i<8;i++)cout<<arr[i]<<" \n"[i==7];
    }
    return 0;
}