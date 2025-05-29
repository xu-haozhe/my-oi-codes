#include<bits/stdc++.h>
#if __cplusplus>=201703L
#define register
#endif
using namespace std;
using ll=long long;using ull=unsigned long long;
constexpr ll maxlogn=18,maxn=1ll<<maxlogn,maxm=1<<maxlogn,mod=998244353;
template<class T> inline void  read(T&t)noexcept{
    register char ch=getchar();
    while(!isdigit(ch))ch=getchar();
    for(t=0;isdigit(ch);ch=getchar())t=t*10+ch-'0';
    [[assume(t>=0)]];
}
ll n,m,logn,u,v,w,lup[maxn],suml[maxn],l[maxn][maxlogn],sum[maxn],ans;
__always_inline unsigned char getdep(unsigned int x)noexcept{return 31-__builtin_clz(x);}
__always_inline unsigned int getsiz(unsigned int x)noexcept{return 1<<(__builtin_clz(x)+logn-(31+1));}
template<class T>__always_inline void chmin(T&x,typename remove_reference<decltype(x)>::type y)noexcept{x=min(x,y);}
int main(){
    read(logn),read(m),n=1<<logn;
    for(int i=2;i!=n;++i)read(lup[i]),suml[i]=lup[i]+lup[i>>1];
    memset(l,0x3f,sizeof(l));
    while(m--){
        read(u),read(v),read(w);
        for(int i=v;i!=u;i>>=1)for(int j=i>>1;j!=u;j>>=1)chmin(l[i][getdep(i)],w+suml[j]-suml[u]+suml[v]-suml[i]);
    }
    for(int i=2;i!=n;i++)
        for(int j=i>>1;j;j>>=1)for(int k=getdep(j);k;--k)
            chmin(l[i][k],l[j][k]+l[i][getdep(j)]);
    for(int i=n-1;i!=1;--i){
        (sum[i^1]+=lup[i^1]*getsiz(i^1)%mod)%=mod,(ans+=sum[i^1])%=mod;
        for(int j_=i,l_=1,d=getdep(i),s=getsiz(i^1);j_<n;j_<<=1,l_<<=1)for(int j=j_,e_=j+l_;j!=e_;j++)
            if(l[j][d]!=0x3f3f3f3f3f3f3f3fll)(ans+=l[j][d]*s+sum[j]%mod)%=mod;
    }
    cout<<ans;
    return 0;
}