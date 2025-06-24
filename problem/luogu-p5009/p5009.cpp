#include <cstdint>
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include<bits/stdc++.h>
using namespace std;
template<class T>inline void read(T&t_){
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
template<class T,class...Args>__always_inline void read(T&first,Args&...args){read(first);read(args...);}
using ll=long long;using ull=unsigned long long;
using mat_type=ull;
constexpr mat_type mod=1e8+7;
//v ab a b l
/*
矩阵有效元素
0 0 0 0 0
1 0 0 0 0
1 1 0 0 0
1 1 0 0 0
1 0 1 1 0
*/
struct mat5x5{
    mat_type a10,a20,a21,a30,a31,a40,a42,a43;
    friend inline void mul(mat5x5 const&a,mat5x5 const&b,mat5x5&res){
        res.a10=(a.a10+b.a10)%mod;
        res.a20=(a.a20+b.a20+a.a21*b.a10)%mod;
        res.a21=(a.a21+b.a21)%mod;
        res.a30=(a.a30+b.a30+a.a31*b.a10)%mod;
        res.a31=(a.a31+b.a31)%mod;
        res.a40=(a.a40+b.a40+a.a42*b.a20+a.a43*b.a30)%mod;
        res.a42=(a.a42+b.a42)%mod;
        res.a43=(a.a43+b.a43)%mod;
    }
};
struct mat5x5_{
    mat5x5 m[2];uint8_t x=0;
    template<class T>inline void operator*=(mat5x5 const&b){mul(m[x],b,m[!x]),x^=1;}
    inline void clear(){m[0].a10=m[0].a20=m[0].a21=m[0].a30=m[0].a31=m[0].a40=m[0].a42=m[0].a43=0,x=0;}
    inline mat5x5&now(){return m[x];}
};
struct modify_v{inline void operator()(mat_type dv,mat5x5&a){
    a.a10=(a.a10+dv)%mod;a.a20=(a.a20+a.a21*dv)%mod;a.a30=(a.a30+a.a31*dv)%mod;
}};
struct modify_a{inline void operator()(mat_type da,mat5x5&a){
    a.a42=(a.a42+da)%mod;a.a42=(a.a42+da)%mod;
}};
struct modify_b{inline void operator()(mat_type db,mat5x5&a){
    a.a21=(a.a21+db)%mod;a.a43=(a.a43+db)%mod;
}};
struct modify_t{inline void operator()(mat_type dt,mat5x5&a){
    a.a20=(a.a20+a.a21*dt)%mod;a.a30=(a.a30+a.a31*dt)%mod;a.a10=(a.a10+dt)%mod;
}};

int main(){
    return 0;
}