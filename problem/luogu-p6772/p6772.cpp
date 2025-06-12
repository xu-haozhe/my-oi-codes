/*
不应使用矩阵快速幂直接转移，预处理矩阵pow2后，倍增转移
*/
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
using namespace std;
using ll=long long;using ull=unsigned long long;
template<class T>inline void read(T&t_)noexcept{
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+ch-'0',ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read(first);read(args...);}
constexpr ll MIN=-1e16;
struct alignas(8<<16) matrix256x256{ll a[256][256];};
struct alignas(8<<8) vec256{ll a[256];};
inline void mul(matrix256x256 &a,matrix256x256 &b,matrix256x256 &c){
    for(auto&i:c.a)for(auto&j:i)j=MIN;
    for(int i=0;i<256;i++){
        for(int j=0;j<256;j++){
            ll tmp=a.a[i][j],(&arr1)[256]=b.a[j],(&arr2)[256]=c.a[i];
            for(int k=0;k<256;k++)arr2[k]=max(arr2[k],arr1[k]+tmp);
        }
    }
}
inline void mul(vec256 &a,matrix256x256 &b,vec256 &c){
    for(auto&i:c.a)i=MIN;
    for(int i=0;i<256;i++){
        ll tmp=a.a[i],(&arr)[256]=b.a[i],(&arr2)[256]=c.a;
        for(int j=0;j<256;j++)arr2[j]=max(arr2[j],arr[j]+tmp);
    }
}
template<class T>struct matrix_{T d[2],*a=d,*b=d+1;inline void swap()noexcept{::swap(a,b);};};
int n,m,k,c[55];ll lstt,T;
matrix256x256 arr[32];matrix_<matrix256x256>arr2;matrix_<vec256>vec;
inline void trans(ll x,matrix_<vec256>&vec){
    for(;x;x&=x-1)mul(*vec.a,arr[63-__builtin_clzll(x&-x)],*vec.b),vec.swap();
}
struct festival{ll t,x,y;friend bool operator<(festival const&a,festival const&b){return a.t<b.t;}}f[205];
int main(){
    read(n,m,T,k);
    sort(f,f+k);
    for(int i=0;i<n;i++)read(c[i]);
    for(auto&i:vec.a->a)i=MIN;vec.a->a[0]=c[0];
    for(auto&i:arr[0].a)for(auto&j:i)j=MIN;
    for(int i=0;i<n;i++)for(int j=0;j<4;j++)arr[0].a[i*5+j][i*5+j+1]=0;
    for(int u,v,w;m--;)read(u,v,w),arr[0].a[(u-1)*5+w-1][(v-1)*5]=c[v-1];
    for(int i=0;i<31;i++)mul(arr[i],arr[i],arr[i+1]);
    for(int i=0;i<k;i++)read(f[i].t,f[i].x,f[i].y);
    sort(f,f+k);
    for(int i=0;i<k;i++){
        auto [t,x,y]=f[i];
        if(t!=lstt)trans(t-lstt,vec);
        if(vec.a->a[x*5-5]>=0)vec.a->a[x*5-5]+=y;
        lstt=t;
    }
    trans(T-lstt,vec);
    if((vec.a->a[0])>=0)cout<<(vec.a->a[0])<<'\n';else cout<<"-1\n";
    return 0;
}