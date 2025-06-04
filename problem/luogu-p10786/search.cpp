#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline constexpr ll num(ll x)noexcept{return x*(x-1)/2;}
constexpr int N=1e6/16;
ll dp[10][N+5];int arr[10][N+5];

int main(){
    for(auto&i:dp)fill(i,i+N+1,1e18);
    dp[8][1]=0;
    for(int i=7;i>=4;i--){
        for(int j=1;j<=N;j++){
            for(int k=1;k<j;k++){
                int a=j/k,b=a+1,y=j%k,x=k-y;
                if(dp[i+1][k]+num(a)*x+num(b)*y<dp[i][j]){
                    dp[i][j]=dp[i+1][k]+num(a)*x+num(b)*y;
                    arr[i][j]=k;
                }
            }
        }
    }
    cout<<dp[4][N]<<endl;
    for(int i=4,x=N;i<8;i++)cout<<(x=arr[i][x])<<",";
    return 0;
}