#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
using namespace std;
using ll=long long;using ull=unsigned long long;
constexpr ll MIN=-1e16;
struct alignas(8<<16) matrix256x256{ll a[256][256];}a;
struct alignas(8<<8) vec256{ll a[256];};
inline void mul(matrix256x256 &a,matrix256x256 &b,matrix256x256 &c){
    for(int i=0;i<256;i++){
        for(int j=0;j<256;j++){
            ll tmp=a.a[i][j],(&arr1)[256]=b.a[j],(&arr2)[256]=c.a[i];
            for(int k=0;k<256;k++)arr2[k]=max(arr2[k],arr1[k]+tmp);
        }
    }
}
inline void mul(vec256 &a,matrix256x256 &b,vec256 &c){
    for(int i=0;i<256;i++){
        for(int j=0;j<256;j++)
    }
}
int main(){
    
    return 0;
}
