#include<bits/stdc++.h>
#include <cstdio>
using namespace std;
using ll=long long;using ull=unsigned long long;
struct u256{
    unsigned long long a,b,c,d;
}read_res_u256;alignas(1<<19) u256 s[1<<19];
template<class T>inline void read(T&t_)noexcept{
    unsigned char ch=getchar_unlocked();T t=0;
    while(!isdigit(ch))ch=getchar_unlocked();
    while(isdigit(ch))t=t*10+(ch&0xf),ch=getchar_unlocked();
    t_=t;[[assume(t_>=0)]];
}
unsigned char read_res_u8;
inline void read_2()noexcept{
    alignas(256)static constexpr unsigned char b[256]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,0,0xa,0xb,0xc,0xd,0xe,0xf};
    for(uint8_t i=0;i<32;i++)(((uint8_t*)(&read_res_u256))[i]=b[getchar_unlocked()])|=b[getchar_unlocked()]<<4;
    getchar_unlocked();
    read_res_u8=getchar_unlocked()&0xf;unsigned char ch=getchar_unlocked();
    if(ch^'\n')read_res_u8=read_res_u8*10+(ch&0xf),getchar_unlocked();
}
int n,m;ull a1,a2;uint8_t ans;
namespace Gen{
    inline ull r()noexcept{
        ull k3=a1,k4=a2;
        a1=k4;
        k3^=(k3<<23);
        a2=k3^k4^(k3>>17)^(k4>>26);
        return a2+k4;
    }
    inline uint r2()noexcept{//xorshift rand
        static uint x=time(0);
        return (((x^=x<<13)^=x>>17)^=x<<5);
    }
    inline void gen(){
        static uint order[400005];
        for(int i=0;i<n;i++)order[i]=i;
        // for(int i=0;i<n;++i)swap(order[i],order[r2()%n]);
        for(int i=0;i<n;i++)
            for(uint8_t j=0;j<32;j++){
                unsigned char tmp=0;
                tmp|=(r()&(1ull<<32))>>(32-7);
                tmp|=(r()&(1ull<<32))>>(32-6);
                tmp|=(r()&(1ull<<32))>>(32-5);
                tmp|=(r()&(1ull<<32))>>(32-4);
                tmp|=(r()&(1ull<<32))>>(32-3);
                tmp|=(r()&(1ull<<32))>>(32-2);
                tmp|=(r()&(1ull<<32))>>(32-1);
                tmp|=(r()&(1ull<<32))>>(32-0);
                ((uint8_t*)(s+order[i]))[j]=tmp;
            }
    }
};
__always_inline uint16_t get_num(u256 const&a,u256 const&b)noexcept{
    return __builtin_popcountll(a.a^b.a)+__builtin_popcountll(a.b^b.b)+__builtin_popcountll(a.c^b.c)+__builtin_popcountll(a.d^b.d);
}
int main(){
    read(n),read(m),read(a1),read(a2);
    Gen::gen();
    while(m--){
        read_2();
        if(ans){
            read_res_u8=0xff-read_res_u8,ans=0;
            for(uint i=0;i<n;i++)if(get_num(read_res_u256,s[i])>read_res_u8){ans=1;break;}
        }else{
            read_res_u8++,ans=0;
            for(uint i=0;i<n;i++)if(get_num(read_res_u256,s[i])<read_res_u8){ans=1;break;}
        }
        putchar('0'|ans),putchar('\n');
    }
    return 0;
}