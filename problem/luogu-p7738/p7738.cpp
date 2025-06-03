#include<bits/stdc++.h>
#include <cstdio>
using namespace std;
using ll=long long;using ull=unsigned long long;
struct u256{
    unsigned long long a,b,c,d;
}read_res_u256;alignas(1<<19) u256 s[1<<19];u256 s2[16][1<<19];u256*p_s2[16][65537];
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
        static uint num[16][65536];
        for(int i=0;i<n;i++){
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
                ((uint8_t*)(s+i))[j]=tmp;
            }
            for(uint8_t j=0;j<16;j++)num[j][((uint16_t*)(s+i))[j]]++;
        }
        for(uint8_t i=0;i<16;i++){
            auto*p=p_s2[i]+1;auto&num_=num[i];p[-1]=s2[i],p[0]=s2[i];
            for(int j=0;j<65535;j++)
                p[j+1]=p[j]+num_[j];
        }
        for(uint8_t i=0;i<16;i++){
            auto*p=p_s2[i]+1;u256*s_=(u256*)(((uint16_t*)s)+i);
            for(int j=0;j<n;j++)
                *(p[*(uint16_t*)(s_+j)]++)=s[j];
        }
    }
};
inline uint16_t get_num(u256 const&a,u256 const&b)noexcept{
    return __builtin_popcountll(a.a^b.a)+__builtin_popcountll(a.b^b.b)+__builtin_popcountll(a.c^b.c)+__builtin_popcountll(a.d^b.d);
}
int main(){
    read(n),read(m),read(a1),read(a2);
    Gen::gen();
    while(m--){
        read_2(),read_res_u8++;
        if(ans)read_res_u256.a^=ULONG_LONG_MAX,read_res_u256.b^=ULONG_LONG_MAX,read_res_u256.c^=ULONG_LONG_MAX,read_res_u256.d^=ULONG_LONG_MAX;
        ans=0;
        for(uint8_t i=0;i<16;i++)
            for(u256*j=p_s2[i][((uint16_t*)&read_res_u256)[i]],*e=p_s2[i][((uint16_t*)&read_res_u256)[i]+1];j!=e;j++)
                if(get_num(*j,read_res_u256)<read_res_u8){
                    ans=1;goto brk;
                }
        brk:;
        putchar('0'|ans),putchar('\n');
    }
    return 0;
}