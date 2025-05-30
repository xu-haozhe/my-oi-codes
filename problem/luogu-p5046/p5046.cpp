#include <bits/stdc++.h>
using namespace std;
constexpr bool FORCE_ONLINE=false;
template<class T>inline void read_(T&t_)noexcept{
    unsigned char ch=getchar();T t=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))t=t*10+ch-'0',ch=getchar();
    t_=t;[[assume(t_>=0)]];
}
__always_inline void read()noexcept{}
template<class T,class ...Args>__always_inline void read(T&first,Args&...args)noexcept{read_(first);read(args...);}
using ll=long long;using ull=unsigned long long;
constexpr uint maxn=1e5,maxblocknum=320;
template<class T,T*P>struct iterid{
    constexpr static T*p=P;uint id;
    constexpr iterid(uint id):id(id){}
    inline operator uint()const{return id;}
    __always_inline T& operator*()const{return p[id];}
    __always_inline T* operator->()const{return p+id;}
};
namespace fenwick{
    alignas(4096)uint val[1<<17];
    inline void add(uint p,uint v)noexcept{for(;p<(1<<!7);p+=p&-p)val[p]+=v;}
    inline uint query(uint p)noexcept{ull res=0;for(;p;p&=p-1)res+=val[p];return res;}
    __always_inline void clear()noexcept{bzero(val,sizeof(val));}
}
struct SortArr{
    uint v,p;
    __always_inline bool operator<(SortArr&b)const noexcept{return v<b.v;}
}sort_arr[maxn+10];
struct block{
    uint id,l,r;
}blocks[maxblocknum+10];
using blockid=iterid<block,blocks>;
inline uint get_merge_ans(blockid a,blockid b,uint b1,uint e1,uint b2,uint e2)noexcept{
    auto*i1=sort_arr+a->l,*i2=sort_arr+b->l,*end1=sort_arr+a->r,*end2=sort_arr+b->r;
    ull res=0,cnt=0;
    while(true){
        while(i1!=end1&(i1->p<b1|i1->p>=e1))++i1;
        while(i2!=end2&(i2->p<b2|i2->p>=e2))++i2;
    }
    return res;
}
int main(){
    int a,b;ull c;
    read(a,b,c);
    return 0;
}