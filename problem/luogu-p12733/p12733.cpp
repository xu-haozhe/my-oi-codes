#include <algorithm>
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
constexpr int maxn=1000000;
template<class T>inline void read_(T&t_)noexcept{
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
__always_inline void read()noexcept{}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read_(first);read(args...);}
template<class T>inline void write_(T t_)noexcept{
    [[assume(t_>=0)]];
    if(t_==0)return (void)(putchar('0'),putchar('\n'));
    static char str[100],*p;
    for((p=str+64);t_;t_/=10)*(--p)=(t_%10)|'0';
    for(;*p;++p)putchar(*p);putchar('\n');
}
ll n,q,d[maxn+5],num[maxn+5],sum;
int main(){
    read(n,q);
    for(int i=0;i<n;i++){
        read(d[i]);
    }
    sort(d,d+n);
    for(int i=0;i<n;i++){
        num[i+1]=num[i]+d[i]+sum;
        sum+=d[i];
    }
    for(ll t;q--;){
        read(t),write_(upper_bound(num,num+n+1,t)-num-1);
    }
    return 0;
}